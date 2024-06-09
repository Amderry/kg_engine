#include <core/Input.hpp>

namespace engine_core
{
	bool Input::keys_pressed[348] = {};
	double Input::mouse_position[2] = { 0 };

	bool Input::is_key_pressed(const int key_code)
	{
		return keys_pressed[key_code < 348 && key_code >= 0 ? key_code : 0];
	}

	void Input::press_key(const int key_code)
	{
		if (key_code < 348 && key_code >= 0)
		{
			keys_pressed[key_code] = true;
		}
	}

	void Input::release_key(const int key_code)
	{
		if (key_code < 348 && key_code >= 0)
		{
			keys_pressed[key_code] = false;
		}
	}
	void Input::move_mouse(const double x, const double y)
	{
		mouse_position[0] = x;
		mouse_position[1] = y;
	}
}