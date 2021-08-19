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

					if (curve)
					{
						float t = std::min(win->runtime(), curve->endTime());
						setPosition(curve->getPosition(t));
						if (curve->rotating())
							changeRotation(curve->getRotation());
						if (win->runtime() > curve->endTime())
							curve = nullptr;
					}

					current->getShader()->setMatrix<4, 4>("model", modelMatrix() * current->modelMatrix());
					shader->setFloat("far_plane", 25.0f);

					current->getMaterial()->Bind();

					if (current->getMaterial()->usingDifTex())
					{
						current->shader->setInt("DifTex", std::get<Texture>(current->getMaterial()->getDiff()).getSlot());
						QM::vector<4> noCol(-1.0f, -1.0f, -1.0f, -1.0f);
						current->shader->setVector<4>("DifCol", noCol);
						current->shader->setBool("useDifTex", true);
					}
					else
					{
						current->shader->setVector<4>("DifCol", std::get<Colour>(current->getMaterial()->getDiff()));
						current->shader->setInt("DifTex", 31);
						current->shader->setBool("useDifTex", false);
					}

					if (current->getMaterial()->usingSpecTex())
					{
						current->shader->setInt("SpecTex", std::get<Texture>(current->getMaterial()->getSpec()).getSlot());
						QM::vector<4> noCol(-1.0f, -1.0f, -1.0f, -1.0f);
						current->shader->setVector<4>("SpecCol", noCol);
						current->shader->setBool("useSpecTex", true);
					}
					else
					{
						current->shader->setVector<4>("SpecCol", std::get<Colour>(current->getMaterial()->getSpec()));
						current->shader->setInt("SpecTex", 31);
						current->shader->setBool("useSpecTex", false);
					}

					current->getShader()->setFloat("shininess", current->getMaterial()->getShininess());

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
						(*i)->getShadowMap()->Bind();
						current->shader->setInt("SLights[" + j + "].depthMap", (*i)->getShadowMap()->getSlot());
					}

					current->shader->setInt("pointLightCount", (int)lighting::pointLights.size());
					for (auto i = lighting::pointLights.begin(); i != lighting::pointLights.end(); i++)
					{
						auto j = std::to_string(i - lighting::pointLights.begin());
						current->shader->setVector<3>("PLights[" + j + "].position", (*i)->getPosition());
						current->shader->setVector<4>("PLights[" + j + "].colour", (*i)->getColour());
						current->shader->setVector<3>("PLights[" + j + "].attenuation", (*i)->getAttenuation());
						(*i)->getShadowMap()->Bind();
						current->shader->setInt("PLights[" + j + "].depthMap", (*i)->getShadowMap()->getSlot());
					}

					//current->getShader()->setInt("dirLightCount", (int)lighting::directionalLights.size());
					//for (auto i = lighting::directionalLights.begin(); i != lighting::directionalLights.end(); i++)
					//{
					//	auto j = std::to_string(i - lighting::directionalLights.begin());
					//	current->getShader()->setVector<3>("DLights[" + j + "].position", (*i)->getPosition());
					//	current->getShader()->setVector<4>("DLights[" + j + "].colour", (*i)->getColour());
					//	current->getShader()->setVector<3>("DLights[" + j + "].direction", (*i)->getDirection());
					//	current->getShader()->setVector<3>("DLights[" + j + "].attenuation", (*i)->getAttenuation());
					//}

					glDrawElements(drawType, current->indices.count(), GL_UNSIGNED_INT, nullptr);

					current->getMaterial()->Unbind();
					for (auto i = lighting::pointLights.begin(); i != lighting::pointLights.end(); i++)
						(*i)->getShadowMap()->Unbind();

					current->vertices.Unbind();
					current->indices.Unbind();
				}
				++i;
			}
	
	}

}