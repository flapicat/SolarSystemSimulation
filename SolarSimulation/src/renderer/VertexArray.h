#pragma once
#include <memory>
#include "Buffer.h"

class VertexArray
{
public:
	VertexArray();
	~VertexArray();
	void Bind();
	void Unbind();
	void Delete();

	void SetVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
	void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

	const std::shared_ptr<VertexBuffer>& GetVertexBuffers() const { return m_vertexBuffer; }
	const std::shared_ptr<IndexBuffer>& GetIndexBuffers() const { return m_indexBuffer; }
private:
	unsigned int m_RendererID;
	std::shared_ptr<VertexBuffer> m_vertexBuffer;
	std::shared_ptr<IndexBuffer> m_indexBuffer;
};

