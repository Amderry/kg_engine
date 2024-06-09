#pragma once
#include <core/Event.hpp>
#include <string>
#include <functional>
#include <core/rendering/OpenGL/ShaderProgram.hpp>
#include <core/rendering/OpenGL/VertexBuffer.hpp>
#include <core/rendering/OpenGL/VertexArray.hpp>
#include <core/rendering/OpenGL/IndexBuffer.hpp>
#include <core/Camera.hpp>
#include <memory>

struct GLFWwindow;

namespace engine_core
{

	class Window
	{
	public:
		using event_callback = std::function<void(Base_Event&)>;

		Window(std::string title, const unsigned int width, const unsigned int height);
		virtual ~Window();

		Window(const Window&) = delete;
		Window(Window&&) = delete;
		Window& operator=(const Window&) = delete;
		Window& operator=(Window&&) = delete;

		void on_update();

		unsigned int get_width() const { return this->w_data.w_width; }
		unsigned int get_height() const { return this->w_data.w_height; }

		void set_mouse_pos(Event_Mouse_Moved event_mouse);
		void handle_key(Event_Key_Pressed event_key);

		void set_event_callback(const event_callback& callback) 
		{
			w_data.event_callback_fn = callback;
		}

	private:
		struct Window_data
		{
			std::string w_title;
			unsigned int w_width;
			unsigned int w_height;
			event_callback event_callback_fn;
		};

		GLFWwindow* w_window = nullptr;
		Window_data w_data;
		double w_mouse_pos[2]{ 0.f, 0.f };
		float w_camera_pos[3]{ 0.f, 0.f, 1.0f };

		int init();
		void shutdown();
	};

}