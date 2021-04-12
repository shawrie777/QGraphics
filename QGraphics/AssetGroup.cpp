#include "AssetGroup.h"
#include "Light.h"
#include <string>
#include "Window.h"

namespace QG
{
	void QG::AssetGroup::build()
	{
		if (built)
			return;

		m_parent->build();
		for (auto* x : m_children)
			x->build();
		built = true;
	}

	void AssetGroup::draw()
	{

			if (!built)
				build();

			//get current camera from current window
			auto context = glfwGetCurrentContext();
			window* win = (window*)(glfwGetWindowUserPointer(context));

			int i = -1;

			int count = (int)m_children.size();

			while (i < count)
			{
				Asset* current;
				if (i == -1)
					current = m_parent;
				else
					current = m_children[i];


				current->vertices.Bind();
				current->indices.Bind();
				current->shader->use();

				current->shader->setVector<3>("viewPos", win->cam->getPosition());
				current->shader->setMatrix<4, 4>("view", win->cam->viewMatrix());
				current->shader->setMatrix<4, 4>("projection", win->cam->projMatrix());

				current->shader->setMatrix<4, 4>("model", modelMatrix() * current->modelMatrix());

				auto temp = current->material->getDiff();

				if (current->material->usingDifTex())
				{
					current->shader->setInt("DifTex", *(int*)(std::get_if<unsigned int>(&temp)));
					QM::vector<4> noCol(-1.0f, -1.0f, -1.0f, -1.0f);
					current->shader->setVector<4>("DifCol", noCol);
					current->shader->setBool("useDifTex", true);
				}
				else
				{
					current->shader->setVector<4>("DifCol", *(Colour*)(std::get_if<Colour>(&temp)));
					current->shader->setInt("DifTex", 31);
					current->shader->setBool("useDifTex", false);
				}

				temp = current->material->getSpec();

				if (current->material->usingSpecTex())
				{
					current->shader->setInt("SpecTex", *(int*)(std::get_if<unsigned int>(&temp)));
					QM::vector<4> noCol(-1.0f, -1.0f, -1.0f, -1.0f);
					current->shader->setVector<4>("SpecCol", noCol);
					current->shader->setBool("useSpecTex", true);
				}
				else
				{
					current->shader->setVector<4>("SpecCol", *(Colour*)(std::get_if<Colour>(&temp)));
					current->shader->setInt("SpecTex", 31);
					current->shader->setBool("useSpecTex", false);
				}

				current->shader->setFloat("shininess", current->material->getShininess());

				//fetch lights
				current->shader->setInt("spotLightCount", (int)lighting::spotLights.size());
				for (auto i = lighting::spotLights.begin(); i != lighting::spotLights.end(); i++)
				{
					auto j = std::to_string(i - lighting::spotLights.begin());
					current->shader->setVector<3>("SLights[" + j + "].position", (*i)->getPosition());
					current->shader->setVector<3>("SLights[" + j + "].direction", (*i)->getDirection());
					current->shader->setFloat("SLights[" + j + "].angle", (*i)->getAngle());
					current->shader->setFloat("SLights[" + j + "].outerAngle", (*i)->getOuterAngle());
					current->shader->setVector<4>("SLights[" + j + "].colour", (*i)->getColour());
					current->shader->setVector<3>("SLights[" + j + "].attenuation", (*i)->getAttenuation());
				}

				current->shader->setInt("pointLightCount", (int)lighting::pointLights.size());
				for (auto i = lighting::pointLights.begin(); i != lighting::pointLights.end(); i++)
				{
					auto j = std::to_string(i - lighting::pointLights.begin());
					current->shader->setVector<3>("PLights[" + j + "].position", (*i)->getPosition());
					current->shader->setVector<4>("PLights[" + j + "].colour", (*i)->getColour());
					current->shader->setVector<3>("PLights[" + j + "].attenuation", (*i)->getAttenuation());
				}

				current->shader->setInt("dirLightCount", (int)lighting::directionalLights.size());
				for (auto i = lighting::directionalLights.begin(); i != lighting::directionalLights.end(); i++)
				{
					auto j = std::to_string(i - lighting::directionalLights.begin());
					current->shader->setVector<3>("DLights[" + j + "].position", (*i)->getPosition());
					current->shader->setVector<4>("DLights[" + j + "].colour", (*i)->getColour());
					current->shader->setVector<3>("DLights[" + j + "].direction", (*i)->getDirection());
					current->shader->setVector<3>("DLights[" + j + "].attenuation", (*i)->getAttenuation());
				}

				glDrawElements(drawType, current->indices.count(), GL_UNSIGNED_INT, nullptr);

				++i;
			}
	
	}

}