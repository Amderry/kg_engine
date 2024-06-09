#pragma once
#include <core/Event.hpp>
#include <memory>
#include <core/Camera.hpp>

namespace engine_core 
{

	class Application 
	{
	public:
		Application();
		virtual ~Application();

		Application(const Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;
		Application& operator=(Application&&) = delete;

		virtual int start(unsigned int w_width, unsigned int w_height, const char* title);
		virtual void on_update() {}
		virtual void on_ui_draw() {}

		Camera camera{ glm::vec3(0, 0, 0) };
		float camera_position[3] = { 0.0, 0.0, 0.0 };

		float camera_rotation[3] = { 0.0, 0.0, 0.0 };

		bool perspective_camera = true;
	private:
		Event_Dispatcher app_event_dispatcher;
		std::unique_ptr<class Window> app_window;
		bool is_close_window = false;
	};
}