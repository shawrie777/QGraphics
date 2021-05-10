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

		bool defaultShader;
		bool defaultMaterial = true;

		Shader* shader;
		Material* material;
	public:
		VertexBuffer vertices;
		IndexBuffer indices;

		Asset(): shader(new Shader), material(new Material), defaultShader(true){};
		Asset(VertexBuffer& VB, IndexBuffer& IB, Shader& S): vertices(VB), indices(IB), shader(&S), material(new Material), defaultShader(false) {};
		Asset(VertexBuffer& VB, IndexBuffer& IB): vertices(VB), indices(IB), shader(new Shader), material(new Material), defaultShader(false) {};
		~Asset();

		Shader* getShader() const { return shader; };

		void setShader(Shader* S) { 
			defaultShader = false;
			delete shader;
			shader = S; 
		};
		void setShader(Shader S) { setShader(&S); };

		Material* getMaterial() const { return material; };

		void setMaterial(Material* M) {
			defaultMaterial = false;
			delete material;
			material = M;
		};
		void setMaterial(Material M) { setMaterial(&M); };

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