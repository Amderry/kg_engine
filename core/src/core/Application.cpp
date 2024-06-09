#include <core/Application.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <core/Log.hpp>
#include <core/Window.hpp>
#include <core/rendering/OpenGL/VertexBuffer.hpp>
#include <core/rendering/OpenGL/VertexArray.hpp>
#include <core/rendering/OpenGL/IndexBuffer.hpp>
//#include <core/rendering/OpenGL/ShaderProgram.hpp>
#include <core/Camera.hpp>
#include <core/rendering/OpenGL/Renderer.hpp>
#include <imgui/imgui.h>
#include <imgui/backends/imgui_impl_opengl3.h>
#include <imgui/backends/imgui_impl_glfw.h>
#include <core/modules/UIModule.hpp>
#include <core/Input.hpp>
#include <chrono>


namespace engine_core
{
    GLfloat data2[]
    {
      0.5f,  0.5f,  0.0f, 0.5f,  0.2f,  1.0f,
      0.5f, -0.5f,  0.0f, 0.6f,  1.0f,  0.3f,
     -0.5f,  0.5f,  0.0f, 0.2f,  0.8f,  1.0f,
     -0.5f, -0.5f,  0.0f, 1.0f,  0.5f,  0.5f,
      0.5f,  0.5f,  1.0f, 0.5f,  0.2f,  1.0f,
      0.5f, -0.5f,  1.0f, 0.6f,  1.0f,  0.3f,
     -0.5f,  0.5f,  1.0f, 0.2f,  0.8f,  1.0f,
     -0.5f, -0.5f,  1.0f, 1.0f,  0.5f,  0.5f,
      0.5f,  0.5f,  1.0f, 0.5f,  0.2f,  1.0f,
      0.5f, -0.5f,  1.0f, 0.6f,  1.0f,  0.3f,
      0.5f,  0.5f,  0.0f, 0.2f,  0.8f,  1.0f,
      0.5f, -0.5f,  0.0f, 1.0f,  0.5f,  0.5f,
     -0.5f,  0.5f,  1.0f, 0.5f,  0.2f,  1.0f,
     -0.5f, -0.5f,  1.0f, 0.6f,  1.0f,  0.3f,
     -0.5f,  0.5f,  0.0f, 0.2f,  0.8f,  1.0f,
     -0.5f, -0.5f,  0.0f, 1.0f,  0.5f,  0.5f,
      0.5f,  0.5f,  0.0f, 0.5f,  0.2f,  1.0f,
      0.5f,  0.5f,  1.0f, 0.6f,  1.0f,  0.3f,
     -0.5f,  0.5f,  0.0f, 0.2f,  0.8f,  1.0f,
     -0.5f,  0.5f,  1.0f, 1.0f,  0.5f,  0.5f,
      0.5f, -0.5f,  0.0f, 0.5f,  0.2f,  1.0f,
      0.5f, -0.5f,  1.0f, 0.6f,  1.0f,  0.3f,
     -0.5f, -0.5f,  0.0f, 0.2f,  0.8f,  1.0f,
     -0.5f, -0.5f,  1.0f, 1.0f,  0.5f,  0.5f,
      5.0f,  5.0f,  0.0f, 0.2f,  0.2f,  0.2f,
     -5.0f,  5.0f,  0.0f, 0.2f,  0.2f,  0.2f,
      5.0f, -5.0f,  0.0f, 0.2f,  0.2f,  0.2f,
     -5.0f, -5.0f,  0.0f, 0.2f,  0.2f,  0.2f,
      5.0f,  5.0f,  0.0f, 0.3f,  0.2f,  0.2f,
      5.0f,  5.0f,  10.0f, 0.3f,  0.2f,  0.2f,
      5.0f, -5.0f,  0.0f, 0.3f,  0.2f,  0.2f,
      5.0f, -5.0f,  10.0f, 0.3f,  0.2f,  0.2f,
    };

    GLint indicies[]
    { 28, 29, 30, 31, 30, 29, 24, 25, 26, 27, 26, 25, 0, 1, 2, 3, 2, 1, 4, 5, 6, 7, 6, 5, 8, 9, 10, 11, 10, 9, 12, 13, 14, 15, 14, 13, 16, 17, 18, 19, 18, 17, 20, 21, 22, 23, 22, 21};

    GLfloat scale[]
    { 1.0, 1.0, 1.0 };

    GLfloat rotation = 0.f;

    GLfloat translation[]
    { 0.0, 0.0, 0.0 };
    float background_color[4]{ 0.44f,  0.44f, 0.55f, 0.f };

    const char* vertex_shader =
        R"(#version 460
      layout(location = 0) in vec3 vertex_position;
      layout(location = 1) in vec3 vertex_color;
      uniform mat4 model_matrix;
      uniform mat4 view_projection_matrix;
      out vec3 color;
      void main() {
        color = vertex_color;
        gl_Position = view_projection_matrix * model_matrix * vec4(vertex_position, 1.0);
      })";

    /*const char* fragment_shader =
      R"(#version 460
      in vec4 gl_FragCoord;
      out vec4 frag_color;
      uniform float time;
      uniform vec3 resolution;

      const float MAX_ITER = 128.0;

      float mandelbrot(vec2 uv)
      {
        float sized_time = time / 1000000000;
        vec2 c = 4.0 * uv - vec2(0.7, 0.0);
        c = c / vec2(0.65, 0.45);
        vec2 z = vec2(0.0);
        float iter = 0.0;
        for(float i = 0.0; i < MAX_ITER; i++){
            z = vec2(z.x * z.x - z.y * z.y, 2.0 * z.x * z.y) + c;
            if(dot(z, z) > 4.0) return iter / MAX_ITER;
            iter++;
        }
        return 0.0;
      }

      vec3 hash(float m)
      {
        float x = fract(sin(m) * 10.23123);
        float y = fract(sin(m + x) * 24.2312);
        float z = fract(cos(x + y) * 32.231);
        return vec3(x, y, z);
      }

      void main() {
         vec2 uv = (gl_FragCoord.xy - 0.5 * resolution.xy) / resolution.y;
         vec3 col = vec3(0.0);

         float m = mandelbrot(uv);
         col += hash(m);

         frag_color = vec4(col, 1.0);
      })";*/

    const char* fragment_shader =
        R"(#version 460
      in vec3 color;
      in vec4 gl_FragCoord;
      out vec4 frag_color;
      uniform float time;
      uniform vec3 resolution;
      void main() {
         frag_color = vec4(color,1.0);
      })";

    std::unique_ptr<Shader_Program> shader_program;

    std::unique_ptr<Vertex_Buffer> data_buffer;
    std::unique_ptr<Vertex_Array> vertex_array;

    std::unique_ptr<Index_Buffer> index_buffer;

	Application::Application()
	{
		log("Starting application");
	}

	Application::~Application()
	{
		log("Closing application");
	}

	int Application::start(unsigned int w_width, unsigned int w_height, const char* title)
	{
		this->app_window = std::make_unique<Window>(title, w_width, w_height);
		
		this->app_event_dispatcher.add_event_listener<Event_Mouse_Moved>(
			[&](Event_Mouse_Moved& event) {
				log("Mouse location: x-", event.x, ", y-", event.y);
                Input::move_mouse(event.x, event.y);
			}
		);

		this->app_event_dispatcher.add_event_listener<Event_Window_Resize>(
			[](Event_Window_Resize& event) {
				log("Window resized: ", event.width, "x", event.height);
			}
		);

		this->app_event_dispatcher.add_event_listener<Event_Window_Close>(
			[&](Event_Window_Close& event) {
				log("Window closed");
				is_close_window = true;
			}
		);

		this->app_event_dispatcher.add_event_listener<Event_Key_Pressed>(
			[&](Event_Key_Pressed& event) {
				log("Key ", event.key_code, " pressed");
                Input::press_key(event.key_code);
			}
		);

		this->app_event_dispatcher.add_event_listener<Event_Key_Released>(
			[](Event_Key_Released& event) {
				log("Key ", event.key_code, " released");
                Input::release_key(event.key_code);
			}
		);

		this->app_window->set_event_callback(
			[&](Base_Event& event)
			{
				this->app_event_dispatcher.dispatch(event);
			}

		
		);

        const unsigned int width = 1000;
        const unsigned int height = 1000;
        const unsigned int channels = 3;
        unsigned char* texture = new unsigned char[width * height * channels];

        GLuint texture_handle;
        glCreateTextures(GL_TEXTURE_2D, 1, &texture_handle);
        glTextureStorage2D(texture_handle, 1, GL_RGB8, width, height);

        //---------------------------//
        shader_program = std::make_unique<Shader_Program>(vertex_shader, fragment_shader);
        if (!shader_program->get_is_compiled())
        {
            exit(-1);
            return false;
        }

        Buffer_Layout buffer_layout_2_vec3
        {
            Shader_Data_Type::Float3,
            Shader_Data_Type::Float3
        };

        vertex_array = std::make_unique<Vertex_Array>();
        data_buffer = std::make_unique<Vertex_Buffer>(data2, sizeof(data2), buffer_layout_2_vec3);
        vertex_array->add_vertex_buffer(*data_buffer);

        index_buffer = std::make_unique<Index_Buffer>(indicies, sizeof(indicies) / sizeof(GLuint));
        vertex_array->set_index_buffer(*index_buffer);
        //glfwSetInputMode(this->w_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        //-------------------------------------------------------//

		while (!is_close_window)
		{
            Renderer_OpenGL::set_clear_color(background_color[0], background_color[1], background_color[2], background_color[3]);
            Renderer_OpenGL::clear();

            glm::mat4 scaling_matrix
            {
                scale[0],       0,         0,      0,
                0,      scale[1],          0,      0,
                0,              0,  scale[2],      0,
                0,              0,         0,      1
            };

            float rotation_in_radians = glm::radians(rotation);
            glm::mat4 rotation_matrix
            {
                cos(rotation_in_radians), sin(rotation_in_radians), 0, 0,
               -sin(rotation_in_radians), cos(rotation_in_radians), 0, 0,
               0,                         0,                        1, 0,
               0,                         0,                        0, 1
            };

            glm::mat4 translation_matrix
            {
                1,              0,              0,              0,
                0,              1,              0,              0,
                0,              0,              1,              0,
                translation[0], translation[1], translation[2], 1
            };

            glm::mat4 model_matrix = translation_matrix * rotation_matrix * scaling_matrix;

            camera.set_projection_type(perspective_camera ? Camera::Projection_Type::Perspective : Camera::Projection_Type::Ortographic);

            shader_program->bind();
            shader_program->set_matrix4("model_matrix", model_matrix);
            shader_program->set_matrix4("view_projection_matrix", camera.get_projection_matrix() * camera.get_view_matrix());

            auto now = std::chrono::high_resolution_clock::now();
            auto duration = now.time_since_epoch();
            auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
            shader_program->set_float("time", static_cast<float>(millis));
            shader_program->set_vec3f("resolution", glm::vec3(this->app_window->get_width(), this->app_window->get_height(), 0));

            Renderer_OpenGL::draw(*vertex_array);


            UIModule::on_ui_draw_begin();
            ImGui::Begin("Background color");
            ImGui::ColorEdit4("Color", background_color);

            ImGui::SliderFloat3("scale", scale, 0.0f, 1.0f);
            ImGui::SliderFloat("rotation", &rotation, 0.0f, 360.0f);
            ImGui::SliderFloat3("translation", translation, -1.0f, 1.0f);

            ImGui::End();
            on_ui_draw();
            UIModule::on_ui_draw_end();

			app_window->on_update();
			on_update();
		}

		return 0;
	}
}