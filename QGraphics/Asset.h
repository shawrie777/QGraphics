#pragma once
#include "Vertex Buffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include "Curve.h"

namespace QG
{
	class Asset
	{
		friend class AssetGroup;
	protected:
		QM::matrix<4, 4> scale = QM::identity<4>();
		QM::Quaternion rotation{ 1,0,0,0 };
		QM::vector<3> position{ 0.0f,0.0f,0.0f };
		bool built = false;
		bool m_shown = true;
		bool changed = true;
		GLenum drawType = GL_TRIANGLES;

		bool defaultShader;
		bool defaultMaterial = true;

		bool grouped = false;

		Shader* shader;
		Material* material;
		std::shared_ptr<Curve> curve = nullptr;

		QM::vector<3> Lbound{ 1.0f,1.0f,1.0f };
		QM::vector<3> Ubound{ -1.0f,-1.0f,-1.0f };
	public:
		VertexBuffer vertices;
		IndexBuffer indices;

		//Create default empty asset
		//no vertices, indices or texture coordinates
		//comes with default grey material and shader
		//generally not needed, use derived classes instead
		Asset();

		//Create asset with existing vertex buffer, index buffer and shader
		//generally not needed, use derived classes instead
		Asset(VertexBuffer& VB, IndexBuffer& IB, Shader& S);

		//Create asset with existing vertex buffer and index buffer but default shader
		//generally not needed, use derived classes instead
		Asset(VertexBuffer& VB, IndexBuffer& IB);

		//load an asset using a Collada (.dae) file
		Asset(const std::string filepath);
		~Asset();

		//get pointer to this objects shader
		Shader* getShader() const;

		//set Shader for this object
		void setShader(Shader* S);

		//get pointer to this objects material
		Material* getMaterial() const;

		//set Material for this object
		void setMaterial(Material* M);

		//assign a curve for this object to follow
		//when the curves end time is reached, this will be set back to null
		//a curve can be followed indefinitely by setting the end time to INFINITE
		void setCurve(Curve& c);

		//build the index and vertex arrays for the object
		//should not need calling directly, for internal use
		virtual void build();

		//draw this object for the next frame
		//should not need calling directly
		//called by Window::Render
		virtual void draw();
		
		//get the model matrix for this object
		//accounts for scale, rotation and translation
		virtual QM::matrix<4, 4, float> modelMatrix();
		
		//set the scale equally in each direction
		virtual void setScale(float SF);
		//set the scale on each axis independently
		virtual void setScale(float x, float y, float z);
		//set the scale on each axis independently
		virtual void setScale(QM::vector<3> SF);
		//stretch the object in the given direction
		virtual void setScale(float SF, QM::vector<3> direction);
		//get the current scale on each axis, as a matrix
		virtual QM::matrix<4,4> getScale();

		//rescale equally in each direction, accounting for existing scale
		virtual void changeScale(float SF);
		//rescale on each axis independently, accounting for existing scale
		virtual void changeScale(float x, float y, float z);
		//rescale on each axis independently, accounting for existing scale
		virtual void changeScale(QM::vector<3> SF);
		//add a stretch to the object in the given direction
		virtual void changeScale(float SF, QM::vector<3> direction);

		//set rotation using Euler angles
		virtual void setRotation(double xAngle, double yAngle, double zAngle);
		//set rotation using an angle and axis
		//the rotation is clockwise, looking down the axis
		virtual void setRotation(float angle, QM::vector<3> axis);
		//set rotation using a unit quaternion
		virtual void setRotation(QM::Quaternion Q);
		//get the current rotation, as a quaternion
		virtual QM::Quaternion getRotation();

		//add a subsequent rotation using Euler angles
		virtual void changeRotation(double xAngle, double yAngle, double zAngle);
		//add a subsequent rotation using an angle and axis
		//the rotation is clockwise, looking down the axis
		virtual void changeRotation(float angle, QM::vector<3> axis);
		//add a subsequent rotation using a unit quaternion
		virtual void changeRotation(QM::Quaternion Q);

		//set the position of the asset
		virtual void setPosition(float x, float y, float z);
		//set the position of the asset using a vector
		virtual void setPosition(QM::vector<3> R);
		//get the current position
		virtual QM::vector<3> getPosition();

		//change the existing position by the given values
		virtual void move(float x, float y, float z);
		//change the existing position by the given values
		virtual void move(QM::vector<3> R);

		//check if the asset is currently visible
		bool isShown() const;
		//show the asset in future frames
		void show();
		//hide the asset in future frames
		void hide();
		//check if the asset is part of an assetGroup
		bool isGrouped() const;

		//check the draw type of the asset
		//generally for internal use
		GLenum getDrawType() const;

		//invert the normals of an object so that the inside is lit, instead of out
		//useful if the object will be viewed from inside, e.g. a room
		void insideOut();

		//internal function used to check if a mouse click intersects with the object
		//and the distance from the camera if it does
		//this can be compared to other objects to work out what is clicked on
		float interceptTime(QM::vector<3> rayOrigin, QM::vector<3> direction);

		//determines the action taken when this object is clicked on
		//the pointed-to function should check the mouseAction members
		//to make sure the action only happens in the right case
		void(*OnClick)(QG::Asset* asset, mouseAction action) = nullptr;

		//check if the asset is currently following a curve
		bool hasCurve();

		//test if two objects overlap
		bool collides(Asset* asset);
	};

}

namespace Assets
{
	extern std::vector<QG::Asset*> assets;
}