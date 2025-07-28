#pragma once
#include "core/common.h"
#include <vector>

#include <glad/glad.h>

enum class ShaderDataType
{
	None,
	BOOL,
	INT, INT2, INT3, INT4,
	FLOAT, FLOAT2, FLOAT3, FLOAT4,
	MAT2, MAT3, MAT4
};

static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::FLOAT:     return GL_FLOAT;
	case ShaderDataType::FLOAT2:    return GL_FLOAT;
	case ShaderDataType::FLOAT3:    return GL_FLOAT;
	case ShaderDataType::FLOAT4:    return GL_FLOAT;
	case ShaderDataType::MAT2:		return GL_FLOAT;
	case ShaderDataType::MAT3:      return GL_FLOAT;
	case ShaderDataType::MAT4:      return GL_FLOAT;
	case ShaderDataType::INT:       return GL_INT;
	case ShaderDataType::INT2:      return GL_INT;
	case ShaderDataType::INT3:      return GL_INT;
	case ShaderDataType::INT4:      return GL_INT;
	case ShaderDataType::BOOL:      return GL_BOOL;
	}

	ASSERT(false, "Unknown ShaderDataType!");
	return 0;
}

static unsigned int DataTypeToSize(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::FLOAT:     return 4;
	case ShaderDataType::FLOAT2:    return 4 * 2;
	case ShaderDataType::FLOAT3:    return 4 * 3;
	case ShaderDataType::FLOAT4:    return 4 * 4;
	case ShaderDataType::MAT2:      return 4 * 2 * 2;
	case ShaderDataType::MAT3:      return 4 * 3 * 3;
	case ShaderDataType::MAT4:      return 4 * 4 * 4;
	case ShaderDataType::INT:       return 4;
	case ShaderDataType::INT2:      return 4 * 2;
	case ShaderDataType::INT3:      return 4 * 3;
	case ShaderDataType::INT4:      return 4 * 4;
	case ShaderDataType::BOOL:      return 1;
	}

	ASSERT(false, "Unknown ShaderDataType");

	return 0;
}

struct BufferElement
{
public:
	std::string m_name;
	ShaderDataType m_Type;
	unsigned int m_Offset;
	unsigned int m_Size;
	bool m_Normalized;

	BufferElement() {}
	BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
		:m_name(name), m_Type(type), m_Size(DataTypeToSize(type)), m_Offset(0), m_Normalized(normalized)
	{
	}

	GLenum GetNormalized() const { return m_Normalized ? GL_TRUE : GL_FALSE; }

	unsigned int GetComponentCount() const
	{
		switch (m_Type)
		{
		case ShaderDataType::FLOAT:     return 1;
		case ShaderDataType::FLOAT2:    return 2;
		case ShaderDataType::FLOAT3:    return 3;
		case ShaderDataType::FLOAT4:    return 4;
		case ShaderDataType::MAT2:      return 2 * 2;
		case ShaderDataType::MAT3:      return 3 * 3;
		case ShaderDataType::MAT4:      return 4 * 4;
		case ShaderDataType::INT:       return 1;
		case ShaderDataType::INT2:      return 2;
		case ShaderDataType::INT3:      return 3;
		case ShaderDataType::INT4:      return 4;
		case ShaderDataType::BOOL:      return 1;
		}

		ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}
	
};

class BufferLayout
{
public:
	BufferLayout(const std::initializer_list<BufferElement>& elements)
		:m_Elements(elements)
	{
		CalculateOffsetAndStride();
	}

	inline unsigned int GetStride() const { return m_Stride; };
	inline const std::vector<BufferElement>& GetElements() const { return m_Elements; }

	std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); };
	std::vector<BufferElement>::iterator end() { return m_Elements.end(); };
	std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); };
	std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); };
private:
	void CalculateOffsetAndStride()
	{
		unsigned int offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.m_Offset = offset;
			offset += element.m_Size;
			m_Stride += element.m_Size;
		}
	}
private:
	std::vector<BufferElement> m_Elements;
	unsigned int m_Stride = 0;
};


class VertexBuffer
{
public:
	VertexBuffer(float* vertices, unsigned int size);
	~VertexBuffer();
	void Bind();
	void Unbind();
	void Delete();

	const BufferLayout& GetLayout() const { return m_Layout; };
	void SetLayout(const BufferLayout& layout) { m_Layout = layout; };
private:
	unsigned int m_RendererID;
	BufferLayout m_Layout = {};
};



class IndexBuffer
{
public:
	IndexBuffer(unsigned int* indices, unsigned int count);
	~IndexBuffer();
	void Bind();
	void Unbind();
	void Delete();

	unsigned int GetCount() const { return m_count; };
private:
	unsigned int m_RendererID;
	unsigned int m_count;
};
