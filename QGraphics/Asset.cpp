#include "Asset.h"
#include "Light.h"
#include <string>
#include "Window.h"

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
		shader->setFloat("far_plane", (float)(win->cam->projMatrix().getFar()));

		material->Bind();

		auto temp = material->getDiff();

		if (material->usingDifTex())
		{			
			shader->setInt("DifTex", *(int*)(std::get_if<unsigned int>(&temp)));
			QM::vector<4> noCol(-1.0f, -1.0f, -1.0f, -1.0f);
			shader->setVector<4>("DifCol", noCol);
			shader->setBool("useDifTex", true);
		}
		else
		{
			shader->setVector<4>("DifCol", std::get<Colour>(temp));
			shader->setInt("DifTex", 31);
			shader->setBool("useDifTex", false);
		}

		temp = material->getSpec();

		if (material->usingSpecTex())
		{
			shader->setInt("SpecTex", *(int*)(std::get_if<unsigned int>(&temp)));
			QM::vector<4> noCol(-1.0f, -1.0f, -1.0f, -1.0f);
			shader->setVector<4>("SpecCol", noCol);
			shader->setBool("useSpecTex", true);
		}
		else
		{
			shader->setVector<4>("SpecCol", std::get<Colour>(temp));
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

		shader->setInt("dirLightCount", (int)lighting::directionalLights.size());
		for (auto i = lighting::directionalLights.begin(); i != lighting::directionalLights.end(); i++)
		{
			auto j = std::to_string(i - lighting::directionalLights.begin());
			shader->setVector<3>("DLights[" + j + "].position", (*i)->getPosition());
			shader->setVector<4>("DLights[" + j + "].colour", (*i)->getColour());
			shader->setVector<3>("DLights[" + j + "].direction", (*i)->getDirection());
			shader->setVector<3>("DLights[" + j + "].attenuation", (*i)->getAttenuation());
		}
		
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
	};

	Material* Asset::getMaterial() const { return material; };

	void Asset::setMaterial(Material* M) {
		defaultMaterial = false;
		delete material;
		material = M;
	};
	void Asset::setMaterial(Material M) { setMaterial(&M); };

	bool Asset::isShown()const { return m_shown; };
	void Asset::show() { m_shown = true; };
	void Asset::hide() { m_shown = false; };
	bool Asset::isGrouped() const { return grouped; };
	GLenum Asset::getDrawType() const { return drawType; };
}