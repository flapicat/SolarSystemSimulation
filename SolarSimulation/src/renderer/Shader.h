#pragma once

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include<string>
#include<fstream>
#include<sstream>
#include<iostream>


class Shader
{
public:
	Shader(const char* vertexShader, const char* fragmentShader);
	void Use();
	void Terminate();

	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

	//----------------------------------------------------------------------------

	void setVec2(const std::string& name, const glm::vec2 value) const;
	void setVec2(const std::string& name, float x, float y) const;

	//----------------------------------------------------------------------------

	void setVec3(const std::string& name, const glm::vec3 value) const;
	void setVec3(const std::string& name, float x, float y, float z) const;

	//----------------------------------------------------------------------------

	void setVec4(const std::string& name, const glm::vec4 value) const;
	void setVec4(const std::string& name, float x, float y, float z, float w) const;

	//----------------------------------------------------------------------------

	void setMat2(const std::string& name, const glm::mat2& mat) const;
	void setMat3(const std::string& name, const glm::mat3& mat) const;
	void setMat4(const std::string& name, const glm::mat4& mat) const;
private:
	unsigned int m_RendererID;
	void checkCompileErrors(GLuint shader, std::string type);

};
