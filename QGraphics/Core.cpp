#include "Core.h"
#include "Window.h"
#include "Asset.h"
#pragma once


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    keyCode K = (keyCode)key;
    keyState state = keyState::press;
    if (action == GLFW_RELEASE)
        state = keyState::release;
    if (action == GLFW_PRESS)
        state = keyState::press;
    modCode M = (modCode)mods;
    keyAction act(K, state, M);

    auto it = keyFuncs.find(act);
    if (it != keyFuncs.end())
        it->second();
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    mouseCode B = (mouseCode)button;
    keyState state = keyState::press;
    if (action == GLFW_RELEASE)
        state = keyState::release;
    if (action == GLFW_PRESS)
        state = keyState::press;
    modCode mod = (modCode)mods;
    mouseAction act(B, state, mod);

    double x, y;
    auto context = glfwGetCurrentContext();
    glfwGetCursorPos(context, &x, &y);

    QG::window* win = (QG::window*)(glfwGetWindowUserPointer(context));
    auto& cam = win->cam;

    QM::vector<4> NDC_rayStart(
        ((float)x / (float)win->getWidth() - 0.5f) * 2.0f,
        ((float)y / (float)win->getHeight() - 0.5f) * -2.0f,
        -1.0f,
        1.0f);

    QM::vector<4> NDC_rayEnd(
        ((float)x / (float)win->getWidth() - 0.5f) * 2.0f,
        ((float)y / (float)win->getHeight() - 0.5f) * -2.0f,
        0.0f,
        1.0f);

    QM::matrix<4, 4> M = (cam->projMatrix() * cam->viewMatrix()).inverse();
    QM::vector<4> rayStart4 = M * NDC_rayStart;
    rayStart4 = (1 / rayStart4.get(4)) * rayStart4;
    QM::vector<3> rayStart(rayStart4.get(1), rayStart4.get(2), rayStart4.get(3));

    QM::vector<4> rayEnd4 = M * NDC_rayEnd;
    rayEnd4 = (1 / rayEnd4.get(4)) * rayEnd4;
    QM::vector<3> rayEnd(rayEnd4.get(1), rayEnd4.get(2), rayEnd4.get(3));

    QM::vector<3> direction = rayEnd - rayStart;
    direction = direction.normalise();

    QG::Asset* clicked = nullptr;
    float bestDist = INFINITY;

    for (auto& x : Assets::assets)
    {
        if (x->isShown())
        {
            float dist = x->interceptTime(rayStart, direction);
            if (dist < bestDist)
            {
                clicked = x;
                bestDist = dist;
        }
    }
    }

    if (bestDist != INFINITY && clicked != nullptr && clicked->OnClick != nullptr)
    {
        clicked->OnClick(clicked, act);
        return;
    }
        
    auto it = mouseFuncs.find(act);
    if (it != mouseFuncs.end())
        it->second();
    
}

void GLAPIENTRY
MessageCallback(GLenum source,
    GLenum type,
    GLuint id,
    GLenum severity,
    GLsizei length,
    const GLchar* message,
    const void* userParam)
{
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
        (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
        type, severity, message);
}

