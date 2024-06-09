#include <core/Rendering/OpenGL/Renderer.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <core/rendering/OpenGL/VertexArray.hpp>
#include <core/Log.hpp>

namespace engine_core
{
	bool Renderer_OpenGL::init(GLFWwindow* p_window)
	{
		glfwMakeContextCurrent(p_window);

		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			log("Unable to initialize GLAD");
			return false;
		}

		log("GLFW context initialized");
		log("Vendor: ", get_vendor_string());
		log("Renderer: ", get_renderer_string());
		log("Version: ", get_version_string());

		return true;
	}

	void Renderer_OpenGL::draw(const Vertex_Array& v_array)
	{
		v_array.bind();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(v_array.get_indicies_count()), GL_UNSIGNED_INT, nullptr);
	}

	void Renderer_OpenGL::set_clear_color(const float r, const float g, const float b, const float a)
	{
		glClearColor(r, g, b, a);
	}

	void Renderer_OpenGL::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Renderer_OpenGL::set_viewport(const unsigned int width, const unsigned int height, const unsigned int left_offset, const unsigned int bottom_offset)
	{
		glViewport(left_offset, bottom_offset, width, height);
	}

	const char* Renderer_OpenGL::get_vendor_string()
	{
		return reinterpret_cast<const char*>(glGetString(GL_VENDOR));
	}

	const char* Renderer_OpenGL::get_renderer_string()
	{
		return reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	}

	const char* Renderer_OpenGL::get_version_string()
	{
		return reinterpret_cast<const char*>(glGetString(GL_VERSION));
	}
}