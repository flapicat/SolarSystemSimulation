#pragma once

#include "common.h"
#include "ImGui/ImGuiAPI.h"
#include "Window.h"

#include "renderer/VertexArray.h"
#include "renderer/Buffer.h"
#include "renderer/Shader.h"

class App
{
public:
	App();
	~App();
	void Run();

	static App* Get() { return s_Instance; };
	Window& GetWidndow() { return *m_window; }

private:
	static App* s_Instance;
	std::unique_ptr<Window> m_window;
	ImGuiAPI m_ImguiAPI;

	std::unique_ptr<Shader> m_Shader;
	std::shared_ptr<VertexArray> m_VA;
};

