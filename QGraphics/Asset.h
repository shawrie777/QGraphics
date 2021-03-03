#pragma once
#include "Vertex Buffer.h"
#include "IndexBuffer.h"
#include "Shader.h"



namespace QG
{
	class Asset
	{
	protected:
		QM::vector<3> scale{ 1.0f,1.0f,1.0f };
		QM::Quaternion rotation{ 1,0,0,0 };
		QM::vector<3> position{ 0.0f,0.0f,0.0f };
		bool built = false;
		GLenum drawType = GL_TRIANGLES;
	public:
		VertexBuffer vertices;
		IndexBuffer indices;
		Shader* shader;
		Material* material;

		Asset(): shader(nullptr) {};
		Asset(VertexBuffer& VB, IndexBuffer& IB, Shader& S): vertices(VB), indices(IB), shader(&S) {};
		Asset(VertexBuffer& VB, IndexBuffer& IB): vertices(VB), indices(IB), shader() {};
		~Asset() {};

		virtual void build();

		void draw();
		
		virtual QM::matrix<4, 4, float> modelMatrix();
		
		virtual void setScale(float SF);
		virtual void setScale(float x, float y, float z);
		virtual void setScale(QM::vector<3> SF);
		virtual QM::vector<3> getScale();

		virtual void changeScale(float SF);
		virtual void changeScale(float x, float y, float z);
		virtual void changeScale(QM::vector<3> SF);

		virtual void setRotation(double xAngle, double yAngle, double zAngle);
		virtual void setRotation(float angle, QM::vector<3> axis);
		virtual void setRotation(QM::Quaternion Q);
		virtual QM::Quaternion getRotation();

		virtual void changeRotation(double xAngle, double yAngle, double zAngle);
		virtual void changeRotation(float angle, QM::vector<3> axis);
		virtual void changeRotation(QM::Quaternion Q);

		virtual void setPosition(float x, float y, float z);
		virtual void setPosition(QM::vector<3> R);
		virtual QM::vector<3> getPosition();

		virtual void move(float x, float y, float z);
		virtual void move(QM::vector<3> R);
	};

}