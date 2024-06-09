#pragma once 

namespace engine_core
{
	class Input
	{
	public:
		static bool is_key_pressed(const int key_code);
		static void press_key(const int key_code);
		static void release_key(const int key_code);
		static void move_mouse(const double x, const double y);
		static double get_mouse_x() { return mouse_position[0]; }
		static double get_mouse_y() { return mouse_position[1]; }
	private:
		static bool keys_pressed[348];
		static double mouse_position[2];
	};
}