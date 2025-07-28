#include "VertexArray.h"

#include <glad/glad.h>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &m_RendererID);
}

VertexArray::~VertexArray()
{
	Delete();
}

void VertexArray::Bind()
{
	glBindVertexArray(m_RendererID);
}

void VertexArray::Unbind()
{
	glBindVertexArray(0);
}

void VertexArray::Delete()
{
	glDeleteVertexArrays(1, &m_RendererID);
}

void VertexArray::SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
{
	ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex buffer has no layout!");
	
	glBindVertexArray(m_RendererID);
	vertexBuffer->Bind();

	unsigned int index = 0;
	const auto& layout = vertexBuffer->GetLayout();
	for (const auto& element : layout)
	{
		glEnableVertexAttribArray(index);
		glVertexAttribPointer(index,
			element.GetComponentCount(),
			ShaderDataTypeToOpenGLBaseType(element.m_Type),
			element.GetNormalized(),
			layout.GetStride(),
			(const void*)element.m_Offset);
		index++;
	}

	m_vertexBuffer = vertexBuffer;
}

void VertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
{
	glBindVertexArray(m_RendererID);
	indexBuffer->Bind();
	m_indexBuffer = indexBuffer;
}
