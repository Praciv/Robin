#include "rbpch.h"
#include "imgui_layer.h"

#include "imgui.h"
#include "Platform/OpenGL/imgui_opengl_renderer.h"
#include "GLFW/glfw3.h"

#include "Robin/application.h"

// TEMPORARY
#include <GLFW/glfw3.h>
#include <GLAD/glad.h>


namespace Robin
{
	imgui_layer::imgui_layer()
		: layer("imgui_layer")
	{

	}

	imgui_layer::~imgui_layer()
	{

	}

	void imgui_layer::on_attach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// TEMPORARY: should eventually use Hazel key codes
		io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
		io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
		io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
		io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
		io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
		io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
		io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
		io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
		io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
		io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
		io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
		io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
		io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
		io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
		io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
		io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
		io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
		io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
		io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
		io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
		io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

		ImGui_ImplOpenGL3_Init("#version 450");
	}

	void imgui_layer::on_detach()
	{

	}

	void imgui_layer::on_update()
	{
		ImGuiIO& io = ImGui::GetIO();
		application& app = application::get();
		io.DisplaySize = ImVec2(app.get_window().get_width(), app.get_window().get_height());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_time > 0.0f ? (time - m_time) : (1.0f / 60.0f);
		m_time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void imgui_layer::on_event(event& event)
	{
		event_dispatcher dispatcher(event);

		dispatcher.dispatch<mouse_button_pressed_event>(RB_BIND_EVENT_FN(imgui_layer::on_mouse_button_pressed_event));
		dispatcher.dispatch<mouse_button_released_event>(RB_BIND_EVENT_FN(imgui_layer::on_mouse_button_released_event));
		dispatcher.dispatch<mouse_moved_event>(RB_BIND_EVENT_FN(imgui_layer::on_mouse_moved_event));
		dispatcher.dispatch<mouse_scrolled_event>(RB_BIND_EVENT_FN(imgui_layer::on_mouse_scrolled_event));
		dispatcher.dispatch<key_pressed_event>(RB_BIND_EVENT_FN(imgui_layer::on_key_pressed_event));
		dispatcher.dispatch<key_released_event>(RB_BIND_EVENT_FN(imgui_layer::on_key_released_event));
		dispatcher.dispatch<key_typed_event>(RB_BIND_EVENT_FN(imgui_layer::on_key_typed_event));
		dispatcher.dispatch<window_resize_event>(RB_BIND_EVENT_FN(imgui_layer::on_window_resized_event));

	}

	bool imgui_layer::on_mouse_button_pressed_event(mouse_button_pressed_event& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.get_mouse_button(), true);

		return false;
	}
	bool imgui_layer::on_mouse_button_released_event(mouse_button_released_event& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(e.get_mouse_button(), false);
		
		return false;
	}
	bool imgui_layer::on_mouse_moved_event(mouse_moved_event& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent(e.get_x(), e.get_y());
		
		return false;
	}
	bool imgui_layer::on_mouse_scrolled_event(mouse_scrolled_event& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent(e.get_x_offset(), e.get_y_offset());

		return false;
	}
	bool imgui_layer::on_key_pressed_event(key_pressed_event& e)
	{
		//TODO: MAKE A MY KEYCODE TO IMGUI KEYCODE CONVERTER
		//TODO: THEN IMPLEMENT MOFIFIERS E.G SHIFT

		ImGuiIO& io = ImGui::GetIO();
		//io.AddKeyEvent(e.get_key_code(), true);
		return false;
	}
	bool imgui_layer::on_key_released_event(key_released_event& e)
	{
		//TODO: MAKE A MY KEYCODE TO IMGUI KEYCODE CONVERTER
		//TODO: THEN IMPLEMENT MOFIFIERS E.G SHIFT

		ImGuiIO& io = ImGui::GetIO();
		//io.AddKeyEvent(e.get_key_code(), false);
		return false;
	}

	bool imgui_layer::on_key_typed_event(key_typed_event& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int key_code = e.get_key_code();
		if (key_code > 0 && key_code < 0x10000)
			io.AddInputCharacter((unsigned short)key_code);

		return false; 
	}

	bool imgui_layer::on_window_resized_event(window_resize_event& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2(e.get_width(), e.get_height());
		io.DisplayFramebufferScale;

		glViewport(0, 0, e.get_width(), e.get_height());

		return false;
	}
}