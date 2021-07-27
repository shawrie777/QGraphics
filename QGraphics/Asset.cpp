#include "Asset.h"
#include "Light.h"
#include <string>
#include "Window.h"
#include <algorithm>

namespace Assets
{
	std::vector<QG::Asset*> assets;
}

namespace QG
{
	Asset::Asset() : shader(new Shader), material(new Material), defaultShader(true)
	{
		Assets::assets.push_back(this);
	};

	Asset::Asset(VertexBuffer& VB, IndexBuffer& IB, Shader& S) : vertices(VB), indices(IB), shader(&S), material(new Material), defaultShader(false) { Assets::assets.push_back(this); };

	Asset::Asset(VertexBuffer& VB, IndexBuffer& IB) : vertices(VB), indices(IB), shader(new Shader), material(new Material), defaultShader(false) { Assets::assets.push_back(this); };

	Asset::~Asset() {
		if (defaultShader)
			delete shader;
		if (defaultMaterial)
			delete material;

		for (auto i = Assets::assets.begin(); i != Assets::assets.end(); i++)
			if (*i == this)
			{
				Assets::assets.erase(i);
				break;
			}
	};


	void QG::Asset::build()
	{
		if (built)
			return;

		vertices.Build();
		indices.Build();
		built = true;
	}

	void Asset::draw()
	{
		if (!m_shown || grouped)
			return;

		if (!built)
			build();

		vertices.Bind();
		indices.Bind();
		shader->use();
		
		//get current camera from current window
		auto context = glfwGetCurrentContext();
		window* win = (window*)(glfwGetWindowUserPointer(context));
		shader->setVector<3>("viewPos", win->cam->getPosition());
		shader->setMatrix<4, 4>("view", win->cam->viewMatrix());
		shader->setMatrix<4, 4>("projection", win->cam->projMatrix());
		shader->setMatrix<4, 4>("model", modelMatrix());
		//shader->setFloat("far_plane", (float)(win->cam->projMatrix().getFar()));
		shader->setFloat("far_plane", 25.0f);

		material->Bind();		//POTENTIAL PROBLEM

		if (material->usingDifTex())
		{					
			shader->setInt("DifTex", std::get<Texture>(material->getDiff()).getSlot());
			QM::vector<4> noCol(-1.0f, -1.0f, -1.0f, -1.0f);
			shader->setVector<4>("DifCol", noCol);
			shader->setBool("useDifTex", true);
		}
		else
		{
			shader->setVector<4>("DifCol", std::get<Colour>(material->getDiff()));
			shader->setInt("DifTex", 31);
			shader->setBool("useDifTex", false);
		}

		if (material->usingSpecTex())
		{
			shader->setInt("SpecTex", std::get<Texture>(material->getSpec()).getSlot());
			QM::vector<4> noCol(-1.0f, -1.0f, -1.0f, -1.0f);
			shader->setVector<4>("SpecCol", noCol);
			shader->setBool("useSpecTex", true);
		}
		else
		{
			shader->setVector<4>("SpecCol", std::get<Colour>(material->getSpec()));
			shader->setInt("SpecTex", 31);
			shader->setBool("useSpecTex", false);
		}

		shader->setFloat("shininess", material->getShininess());

		//fetch lights
		shader->setInt("spotLightCount", (int)lighting::spotLights.size());
		for (auto i = lighting::spotLights.begin(); i != lighting::spotLights.end(); i++)
		{			
			auto j = std::to_string(i - lighting::spotLights.begin());
			shader->setVector<3>("SLights[" + j + "].position", (*i)->getPosition());
			shader->setVector<3>("SLights[" + j + "].direction", (*i)->getDirection());
			shader->setFloat("SLights[" + j + "].angle", (*i)->getAngle());
			shader->setFloat("SLights[" + j + "].outerAngle", (*i)->getOuterAngle());
			shader->setVector<4>("SLights[" + j + "].colour", (*i)->getColour());
			shader->setVector<3>("SLights[" + j + "].attenuation", (*i)->getAttenuation());
			(*i)->getShadowMap()->Bind();
			shader->setInt("SLights[" + j + "].depthMap", (*i)->getShadowMap()->getSlot());
		}
		
		shader->setInt("pointLightCount", (int)lighting::pointLights.size());
		for (auto i = lighting::pointLights.begin(); i != lighting::pointLights.end(); i++)
		{
			auto j = std::to_string(i - lighting::pointLights.begin());
			shader->setVector<3>("PLights[" + j + "].position", (*i)->getPosition());
			shader->setVector<4>("PLights[" + j + "].colour", (*i)->getColour());
			shader->setVector<3>("PLights[" + j + "].attenuation", (*i)->getAttenuation());
			(*i)->getShadowMap()->Bind();
			shader->setInt("PLights[" + j + "].depthMap", (*i)->getShadowMap()->getSlot());
		}

		//shader->setInt("dirLightCount", (int)lighting::directionalLights.size());
		//for (auto i = lighting::directionalLights.begin(); i != lighting::directionalLights.end(); i++)
		//{
		//	auto j = std::to_string(i - lighting::directionalLights.begin());
		//	shader->setVector<3>("DLights[" + j + "].position", (*i)->getPosition());
		//	shader->setVector<4>("DLights[" + j + "].colour", (*i)->getColour());
		//	shader->setVector<3>("DLights[" + j + "].direction", (*i)->getDirection());
		//	shader->setVector<3>("DLights[" + j + "].attenuation", (*i)->getAttenuation());
		//}
		
		glDrawElements(drawType, indices.count(), GL_UNSIGNED_INT, nullptr);
		material->Unbind();

		for (auto i = lighting::pointLights.begin(); i != lighting::pointLights.end(); i++)
			(*i)->getShadowMap()->Unbind();

		vertices.Unbind();
		indices.Unbind();
	}

	QM::matrix<4, 4, float> Asset::modelMatrix()
	{
		QM::matrix<4, 4> Mscale;
		Mscale.set(1, 1, scale.get(1));
		Mscale.set(2, 2, scale.get(2));
		Mscale.set(3, 3, scale.get(3));
		Mscale.set(4, 4, 1);
		
		QM::matrix<4, 4> Mrotation;

		float angle = 2.0f * (float)acos(rotation.r);
		
		if (angle != 0)
		{
			QM::vector<3> axis = QM::vector<3>((float)rotation.x, (float)rotation.y, (float)rotation.z).normalise();
			float C = cos(angle);
			float S = sin(angle);


			Mrotation.set(1, 1, C + axis.get(1) * axis.get(1) * (1 - C));
			Mrotation.set(1, 2, axis.get(1) * axis.get(2) * (1 - C) - axis.get(3) * S);
			Mrotation.set(1, 3, axis.get(1) * axis.get(3) * (1 - C) + axis.get(2) * S);
			Mrotation.set(2, 1, axis.get(2) * axis.get(1) * (1 - C) + axis.get(3) * S);
			Mrotation.set(2, 2, C + axis.get(2) * axis.get(2) * (1 - C));
			Mrotation.set(2, 3, axis.get(2) * axis.get(3) * (1 - C) - axis.get(1) * S);
			Mrotation.set(3, 1, axis.get(3) * axis.get(1) * (1 - C) - axis.get(2) * S);
			Mrotation.set(3, 2, axis.get(3) * axis.get(2) * (1 - C) + axis.get(1) * S);
			Mrotation.set(3, 3, C + axis.get(3) * axis.get(3) * (1 - C));
			Mrotation.set(4, 4, 1);
		}
		else
			Mrotation = QM::identity<4>();

		QM::matrix<4, 4> Mtranslation = QM::identity<4>();
		Mtranslation.set(1, 4, position.get(1));
		Mtranslation.set(2, 4, position.get(2));
		Mtranslation.set(3, 4, position.get(3));

		return Mtranslation * Mrotation * Mscale;
	}

	void Asset::setScale(float SF)
	{
		setScale(SF, SF, SF);
	}

	void Asset::setScale(float x, float y, float z)
	{
		scale = QM::vector<3>(x, y, z);
	}

	void Asset::setScale(QM::vector<3> SF)
	{
		scale = SF;
	}

	QM::vector<3> Asset::getScale()
	{
		return scale;
	}

	void Asset::changeScale(float SF)
	{
		scale = SF * scale;
	}

	void Asset::changeScale(float x, float y, float z)
	{
		scale.set(1, scale.get(1) * x);
		scale.set(2, scale.get(2) * y);
		scale.set(3, scale.get(3) * z);
	}

	void Asset::changeScale(QM::vector<3> SF)
	{
		scale.set(1, scale.get(1) * SF.get(1));
		scale.set(2, scale.get(2) * SF.get(2));
		scale.set(3, scale.get(3) * SF.get(3));
	}

	void Asset::setRotation(double xAngle, double yAngle, double zAngle)
	{
		rotation = QM::rotation(xAngle, yAngle, zAngle).normalise();
	}

	void Asset::setRotation(float angle, QM::vector<3> axis)
	{
		rotation = QM::rotation(angle, axis).normalise();
	}

	void Asset::setRotation(QM::Quaternion Q)
	{//may need more checks
		if (abs(Q.magnitude()-1) < 0.01)
			rotation = Q.normalise();
	}

	QM::Quaternion Asset::getRotation()
	{
		return rotation;
	}

	void Asset::changeRotation(double xAngle, double yAngle, double zAngle)
	{
		auto rot2 = QM::rotation(xAngle, yAngle, zAngle).normalise();
		rotation = (rot2 * rotation).normalise();
	}

	void Asset::changeRotation(float angle, QM::vector<3> axis)
	{
		auto rot2 = QM::rotation(angle, axis);
		rotation = (rot2 * rotation).normalise();
	}

	void Asset::changeRotation(QM::Quaternion Q)
	{
		if (abs(Q.magnitude() - 1) < 0.01)
			rotation = (Q * rotation).normalise();
	}

	void Asset::setPosition(float x, float y, float z)
	{
		position = QM::vector<3>(x, y, z);
	}

	void Asset::setPosition(QM::vector<3> R)
	{
		position = R;
	}

	QM::vector<3> Asset::getPosition()
	{
		return position;
	}

	void Asset::move(float x, float y, float z)
	{
		position += QM::vector<3>(x, y, z);
	}

	void Asset::move(QM::vector<3> R)
	{
		position += R;
	}

	Shader* Asset::getShader() const { return shader; };

	void Asset::setShader(Shader* S) {
		defaultShader = false;
		delete shader;
		shader = S;
	}

	Material* Asset::getMaterial() const { return material; };

	void Asset::setMaterial(Material* M) {
		defaultMaterial = false;
		material = M;
	}

	bool Asset::isShown()const { return m_shown; };
	void Asset::show() { m_shown = true; };
	void Asset::hide() { m_shown = false; };
	bool Asset::isGrouped() const { return grouped; };
	GLenum Asset::getDrawType() const { return drawType; }
	
	void Asset::insideOut()
	{
		for (auto& x : vertices)
			x.setNormal(-1 * x.getNormal());
	}

	float Asset::interceptTime(QM::vector<3> rayOrigin, QM::vector<3> direction)
	{
		QM::vector<4> lowBound4;
		lowBound4.set(1, Lbound.get(1));
		lowBound4.set(2, Lbound.get(2));
		lowBound4.set(3, Lbound.get(3));
		lowBound4.set(4, 1);
		lowBound4 = modelMatrix() * lowBound4;
		QM::vector<3> lowBound3;
		lowBound3.set(1, lowBound4.get(1));
		lowBound3.set(2, lowBound4.get(2));
		lowBound3.set(3, lowBound4.get(3));

		QM::vector<4> highBound4;
		highBound4.set(1, Ubound.get(1));
		highBound4.set(2, Ubound.get(2));
		highBound4.set(3, Ubound.get(3));
		highBound4.set(4, 1);
		highBound4 = modelMatrix() * highBound4;
		QM::vector<3> highBound3;
		highBound3.set(1, highBound4.get(1));
		highBound3.set(2, highBound4.get(2));
		highBound3.set(3, highBound4.get(3));

		bool xIntercept = true;
		bool yIntercept = true;
		bool zIntercept = true;

		QM::vector<3> norm;
		norm.set(1, modelMatrix().get(1, 1));
		norm.set(2, modelMatrix().get(2, 1));
		norm.set(3, modelMatrix().get(3, 1));

		float denom = norm * direction;
		float minX = 0;
		float maxX = 0;
		if (abs(denom) < 0.01)
		{
			minX = INFINITY;
			maxX = INFINITY;
			xIntercept = false;
			float Udist = abs((QM::vector<3>)(rayOrigin - highBound3) * norm) / norm.magnitude();
			float Ldist = abs((QM::vector<3>)(rayOrigin - lowBound3) * norm) / norm.magnitude();
			float Pdist = abs((QM::vector<3>)(highBound3 - lowBound3) * norm) / norm.magnitude();
			if (Pdist < Udist || Pdist < Ldist)
				return INFINITY;
		}
		else
		{
			minX = (QM::vector<3>)(lowBound3 - rayOrigin) * norm / denom;
			maxX = (QM::vector<3>)(highBound3 - rayOrigin) * norm / denom;
			if (minX < 0 || maxX < 0)
				return INFINITY;
		}
		if (maxX < minX)
			std::swap(maxX, minX);

		norm.set(1, modelMatrix().get(1, 2));
		norm.set(2, modelMatrix().get(2, 2));
		norm.set(3, modelMatrix().get(3, 2));

		denom = norm * direction;
		float minY = 0;
		float maxY = 0;
		if (abs(denom) < 0.01)
		{
			minY = INFINITY;
			maxY = INFINITY;
			yIntercept = false;
			float Udist = abs((QM::vector<3>)(rayOrigin - highBound3) * norm) / norm.magnitude();
			float Ldist = abs((QM::vector<3>)(rayOrigin - lowBound3) * norm) / norm.magnitude();
			float Pdist = abs((QM::vector<3>)(highBound3 - lowBound3) * norm) / norm.magnitude();
			if (Pdist < Udist || Pdist < Ldist)
				return INFINITY;
		}
		else
		{
			minY = (QM::vector<3>)(lowBound3 - rayOrigin) * norm / denom;
			maxY = (QM::vector<3>)(highBound3 - rayOrigin) * norm / denom;
			if (minY < 0 || maxY < 0)
				return INFINITY;
		}
		if (maxY < minY)
			std::swap(maxY, minY);

		norm.set(1, modelMatrix().get(1, 3));
		norm.set(2, modelMatrix().get(2, 3));
		norm.set(3, modelMatrix().get(3, 3));

		denom = norm * direction;
		float minZ = 0;
		float maxZ = 0;
		if (abs(denom) < 0.01)
		{
			minZ = INFINITY;
			maxZ = INFINITY;
			zIntercept = false;
			float Udist = abs((QM::vector<3>)(rayOrigin - highBound3) * norm) / norm.magnitude();
			float Ldist = abs((QM::vector<3>)(rayOrigin - lowBound3) * norm) / norm.magnitude();
			float Pdist = abs((QM::vector<3>)(highBound3 - lowBound3) * norm) / norm.magnitude();
			if (Pdist < Udist || Pdist < Ldist)
				return INFINITY;
		}
		else
		{
			minZ = (QM::vector<3>)(lowBound3 - rayOrigin) * norm / denom;
			maxZ = (QM::vector<3>)(highBound3 - rayOrigin) * norm / denom;
			if (minZ < 0 || maxZ < 0)
				return INFINITY;
		}
		if (maxZ < minZ)
			std::swap(maxZ, minZ);

		if (xIntercept && yIntercept && zIntercept)
		{
			if (maxX < minY || maxX < minZ || maxY < minX || maxY < minZ || maxZ < minX || maxZ < minY)
				return INFINITY;
			return std::max({ minX, minY, minZ });
		}
		else if (int(xIntercept) + int(yIntercept) + int(zIntercept) == 2)
		{
			if (!xIntercept)
			{
				if (maxY < minZ || maxZ < minY)
					return INFINITY;
				else
					return std::max(minY, minZ);
			}
			if (!yIntercept)
			{
				if (maxX < minZ || maxZ < minX)
					return INFINITY;
				else
					return std::max(minX, minZ);
			}
			if (!zIntercept)
			{
				if (maxX < minY || maxY < minX)
					return INFINITY;
				else				
					return std::max(minX, minY);
			}
		}
		else
			return std::min({ minX, minY, minZ });

		return INFINITY;
	}
}