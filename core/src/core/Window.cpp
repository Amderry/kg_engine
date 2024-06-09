#include <core/Window.hpp>
#include <core/Log.hpp>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <core/Camera.hpp>
#include <chrono>
#include <core/rendering/OpenGL/Renderer.hpp>
#include <core/modules/UIModule.hpp>

namespace engine_core
{
    GLuint vao;
	Window::Window(std::string title, const unsigned int width, const unsigned int height) 
        : w_data{ std::move(title), width, height }
	{
		int result_code = init();
	}

	Window::~Window() 
	{
		shutdown();
	}

	int Window::init() 
	{
        log("Window started with ", this->w_data.w_width, "x", this->w_data.w_height, " ", this->w_data.w_title);
        
        glfwSetErrorCallback([](int error_code, const char* desc)
            {
                log("Error: ", error_code, " Desc: ", desc);
            });

        if (!glfwInit())
        {
            log("Can't initialize GLFW");
            return -1;
        }

        this->w_window = glfwCreateWindow(w_data.w_width, w_data.w_height, w_data.w_title.c_str(), nullptr, nullptr);
        if (!this->w_window)
        {
            log("Can't create windown with  ", this->w_data.w_width, "x", this->w_data.w_height, " ", this->w_data.w_title);
            return -2;
        }

        if (!Renderer_OpenGL::init(this->w_window))
        {
            return -3;
        }

        glfwSetWindowUserPointer(this->w_window, &this->w_data);
        glfwSetWindowSizeCallback(this->w_window, []
        (GLFWwindow* p_window, int width, int height) 
            {
                Window_data data = *static_cast<Window_data*>(glfwGetWindowUserPointer(p_window));
                data.w_width = width;
                data.w_height = height;

                Event_Window_Resize event(width, height);
                data.event_callback_fn(event);
            }
        );

        glfwSetCursorPosCallback(this->w_window, []
        (GLFWwindow* p_window, double xpos, double ypos)
            {
                Window_data data = *static_cast<Window_data*>(glfwGetWindowUserPointer(p_window));

                Event_Mouse_Moved event(xpos, ypos);
                data.event_callback_fn(event);
            }
        );

        glfwSetWindowCloseCallback(this->w_window, []
        (GLFWwindow* p_window)
            {
                Window_data data = *static_cast<Window_data*>(glfwGetWindowUserPointer(p_window));

                Event_Window_Close event;
                data.event_callback_fn(event);
            }
        );

        glfwSetKeyCallback(this->w_window, []
        (GLFWwindow* p_window, int key, int scancode, int action, int mods)
            {
                Window_data data = *static_cast<Window_data*>(glfwGetWindowUserPointer(p_window));

                if (action == GLFW_PRESS || action == GLFW_REPEAT)
                {
                    Event_Key_Pressed event(key);
                    data.event_callback_fn(event);
                }
                else
                {
                    Event_Key_Released event(key);
                    data.event_callback_fn(event);
                }
            }
        );

        glfwSetFramebufferSizeCallback(this->w_window, []
        (GLFWwindow* p_window, int width, int height)
            {
                Renderer_OpenGL::set_viewport(width, height);
            }
        );

        UIModule::on_window_create(this->w_window);
        return 0;
	}

	void Window::shutdown() 
	{
        UIModule::on_window_close();
        glfwDestroyWindow(this->w_window);
        glfwTerminate();
	}

    void Window::set_mouse_pos(Event_Mouse_Moved event_mouse)
    {
        this->w_mouse_pos[0] = event_mouse.x;
        this->w_mouse_pos[1] = event_mouse.y;
    }

    void Window::handle_key(Event_Key_Pressed event_key)
    {
        if (event_key.key_code == 87) {
            this->w_camera_pos[2] += 0.01f;
        }
        else if (event_key.key_code == 83) {
            this->w_camera_pos[2] -= 0.01f;
        }
        else if (event_key.key_code == 65) {
            this->w_camera_pos[0] -= 0.01f;
        }
        else if (event_key.key_code == 68) {
            this->w_camera_pos[0] += 0.01f;
        }
        else if (event_key.key_code == 256) {
            this->shutdown();
        }
    }

	void Window::on_update() 
	{
        glfwSwapBuffers(w_window);
        glfwPollEvents();
	}
}