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

				if (current->isShown())
				{
					current->vertices.Bind();
					current->indices.Bind();
					current->getShader()->use();

					current->getShader()->setVector<3>("viewPos", win->cam->getPosition());
					current->getShader()->setMatrix<4, 4>("view", win->cam->viewMatrix());
					current->getShader()->setMatrix<4, 4>("projection", win->cam->projMatrix());

					current->getShader()->setMatrix<4, 4>("model", modelMatrix() * current->modelMatrix());

					current->getMaterial()->Bind();

					auto temp = current->getMaterial()->getDiff();

					if (current->getMaterial()->usingDifTex())
					{
						current->getShader()->setInt("DifTex", *(int*)(std::get_if<unsigned int>(&temp)));
						QM::vector<4> noCol(-1.0f, -1.0f, -1.0f, -1.0f);
						current->getShader()->setVector<4>("DifCol", noCol);
						current->getShader()->setBool("useDifTex", true);
					}
					else
					{
						current->getShader()->setVector<4>("DifCol", *(Colour*)(std::get_if<Colour>(&temp)));
						current->getShader()->setInt("DifTex", 31);
						current->getShader()->setBool("useDifTex", false);
					}

					temp = current->getMaterial()->getSpec();

					if (current->getMaterial()->usingSpecTex())
					{
						current->getShader()->setInt("SpecTex", *(int*)(std::get_if<unsigned int>(&temp)));
						QM::vector<4> noCol(-1.0f, -1.0f, -1.0f, -1.0f);
						current->getShader()->setVector<4>("SpecCol", noCol);
						current->getShader()->setBool("useSpecTex", true);
					}
					else
					{
						current->getShader()->setVector<4>("SpecCol", *(Colour*)(std::get_if<Colour>(&temp)));
						current->getShader()->setInt("SpecTex", 31);
						current->getShader()->setBool("useSpecTex", false);
					}

					current->getShader()->setFloat("shininess", current->getMaterial()->getShininess());

					//fetch lights
					current->getShader()->setInt("spotLightCount", (int)lighting::spotLights.size());
					for (auto i = lighting::spotLights.begin(); i != lighting::spotLights.end(); i++)
					{
						auto j = std::to_string(i - lighting::spotLights.begin());
						current->getShader()->setVector<3>("SLights[" + j + "].position", (*i)->getPosition());
						current->getShader()->setVector<3>("SLights[" + j + "].direction", (*i)->getDirection());
						current->getShader()->setFloat("SLights[" + j + "].angle", (*i)->getAngle());
						current->getShader()->setFloat("SLights[" + j + "].outerAngle", (*i)->getOuterAngle());
						current->getShader()->setVector<4>("SLights[" + j + "].colour", (*i)->getColour());
						current->getShader()->setVector<3>("SLights[" + j + "].attenuation", (*i)->getAttenuation());
					}

					current->getShader()->setInt("pointLightCount", (int)lighting::pointLights.size());
					for (auto i = lighting::pointLights.begin(); i != lighting::pointLights.end(); i++)
					{
						auto j = std::to_string(i - lighting::pointLights.begin());
						current->getShader()->setVector<3>("PLights[" + j + "].position", (*i)->getPosition());
						current->getShader()->setVector<4>("PLights[" + j + "].colour", (*i)->getColour());
						current->getShader()->setVector<3>("PLights[" + j + "].attenuation", (*i)->getAttenuation());
					}

					current->getShader()->setInt("dirLightCount", (int)lighting::directionalLights.size());
					for (auto i = lighting::directionalLights.begin(); i != lighting::directionalLights.end(); i++)
					{
						auto j = std::to_string(i - lighting::directionalLights.begin());
						current->getShader()->setVector<3>("DLights[" + j + "].position", (*i)->getPosition());
						current->getShader()->setVector<4>("DLights[" + j + "].colour", (*i)->getColour());
						current->getShader()->setVector<3>("DLights[" + j + "].direction", (*i)->getDirection());
						current->getShader()->setVector<3>("DLights[" + j + "].attenuation", (*i)->getAttenuation());
					}

					glDrawElements(drawType, current->indices.count(), GL_UNSIGNED_INT, nullptr);
				}
				++i;
			}
	
	}

}