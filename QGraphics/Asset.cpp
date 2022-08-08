#include "Asset.h"
#include "Light.h"
#include <string>
#include "Window.h"
#include <algorithm>
#include <fstream>
#include <sstream>

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

	Asset::Asset(const std::string filepath) : shader(new Shader), material(new Material), defaultShader(true)
	{
		std::ifstream stream;
		std::string content;
		stream.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			stream.open(filepath);
			std::stringstream string;
			string << stream.rdbuf();
			stream.close();
			content = string.str();
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERROR, failed to read asset file: " << filepath << std::endl;
		}

		std::string target("positions-array");
		auto startPos = std::search(content.begin(), content.end(), target.begin(),target.end());
		target = ">";
		startPos = std::search(startPos, content.end(), target.begin(), target.end());
		startPos++;

		target = "<";
		auto endPos = std::search(startPos, content.end(), target.begin(), target.end());

		std::vector<float> values;
		std::string data = content.substr(startPos - content.begin(), endPos-startPos);
		bool finding = true;
		std::string::size_type sz = 0;
		while (finding)
		{
			try
			{
				float value = std::stof(data, &sz);
				values.push_back(value);
				data = data.substr(sz);
			}
			catch (const std::invalid_argument& e)
			{
				finding = false;
			}
		}
		_ASSERT(values.size() % 3 == 0);

		Lbound = QM::vector<3>();
		Ubound = QM::vector<3>();

		std::vector<QM::vector<3>> positions;
		int i = 0;
		while (i<values.size())
		{
			QM::vector<3> pos;
			pos.set(1, values[i++]);
			pos.set(2, values[i++]);
			pos.set(3, values[i++]);
			positions.push_back(pos);

			Lbound.set(1, std::min(Lbound.get(1), pos.get(1)));
			Lbound.set(2, std::min(Lbound.get(2), pos.get(2)));
			Lbound.set(3, std::min(Lbound.get(3), pos.get(3)));

			Ubound.set(1, std::max(Ubound.get(1), pos.get(1)));
			Ubound.set(2, std::max(Ubound.get(2), pos.get(2)));
			Ubound.set(3, std::max(Ubound.get(3), pos.get(3)));
		}
		values.clear();

		target = "normals-array";
		startPos = std::search(content.begin(), content.end(), target.begin(), target.end());
		target = ">";
		startPos = std::search(startPos, content.end(), target.begin(), target.end());
		startPos++;

		target = "<";
		endPos = std::search(startPos, content.end(), target.begin(), target.end());

		data = content.substr(startPos - content.begin(), endPos - startPos);
		finding = true;		
		while (finding)
		{
			try
			{
				float value = std::stof(data, &sz);
				values.push_back(value);
				data = data.substr(sz);
			}
			catch (const std::invalid_argument& e)
			{
				finding = false;
			}
		}
		_ASSERT(values.size() % 3 == 0);

		std::vector<QM::vector<3>> normals;
		i = 0;
		while (i < values.size())
		{
			QM::vector<3> norm;
			norm.set(1, values[i++]);
			norm.set(2, values[i++]);
			norm.set(3, values[i++]);
			normals.push_back(norm);
		}
		values.clear();

		target = "mesh-map";
		startPos = std::search(content.begin(), content.end(), target.begin(), target.end());
		target = "count";
		startPos = std::search(startPos, content.end(), target.begin(), target.end());
		target = ">";
		startPos = std::search(startPos, content.end(), target.begin(), target.end());
		startPos++;

		target = "<";
		endPos = std::search(startPos, content.end(), target.begin(), target.end());

		data = content.substr(startPos - content.begin(), endPos - startPos);
		finding = true;
		while (finding)
		{
			try
			{
				float value = std::stof(data, &sz);
				values.push_back(value);
				data = data.substr(sz);
			}
			catch (const std::invalid_argument& e)
			{
				finding = false;
			}
		}
		_ASSERT(values.size() % 2 == 0);

		std::vector<QM::vector<2>> texCoords;
		i = 0;
		while (i < values.size())
		{
			QM::vector<2> tex;
			tex.set(1, values[i++]);
			tex.set(2, -1.0f * values[i++]);
			texCoords.push_back(tex);
		}
		values.clear();

		target = "<p>";
		startPos = std::search(content.begin(), content.end(), target.begin(), target.end());
		startPos += 3;

		target = "<";
		endPos = std::search(startPos, content.end(), target.begin(), target.end());

		data = content.substr(startPos - content.begin(), endPos - startPos);
		std::vector<int> Ivalues;
		finding = true;
		while (finding)
		{
			try
			{
				int value = std::stoi(data, &sz);
				Ivalues.push_back(value);
				data = data.substr(sz);
			}
			catch (const std::invalid_argument& e)
			{
				finding = false;
			}
		}
		_ASSERT(Ivalues.size() % 3 == 0);

		i = 0;
		while (i < Ivalues.size())
		{
			int pos_index = Ivalues[i++];
			int norm_index = Ivalues[i++];
			int tex_index = Ivalues[i++];

			QG::Vertex X(positions[pos_index], texCoords[tex_index], normals[norm_index]);
			vertices.push_back(X);
		}

		for (int j = 0; j < vertices.vertexCount(); j++)
			indices.AddIndices({ j });

		Assets::assets.push_back(this);
	}

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

		if (curve)
		{
			float t = std::min(win->runtime(), curve->endTime());
			setPosition(curve->getPosition(t));
			if (curve->rotating())
				changeRotation(curve->getRotation());
			if (win->runtime() > curve->endTime())
			{
				setPosition(curve->getPosition(curve->endTime()));
				for (auto i = Curves::curves.begin(); i != Curves::curves.end(); i++)
					if (curve == *i)
					{
						Curves::curves.erase(i);
						break;
					}
				curve = nullptr;
			}
		}



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

		return Mtranslation * Mrotation * scale;
	}

	void Asset::setScale(float SF)
	{
		setScale(SF, SF, SF);
	}

	void Asset::setScale(float x, float y, float z)
	{
		QM::matrix<4, 4> temp = QM::identity<4>();
		temp.set(1, 1, x);
		temp.set(2, 2, y);
		temp.set(3, 3, z);
		scale = temp;
	}

	void Asset::setScale(QM::vector<3> SF)
	{
		QM::matrix<4, 4> temp = QM::identity<4>();
		for (int i = 1; i < 4; i++)
			temp.set(i, i, SF.get(i));

		scale = temp;
	}

	void Asset::setScale(float SF, QM::vector<3> direction)
	{
		QM::vector<3> alpha;

		if (direction.get(2) == 0 && direction.get(3) == 0)
			alpha = QM::vector<3>(0.0f, 1.0f, 0.0f);
		else
			alpha = QM::vector<3>(1.0f, 0.0f, 0.0f);

		QM::vector<3> beta = direction.cross(alpha);
		alpha = beta.cross(direction);

		QM::matrix<4, 4> Q;
		for (int i = 1; i < 4; i++)
		{
			Q.set(i, 1, direction.get(i));
			Q.set(i, 2, alpha.get(i));
			Q.set(i, 3, beta.get(i));
		}
		Q.set(4, 4, 1);
		auto inv_Q = Q.inverse();
		QM::matrix<4, 4> P = QM::identity<4>();
		P.set(1, 1, SF);

		scale = Q * P * inv_Q;
	}

	QM::matrix<4,4> Asset::getScale()
	{
		return scale;
	}

	void Asset::changeScale(float SF)
	{
		scale = SF * scale;
	}

	void Asset::changeScale(float x, float y, float z)
	{
		QM::matrix<4, 4> temp = QM::identity<4>();
		temp.set(1, 1, x);
		temp.set(2, 2, y);
		temp.set(3, 3, z);
		scale = temp * scale;
	}

	void Asset::changeScale(QM::vector<3> SF)
	{
		QM::matrix<4, 4> temp = QM::identity<4>();
		for (int i = 1; i < 4; i++)
			temp.set(i, i, SF.get(i));

		scale = temp * scale;
	}

	void Asset::changeScale(float SF, QM::vector<3> direction)
	{
		QM::vector<3> alpha;

		if (direction.get(2) == 0 && direction.get(3) == 0)
			alpha = QM::vector<3>(0.0f, 1.0f, 0.0f);
		else
			alpha = QM::vector<3>(1.0f, 0.0f, 0.0f);

		QM::vector<3> beta = direction.cross(alpha);
		alpha = beta.cross(direction);

		QM::matrix<4, 4> Q;
		for (int i = 1; i < 4; i++)
		{
			Q.set(i, 1, direction.get(i));
			Q.set(i, 2, alpha.get(i));
			Q.set(i, 3, beta.get(i));
		}
		Q.set(4, 4, 1);
		auto inv_Q = Q.inverse();
		QM::matrix<4, 4> P = QM::identity<4>();
		P.set(1, 1, SF);

		scale = Q * P * inv_Q * scale;
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

	void Asset::setCurve(Curve& c)
	{		
		Curves::curves.push_back(std::make_shared<Curve>(c));
		curve = Curves::curves.back();
		curve->setStartTime(getWindow()->runtime());
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

		std::vector<float> minima;
		std::vector<float> maxima;
		for (int i = 1; i < 4; i++)
		{
			QM::vector<3> norm;
			norm.set(1, modelMatrix().get(1, i));
			norm.set(2, modelMatrix().get(2, i));
			norm.set(3, modelMatrix().get(3, i));
			norm = norm.normalise();

			float denom = norm * direction;
			float min = 0;
			float max = 0;
			if (abs(denom) < 0.00001)
			{
				min = INFINITY;
				max = INFINITY;
				float Udist = abs((QM::vector<3>)(rayOrigin - highBound3) * norm);
				float Ldist = abs((QM::vector<3>)(rayOrigin - lowBound3) * norm);
				float Pdist = abs((QM::vector<3>)(highBound3 - lowBound3) * norm);
				if (Pdist < Udist || Pdist < Ldist)
					return INFINITY;

				continue;
			}
			else {
				min = (QM::vector<3>)(lowBound3 - rayOrigin) * norm / denom;
				max = (QM::vector<3>)(highBound3 - rayOrigin) * norm / denom;
				if (max < min)
					std::swap(max, min);
			}

			if (max < 0)
				return INFINITY;
			if (min < 0)
				min = 0.0f;

			minima.push_back(min);
			maxima.push_back(max);
		}

		float max_min = *std::max_element(minima.begin(), minima.end());
		float min_max = *std::min_element(maxima.begin(), maxima.end());

		if (min_max < max_min)
			return INFINITY;
		if (max_min == 0.0f)
			return min_max;
		return max_min;		

		return INFINITY;
	}
	bool Asset::hasCurve()
	{
		return curve != nullptr;
	}

	bool Asset::collides(Asset* asset)
	{
		auto model = modelMatrix();
		QM::vector<4> temp = model * QM::vector<4>(Lbound.get(1), Lbound.get(2), Lbound.get(3), 1.0f);		
		QM::vector<3> first_Lbound(temp.get(1), temp.get(2), temp.get(3));

		temp = model * QM::vector<4>(Ubound.get(1), Ubound.get(2), Ubound.get(3), 1.0f);
		QM::vector<3> first_Ubound(temp.get(1), temp.get(2), temp.get(3));

		temp = model * QM::vector<4>(asset->Lbound.get(1), asset->Lbound.get(2), asset->Lbound.get(3), 1.0f);
		QM::vector<3> second_Lbound(temp.get(1), temp.get(2), temp.get(3));

		temp = model * QM::vector<4>(asset->Ubound.get(1), asset->Ubound.get(2), asset->Ubound.get(3), 1.0f);
		QM::vector<3> second_Ubound(temp.get(1), temp.get(2), temp.get(3));

		for (int i = 1; i < 4; i++)
		{
			std::vector<float> values;
			values.push_back(first_Lbound.get(i));
			values.push_back(first_Ubound.get(i));
			values.push_back(second_Lbound.get(i));
			values.push_back(second_Ubound.get(i));

			std::vector<float> value_copy = values;
			std::sort(value_copy.begin(), value_copy.end());

			int A = std::find(value_copy.begin(), value_copy.end(), values[0]) - value_copy.begin();
			int B = std::find(value_copy.begin(), value_copy.end(), values[1]) - value_copy.begin();

			if (A + B == 1 || A + B == 5)
				return false;
		}
		return true;
	}
}