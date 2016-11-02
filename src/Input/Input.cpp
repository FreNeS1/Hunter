#include "Input.hpp"

namespace bas {

	Input::Input()
		: m_Focused(true)
		, m_MouseX(0)
		, m_MouseY(0)
	{
		load();
	}

	void Input::load()
	{
		for (int i = 0; i < (int)Action::TOTAL; i++)
		{
			for (int j = 0; j < NUM_TRIGGERS; j++)
			{
				m_Triggers[i][j] = config::config1[i][j];
			}
		}
	}

	void Input::set(InputType type, int code, bool value)
	{
		int Icode = getCode(type, code);

		int flank;
		if (value)
			flank = 1;
		else
			flank = -1;

		for (int i = 0; i < (int)Action::TOTAL; i++)
		{
			for (int j = 0; j < NUM_TRIGGERS; j++)
			{
				if (Icode == m_Triggers[i][j])
				{
					m_Input[i] = value;
					m_Flank[i] = flank;

					if (i < 4)
						m_MouseUsed = false;
				}
			}
		}
	}

	void Input::setMouse(int x, int y)
	{
		m_MouseX = x;
		m_MouseY = y;
		m_MouseUsed = true;
	}

	void Input::setFocused(bool focus)
	{
		m_Focused = focus;
	}

	bool Input::getInput(int k)
	{
		return m_Input[k];
	}

	bool Input::getPress(int k)
	{
		return m_Flank[k] == 1;
	}

	bool Input::getRelease(int k)
	{
		return m_Flank[k] == -1;
	}

	int Input::getMouseX()
	{
		return m_MouseX;
	}

	int Input::getMouseY()
	{
		return m_MouseY;
	}

	bool Input::getFocused()
	{
		return m_Focused;
	}

	bool Input::getMouseUsed()
	{
		return m_MouseUsed;
	}

	void Input::clear()
	{
		for (int i = 0; i < (int)Action::TOTAL; i++)
			m_Flank[i] = 0;
	}

	int Input::getCode(InputType type, int k)
	{
		return (int)type + k;
	}

}