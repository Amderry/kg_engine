#include <iostream>
#include <memory>
#include <core/Application.hpp>
#include <core/Log.hpp>
#include <imgui/imgui.h>
#include <core/Input.hpp>

class Engine_Editor : public engine_core::Application
{
	double initial_mouse_pos_x = .0f;
	double initial_mouse_pos_y = .0f;
	virtual void on_update() override
	{
		glm::vec3 movement_delta{ 0.f, 0.f, 0.f };
		glm::vec3 rotation_delta{ 0.f, 0.f, 0.f };
		if (engine_core::Input::is_key_pressed(87)) {
			movement_delta.x += 0.01f;
		}
		else if (engine_core::Input::is_key_pressed(83)) {
			movement_delta.x -= 0.01f;
		}
		else if (engine_core::Input::is_key_pressed(65)) {
			movement_delta.y += 0.01f;
		}
		else if (engine_core::Input::is_key_pressed(68)) {
			movement_delta.y -= 0.01f;
		}

		rotation_delta.z = initial_mouse_pos_x - engine_core::Input::get_mouse_x();
		rotation_delta.y = -(initial_mouse_pos_y - engine_core::Input::get_mouse_y());
		initial_mouse_pos_x = engine_core::Input::get_mouse_x();
		initial_mouse_pos_y = engine_core::Input::get_mouse_y();
		movement_delta.z = 0.0f;

		camera.add_movement_and_rotation(movement_delta, rotation_delta);
	}

	virtual void on_ui_draw() override
	{
		camera_position[0] = camera.get_camera_position().x;
		camera_position[1] = camera.get_camera_position().y;
		camera_position[2] = camera.get_camera_position().z;
		camera_rotation[0] = camera.get_camera_rotation().x;
		camera_rotation[1] = camera.get_camera_rotation().y;
		camera_rotation[2] = camera.get_camera_rotation().z;

		ImGui::Begin("Editor");
		if (ImGui::SliderFloat3("camera_position", camera_position, -10.0f, 10.0f))
		{
			camera.set_position(glm::vec3(camera_position[0], camera_position[1], camera_position[2]));
		}
		if (ImGui::SliderFloat3("camera_rotation", camera_rotation, 0.f, 60.0f))
		{
			camera.set_rotation(glm::vec3(camera_rotation[0], camera_rotation[1], camera_rotation[2]));
		}
		ImGui::Checkbox("Perspective_camera", &perspective_camera);
		ImGui::End();
	}

	int frame = 0;
};

int main() 
{
	auto editor = std::make_unique<Engine_Editor>();
	int width{ 1280 }, height{ 1024 };
	char title[]{ "Game" };

	int return_code = editor->start(width, height, title);

	return return_code;
}