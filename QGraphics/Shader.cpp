#include "Shader.h"
#include <fstream>
#include <sstream>

namespace QG
{
	Shader::Shader() : Shader("F:/C++/QGraphics/QGraphics/Vertex.txt","F:/C++/QGraphics/QGraphics/Frag.txt")
	{		
	}

    Shader::Shader(const char* vertexPath, const char* fragmentPath)
    {
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;

		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();

			vShaderFile.close();
			fShaderFile.close();

			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR Shader file not succesfully read" << std::endl;
		}
		const char* vShaderCode = vertexCode.c_str();
		const char* fShaderCode = fragmentCode.c_str();


		unsigned int vertex, fragment;
		int success;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR: Shader::Vertex compilation failed/n" << infoLog << std::endl;
		};

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "ERROR: Shader::Fragment compilation failed/n" << infoLog << std::endl;
		}

		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR: Shader::Linking failed/n" << infoLog << std::endl;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

    Shader::~Shader()
    {
		glDeleteProgram(ID);
    }

    void Shader::use()
    {
		glUseProgram(ID);
    }

    void Shader::setBool(const std::string& name, bool value) const
    {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }

    void Shader::setInt(const std::string& name, int value) const
    {
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }

    void Shader::setUInt(const std::string& name, unsigned int value) const
    {
		glUniform1f(glGetUniformLocation(ID, name.c_str()), (GLfloat)value);
    }

    void Shader::setFloat(const std::string& name, float value) const
    {
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1)
			throw("Uniform not found");
		glUniform1f(loc, value);
    }

    void Shader::setDouble(const std::string& name, double value) const
    {
		glUniform1d(glGetUniformLocation(ID, name.c_str()), value);
    }

}