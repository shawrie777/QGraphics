#pragma once

#include "Core.h"

namespace QG
{

	class Shader
	{
	private:
		unsigned int ID;
		unsigned int vertex, fragment, geometry;
		bool geo;
	public:
		//Creates default shader
		Shader();

		Shader(const char* vertexPath, const char* fragmentPath);

		//geometry shader optional
		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath);

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
		if (loc != -1)
			glUniformMatrix2fv(loc, 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 2, int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix2fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 2, unsigned int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix2fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 2, double> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix2dv(loc, 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 3, float> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix3fv(loc, 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 3, int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix3fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 3, unsigned int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix3fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 3, double> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix3dv(loc, 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 4, float> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix4fv(loc, 1, GL_TRUE, value.pointer());		
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 4, int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix4fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 4, unsigned int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix4fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 4, double> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix4dv(loc, 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 3, float> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix3x2fv(loc, 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 3, int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix3x2fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 3, unsigned int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix3x2fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 3, double> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix3x2dv(loc, 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 4, float> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix4x2fv(loc, 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 4, int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix4x2fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 4, unsigned int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix4x2fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<2, 4, double> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix4x2dv(loc, 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 2, float> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix2x3fv(loc, 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 2, int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix2x3fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 2, unsigned int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix2x3fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 2, double> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix2x3dv(loc, 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 4, float> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix4x3fv(loc, 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 4, int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix4x3fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 4, unsigned int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix4x3fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<3, 4, double> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix4x3dv(loc, 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 2, float> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix2x4fv(loc, 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 2, int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix2x4fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 2, unsigned int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix2x4fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 2, double> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix2x4dv(loc, 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 3, float> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix3x4fv(loc, 1, GL_TRUE, value.pointer());
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 3, int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix3x4fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 3, unsigned int> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniformMatrix3x4fv(loc, 1, GL_TRUE, (GLfloat*)(value.pointer()));
	}

	template<>
	inline void Shader::setMatrix(const std::string& name, QM::matrix<4, 3, double> value)
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
		glUniformMatrix3x4dv(loc, 1, GL_TRUE, value.pointer());
	}

	template<int size, typename scalar>
	inline void Shader::setVector(const std::string& name, QM::vector<size, scalar> value) const
	{
		throw("Template specialisation failed");
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<2, float> value) const
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniform2f(loc, value.get(1), value.get(2));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<2, int> value) const
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniform2i(loc, value.get(1), value.get(2));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<2, unsigned int> value) const
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniform2ui(loc, value.get(1), value.get(2));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<2, double> value) const
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniform2d(loc, value.get(1), value.get(2));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<3, float> value) const
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniform3f(loc, value.get(1), value.get(2), value.get(3));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<3, int> value) const
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniform3i(loc, value.get(1), value.get(2), value.get(3));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<3, unsigned int> value) const
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniform3ui(loc, value.get(1), value.get(2), value.get(3));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<3, double> value) const
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniform3d(loc, value.get(1), value.get(2), value.get(3));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<4, float> value) const
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniform4f(loc, value.get(1), value.get(2), value.get(3), value.get(4));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<4, int> value) const
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniform4i(loc, value.get(1), value.get(2), value.get(3), value.get(4));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<4, unsigned int> value) const
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniform4ui(loc, value.get(1), value.get(2), value.get(3), value.get(4));
	}

	template<>
	inline void Shader::setVector(const std::string& name, QM::vector<4, double> value) const
	{
		auto loc = glGetUniformLocation(ID, name.c_str());
		if (loc != -1)
			glUniform4d(loc, value.get(4), value.get(2), value.get(3), value.get(4));
	}
}