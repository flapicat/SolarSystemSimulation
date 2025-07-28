#include "Shader.h"

Shader::Shader(const char* vertexShader, const char* fragmentShader)
{
	std::string vertexCode;
	std::ifstream vShaderFile;
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		vShaderFile.open(vertexShader);
		std::stringstream vShaderStream;
		vShaderStream << vShaderFile.rdbuf();
		vShaderFile.close();
		vertexCode = vShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << vertexShader << "\n";
	}

	std::string fragmentCode;
	std::ifstream fShaderFile;
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		fShaderFile.open(fragmentShader);
		std::stringstream fShaderStream;
		fShaderStream << fShaderFile.rdbuf();
		fShaderFile.close();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cerr << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << fragmentShader << "\n";
	}

	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();

	unsigned int vertex, fragment;
	int success;
	char infoLog[1024];

	//vertex
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertex, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED: " << vertexShader << "\n" << infoLog << "\n";
	}

	//fragment
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragment, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED: " << fragmentShader << "\n" << infoLog << "\n";
	}

	//Shader program
	m_RendererID = glCreateProgram();
	glAttachShader(m_RendererID, vertex);
	glAttachShader(m_RendererID, fragment);
	glLinkProgram(m_RendererID);
	glGetProgramiv(m_RendererID, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_RendererID, 512, NULL, infoLog);
		std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << "\n";
	}
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

void Shader::Use()
{
    glUseProgram(m_RendererID);
}

void Shader::Terminate()
{
    glDeleteProgram(m_RendererID);
}

void Shader::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
	glUniform1i(glGetUniformLocation(m_RendererID, name.c_str()), (int)value);
}

void Shader::setFloat(const std::string& name, float value) const
{
	glUniform1f(glGetUniformLocation(m_RendererID, name.c_str()), (int)value);
}

void Shader::setVec2(const std::string& name, const glm::vec2 value) const
{
	glUniform2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, &value[0]);
}

void Shader::setVec2(const std::string& name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(m_RendererID, name.c_str()), x, y);
}

void Shader::setVec3(const std::string& name, const glm::vec3 value) const
{
	glUniform3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, &value[0]);
}

void Shader::setVec3(const std::string& name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z);
}

void Shader::setVec4(const std::string& name, const glm::vec4 value) const
{
	glUniform4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, &value[0]);
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
	glUniform4f(glGetUniformLocation(m_RendererID, name.c_str()), x, y, z, w);
}

void Shader::setMat2(const std::string& name, const glm::mat2& mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat3(const std::string& name, const glm::mat3& mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setMat4(const std::string& name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(m_RendererID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void Shader::checkCompileErrors(GLuint shader, std::string type)
{
	GLint success;
	GLchar infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cerr << "ERROR::SHADER_COMPILATION_ERROR of type: {0}\n {1} -------------------------------------------------------\n";
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cerr << "ERROR::PROGRAM_LINKING_ERROR of type: {0}\n {1} -------------------------------------------------------\n";
			}
		}
	}
}
