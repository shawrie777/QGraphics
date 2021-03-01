#pragma once

#include "Core.h"

namespace QG
{

	class Shader
	{
	private:
		unsigned int ID;
	public:
		//Creates default shader
		Shader();

		Shader(const char* vertexPath, const char* fragmentPath);
		~Shader();

		void use();

		void setBool(const std::string& name, bool value) const;
		void setInt(const std::string& name, int value) const;
		void setUInt(const std::string& name, unsigned int value) const;
		void setFloat(const std::string& name, float value) const;
		void setDouble(const std::string& name, double value) const;

		template <int rows, int cols, typename scalar = float>
		void setMatrix(const std::string& name, QM::matrix<rows, cols, scalar> value);

		template <int size, typename scalar = float>
		void setVector(const std::string& name, QM::vector<size, scalar> value) const;
	};

	template<int rows, int cols, typename scalar>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<rows, cols, scalar> value)
	{
		throw("Template specialisation failed.");
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 2, float> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1)
			throw("Uniform not found");
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 2, int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1)
			throw("Uniform not found");
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 2, unsigned int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1)
			throw("Uniform not found");
		glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 2, double> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1)
			throw("Uniform not found");
		glUniformMatrix2dv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 3, float> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc==-1)
			throw("Uniform not found");

		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 3, int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1)
			throw("Uniform not found");
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 3, unsigned int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1)
			throw("Uniform not found");
		glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 3, double> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1)
			throw("Uniform not found");
		glUniformMatrix3dv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 4, float> value)
	{
		auto temp = name.c_str();
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1)
			throw("Uniform not found");
		glUniformMatrix4fv(loc, 1, GL_TRUE, value.pointer());		
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 4, int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1)
			throw("Uniform not found");
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 4, unsigned int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc == -1)
			throw("Uniform not found");
		glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 4, double> value)
	{
		glUniformMatrix4dv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 3, float> value)
	{
		glUniformMatrix3x2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 3, int> value)
	{
		glUniformMatrix3x2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 3, unsigned int> value)
	{
		glUniformMatrix3x2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 3, double> value)
	{
		glUniformMatrix3x2dv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 4, float> value)
	{
		glUniformMatrix4x2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 4, int> value)
	{
		glUniformMatrix4x2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 4, unsigned int> value)
	{
		glUniformMatrix4x2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 4, double> value)
	{
		glUniformMatrix4x2dv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 2, float> value)
	{
		glUniformMatrix2x3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 2, int> value)
	{
		glUniformMatrix2x3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 2, unsigned int> value)
	{
		glUniformMatrix2x3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 2, double> value)
	{
		glUniformMatrix2x3dv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 4, float> value)
	{
		glUniformMatrix4x3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 4, int> value)
	{
		glUniformMatrix4x3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 4, unsigned int> value)
	{
		glUniformMatrix4x3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 4, double> value)
	{
		glUniformMatrix4x3dv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 2, float> value)
	{
		glUniformMatrix2x4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 2, int> value)
	{
		glUniformMatrix2x4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 2, unsigned int> value)
	{
		glUniformMatrix2x4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 2, double> value)
	{
		glUniformMatrix2x4dv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 3, float> value)
	{
		glUniformMatrix3x4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 3, int> value)
	{
		glUniformMatrix3x4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 3, unsigned int> value)
	{
		glUniformMatrix3x4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 3, double> value)
	{
		glUniformMatrix3x4dv(glGetUniformLocation(ID, name.c_str()), 1, GL_TRUE, value.pointer());
	}

	template<int size, typename scalar>
	inline void Shader::setVector(const std::string& name, QM::vector<size, scalar> value) const
	{
		throw("Template specialisation failed");
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<2, float> value) const
	{
		glUniform2f(glGetUniformLocation(ID, name.c_str()), value.get(1), value.get(2));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<2, int> value) const
	{
		glUniform2i(glGetUniformLocation(ID, name.c_str()), value.get(1), value.get(2));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<2, unsigned int> value) const
	{
		glUniform2ui(glGetUniformLocation(ID, name.c_str()), value.get(1), value.get(2));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<2, double> value) const
	{
		glUniform2d(glGetUniformLocation(ID, name.c_str()), value.get(1), value.get(2));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<3, float> value) const
	{
		glUniform3f(glGetUniformLocation(ID, name.c_str()), value.get(1), value.get(2), value.get(3));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<3, int> value) const
	{
		glUniform3i(glGetUniformLocation(ID, name.c_str()), value.get(1), value.get(2), value.get(3));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<3, unsigned int> value) const
	{
		glUniform3ui(glGetUniformLocation(ID, name.c_str()), value.get(1), value.get(2), value.get(3));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<3, double> value) const
	{
		glUniform3d(glGetUniformLocation(ID, name.c_str()), value.get(1), value.get(2), value.get(3));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<4, float> value) const
	{
		glUniform4f(glGetUniformLocation(ID, name.c_str()), value.get(1), value.get(2), value.get(3), value.get(4));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<4, int> value) const
	{
		glUniform4i(glGetUniformLocation(ID, name.c_str()), value.get(1), value.get(2), value.get(3), value.get(4));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<4, unsigned int> value) const
	{
		glUniform4ui(glGetUniformLocation(ID, name.c_str()), value.get(1), value.get(2), value.get(3), value.get(4));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<4, double> value) const
	{
		glUniform4d(glGetUniformLocation(ID, name.c_str()), value.get(4), value.get(2), value.get(3), value.get(4));
	}
}