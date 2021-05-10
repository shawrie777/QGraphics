#include "Skybox.h"
#include "Window.h"

namespace QG
{
	Skybox::Skybox(std::vector<std::string> faces) : texture(faces)
	{
		delete material;
		defaultMaterial = false;
		shader = new Shader("f:/c++/qgraphics/QGraphics/skybox_vertex_shader.txt", "f:/c++/qgraphics/QGraphics/skybox_frag_shader.txt");
	}

	Skybox::Skybox(std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back) :
		texture(right, left, top, bottom, front, back)
	{
		delete material;
		defaultMaterial = false;
		shader = new Shader("f:/c++/qgraphics/QGraphics/skybox_vertex_shader.txt", "f:/c++/qgraphics/QGraphics/skybox_frag_shader.txt");
	}

	void Skybox::draw()
	{
		if (!m_shown)
			return;

		if (!built)
			build();

		glDepthMask(GL_FALSE);

		vertices.Bind();
		indices.Bind();
		shader->use();

		//get current camera from current window
		auto context = glfwGetCurrentContext();
		window* win = (window*)(glfwGetWindowUserPointer(context));


		shader->setMatrix<4, 4>("projection", win->cam->projMatrix());
		QM::matrix<4, 4> V = win->cam->viewMatrix();
		QM::matrix<4, 4> I = QM::identity<4>();
		I.set(4, 4, 0);
		V = V * I;
		V.set(4, 4, 1);
		shader->setMatrix<4, 4>("view", V);

		texture.Bind();

		shader->setInt("skybox", texture.getSlot());

		glDrawElements(drawType, indices.count(), GL_UNSIGNED_INT, nullptr);
		glDepthMask(GL_TRUE);

		changed = false;
		texture.Unbind();
	}
}