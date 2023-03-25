#include "Cursor.h"

namespace QG
{
	Cursor::Cursor(cursorType type)
	{
		m_cursor = glfwCreateStandardCursor((int)type);
	}

	Cursor::~Cursor()
	{
		glfwDestroyCursor(m_cursor);
	}

}