#pragma once

#include <imgui/imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class ImGuiAPI
{
public:
	ImGuiAPI() = default;
	~ImGuiAPI();
	void Init();
	void Close();

	void Begin();
	void End();
};

