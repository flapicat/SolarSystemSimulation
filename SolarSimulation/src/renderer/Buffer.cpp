#include "Buffer.h"

#include <glad/glad.h>

VertexBuffer::VertexBuffer(float* vertices, unsigned int size)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VertexBuffer::~VertexBuffer()
{
	Delete();
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::Delete()
{
	glDeleteBuffers(1, &m_RendererID);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

IndexBuffer::IndexBuffer(unsigned int* indices, unsigned int count)
	:m_count(count)
{
	glGenBuffers(1, &m_RendererID);
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
	glBufferData(GL_ARRAY_BUFFER, count * sizeof(unsigned int), indices, GL_STATIC_DRAW);
}

IndexBuffer::~IndexBuffer()
{
	Delete();
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IndexBuffer::Delete()
{
	glDeleteBuffers(1, &m_RendererID);
}
