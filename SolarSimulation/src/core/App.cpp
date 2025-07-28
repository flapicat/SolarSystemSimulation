#include "App.h"

App* App::s_Instance = nullptr;

App::App()
{
	s_Instance = this;
    Window::WindowData data = {1920, 1080, "Solar System Symulation"};
	m_window = std::make_unique<Window>(data);

	m_ImguiAPI.Init();

    std::vector<float> vertices = {
        // Front face (red)
        -0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   1.0f, 0.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 0.0f, 1.0f,

        // Back face (green)
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   0.0f, 1.0f, 0.0f, 1.0f,

        // Left face (blue)
        -0.5f, -0.5f, -0.5f,   0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,   0.0f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   0.0f, 0.0f, 1.0f, 1.0f,

        // Right face (yellow)
         0.5f, -0.5f,  0.5f,   1.0f, 1.0f, 0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   1.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 1.0f, 0.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 1.0f, 0.0f, 1.0f,
        
        // Top face (magenta)
        -0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,   1.0f, 0.0f, 1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,   1.0f, 0.0f, 1.0f, 1.0f,
        
        // Bottom face (cyan)
        -0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,   0.0f, 1.0f, 1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,   0.0f, 1.0f, 1.0f, 1.0f
    };

    std::vector<unsigned int> indices = {
        // Front face
        0, 1, 2, 2, 3, 0,
        // Back face
        4, 5, 6, 6, 7, 4,
        // Left face
        8, 9,10, 10,11,8,
        // Right face
        12,13,14, 14,15,12,
        // Top face
        16,17,18, 18,19,16,
        // Bottom face
        20,21,22, 22,23,20
    };

    m_Shader.reset(new Shader("assets/shaders/shader.vert","assets/shaders/shader.frag"));


    m_VA = std::make_shared<VertexArray>();
    std::shared_ptr<VertexBuffer> VB;
    VB.reset(new VertexBuffer(vertices.data(), vertices.size() * sizeof(float)));
    BufferLayout layout = {
        { ShaderDataType::FLOAT3, "a_Position" },
        { ShaderDataType::FLOAT4, "a_Color" }
    };
    VB->SetLayout(layout);
    m_VA->SetVertexBuffer(VB);

    std::shared_ptr<IndexBuffer>IB;
    IB.reset(new IndexBuffer(indices.data(), indices.size()));
    m_VA->SetIndexBuffer(IB);
}

App::~App()
{
    glfwTerminate();
}

void App::Run()
{
    while (!glfwWindowShouldClose(m_window->GetNativeWindow()))
    {
        glClearColor(0.1f, 0.1f, 0.15f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        m_Shader->Use();
        m_VA->Bind();
        glDrawElements(GL_TRIANGLES, m_VA->GetIndexBuffers()->GetCount(), GL_UNSIGNED_INT, 0);

        m_ImguiAPI.Begin();
        ImGui::Begin("ImGui window title");
        ImGui::Text("ImGui window");
        ImGui::End();
        m_ImguiAPI.End();

        m_window->update();
    }
}
