#pragma once

struct GLFWwindow;

namespace engine_core
{
	class Vertex_Array;

	class Renderer_OpenGL
	{
	public:
		static bool init(GLFWwindow* p_window);

		static void draw(const Vertex_Array& v_array);
		static void set_clear_color(const float r, const float g, const float b, const float a);
		static void clear();
		static void set_viewport(const unsigned int width, const unsigned int height, const unsigned int left_offset = 0, const unsigned int bottom_offset = 0);

		static const char* get_vendor_string();
		static const char* get_renderer_string();
		static const char* get_version_string();
	};
}