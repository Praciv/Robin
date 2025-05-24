#pragma once

#include "Robin/core.h"

namespace Robin
{
	class ROBIN_API input
	{
	public:
		inline static bool is_key_pressed(int key_code) { return s_instance->is_key_pressed_implementation(key_code); }
		inline static bool is_mouse_button_pressed(int button) { return s_instance->is_mouse_button_pressed_implementation(button); }
		inline static std::pair<float, float> get_mouse_position() { return s_instance->get_mouse_position_implementation(); }
		inline static float get_mouse_x() { return s_instance->get_mouse_x_implementation(); }
		inline static float get_mouse_y() { return s_instance->get_mouse_y_implementation(); }

	protected:
		virtual bool is_key_pressed_implementation(int key_code) = 0;
		virtual bool is_mouse_button_pressed_implementation(int button) = 0;
		virtual std::pair<float, float> get_mouse_position_implementation() = 0;
		virtual float get_mouse_x_implementation() = 0;
		virtual float get_mouse_y_implementation() = 0;

	private:
		static input* s_instance;
	};
}