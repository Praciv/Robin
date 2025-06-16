#include "rbpch.h"
#include "windows_input.h"

#include "Robin/Core/application.h"
#include <GLFW/glfw3.h>

namespace Robin
{
    input* input::s_instance = new windows_input();

    bool windows_input::is_key_pressed_implementation(int key_code)
    {
        auto window = static_cast<GLFWwindow*>(application::get().get_window().get_native_window());
        auto state = glfwGetKey(window, key_code);
        
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
    bool windows_input::is_mouse_button_pressed_implementation(int button)
    {
        auto window = static_cast<GLFWwindow*>(application::get().get_window().get_native_window());
        auto state = glfwGetMouseButton(window, button);

        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }
    std::pair<float, float> windows_input::get_mouse_position_implementation()
    {
        auto window = static_cast<GLFWwindow*>(application::get().get_window().get_native_window());
        double x_pos, y_pos;
        glfwGetCursorPos(window, &x_pos, &y_pos);

        return std::pair<float, float>((float)x_pos, (float)y_pos);
    }
    float windows_input::get_mouse_x_implementation()
    {
        auto [x, y] = get_mouse_position_implementation();
        return x;
    }
    float windows_input::get_mouse_y_implementation()
    {
        auto [x, y] = get_mouse_position_implementation();
        return y;
    }
}
