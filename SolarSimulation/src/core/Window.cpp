#include "Window.h"

Window::Window(WindowData& data)
{
    CreateWindow(data);
}

Window::~Window()
{
	DestroyWindow();
}

void Window::update()
{
    glfwPollEvents();
    glfwSwapBuffers(m_window);
}

void Window::CreateWindow(WindowData& data)
{
    m_windowData.width = data.width;
    m_windowData.height = data.height;
    m_windowData.Title = data.Title;

    ASSERT(glfwInit(), "Failed to initialize GLFW\n");

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    m_window = glfwCreateWindow(m_windowData.width, m_windowData.height, m_windowData.Title.c_str(), nullptr, nullptr);
    ASSERT(m_window, "Failed to create GLFW window\n");

    glfwMakeContextCurrent(m_window);
    glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);

    ASSERT(gladLoadGLLoader((GLADloadproc)glfwGetProcAddress), "Failed to initialize GLAD\n");
    glEnable(GL_DEPTH_TEST);
}

void Window::DestroyWindow()
{
	glfwDestroyWindow(m_window);
}

void Window::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
