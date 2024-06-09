#pragma once
#include <array>
#include <functional>

namespace engine_core 
{
	enum class Event_Type
	{
		window_resize = 0,
		window_close,

		key_pressed,
		key_released,

		mouse_button_pressed,
		mouse_button_released,
		mouse_moved,

		events_count
	};

	struct Base_Event
	{
		virtual ~Base_Event() = default;
		virtual Event_Type get_type() const = 0;
	};

	class Event_Dispatcher
	{
	public:
		template <typename Event_Type_Template>
		void add_event_listener(std::function<void(Event_Type_Template&)> callback)
		{
			auto base_callback = [func = std::move(callback)](Base_Event& e)
				{
					if (e.get_type() == Event_Type_Template::type)
					{
						func(static_cast<Event_Type_Template&>(e));
					}
				};
			this->m_event_callbacks[static_cast<size_t>(Event_Type_Template::type)] = std::move(base_callback);
		}

		void dispatch(Base_Event& event)
		{
			auto& callback = this->m_event_callbacks[static_cast<size_t>(event.get_type())];
			if (callback)
			{
				callback(event);
			}
		}
	private:
		std::array<std::function<void(Base_Event&)>, static_cast<size_t>(Event_Type::events_count)> m_event_callbacks;
	};

	struct Event_Mouse_Moved : public Base_Event
	{
		Event_Mouse_Moved(double n_x, double n_y) : x(n_x), y(n_y)
		{
		}

		virtual Event_Type get_type() const override
		{
			return type;
		}

		double x;
		double y;

		static const Event_Type type = Event_Type::mouse_moved;
	};

	struct Event_Window_Resize : public Base_Event
	{
		Event_Window_Resize(int n_width, int n_height) : width(n_width), height(n_height)
		{
		}

		virtual Event_Type get_type() const override
		{
			return type;
		}

		int width;
		int height;

		static const Event_Type type = Event_Type::window_resize;
	};

	struct Event_Window_Close : public Base_Event
	{
		virtual Event_Type get_type() const override
		{
			return type;
		}

		static const Event_Type type = Event_Type::window_close;
	};

	struct Event_Key_Pressed : public Base_Event
	{
		Event_Key_Pressed(int key_code) : key_code(key_code)
		{
		}

		virtual Event_Type get_type() const override
		{
			return type;
		}

		int key_code;

		static const Event_Type type = Event_Type::key_pressed;
	};

	struct Event_Key_Released : public Base_Event
	{
		Event_Key_Released(int key_code) : key_code(key_code)
		{
		}

		virtual Event_Type get_type() const override
		{
			return type;
		}

		int key_code;

		static const Event_Type type = Event_Type::key_released;
	};

	struct Event_Mouse_Button_Pressed : public Base_Event
	{
		Event_Mouse_Button_Pressed(const int key_code) : key_code(key_code)
		{
		}

		virtual Event_Type get_type() const override
		{
			return type;
		}

		int key_code;

		static const Event_Type type = Event_Type::mouse_button_pressed;
	};
}