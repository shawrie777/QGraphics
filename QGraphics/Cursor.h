#pragma once

#include "Core.h"

namespace QG
{
	enum class cursorType
	{
		NONE = 0,
		arrow = GLFW_ARROW_CURSOR,
		IBeam = GLFW_IBEAM_CURSOR,
		crosshair = GLFW_CROSSHAIR_CURSOR,
		hand = GLFW_HAND_CURSOR,
		Hresize = GLFW_HRESIZE_CURSOR,
		Vresize = GLFW_VRESIZE_CURSOR
	};

	class Cursor
	{
		friend class window;
	private:
		GLFWcursor* m_cursor;
	public:
		Cursor(cursorType type);
		~Cursor();
	};
}
