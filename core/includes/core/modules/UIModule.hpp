#pragma once

struct GLFWwindow;

namespace engine_core
{
	class UIModule
	{
	public:
		static void on_window_create(GLFWwindow* p_window);
		static void on_window_close();
		static void on_ui_draw_begin();
		static void on_ui_draw_end();
	};
}