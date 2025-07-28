#pragma once
#include <string>

#include<glad/glad.h>
#include <GLFW/glfw3.h>

#include "common.h"

class Window
{
public:
	struct WindowData
	{
		unsigned int width;
		unsigned int height;
		std::string Title;
	};
	Window(WindowData& data);
	~Window();

	void update();

	void CreateWindow(WindowData& data);
	void DestroyWindow();

	inline unsigned int GetWidth() { return m_windowData.width; }
	inline unsigned int GetHeight() { return m_windowData.height; }

	GLFWwindow* GetNativeWindow() { return m_window; }
private:
	GLFWwindow* m_window;

	WindowData m_windowData;
private:
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

