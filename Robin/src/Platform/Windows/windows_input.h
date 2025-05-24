#pragma once

#include "Robin/core.h"
#include "Robin/input.h"

namespace Robin
{
	class windows_input : public input
	{
	protected:
		virtual bool is_key_pressed_implementation(int key_code) override;
		virtual bool is_mouse_button_pressed_implementation(int button) override;
		virtual std::pair<float, float> get_mouse_position_implementation() override;
		virtual float get_mouse_x_implementation() override;
		virtual float get_mouse_y_implementation() override;
	};
}

