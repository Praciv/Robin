#include "rbpch.h"
#include "imgui_layer.h"

#include "imgui.h"

#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

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
		// setup ImGui Context 
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		// setup imgui style 
		ImGui::StyleColorsDark();
	
		// when viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones 
		ImGuiStyle& style = ImGui::GetStyle();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		application& app = application::get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.get_window().get_native_window());
	
		// setup renderer bindins 
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 450");
	}

	void imgui_layer::on_detach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void imgui_layer::on_imgui_render()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}

	void imgui_layer::begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void imgui_layer::end()
	{
		ImGuiIO& io = ImGui::GetIO();
		application& app = application::get();
		io.DisplaySize = ImVec2(app.get_window().get_width(), app.get_window().get_height());

		// rendering 
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}
}