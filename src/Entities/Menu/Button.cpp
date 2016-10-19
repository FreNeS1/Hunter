#include "Button.hpp"

namespace bas {

	void Button::Interact(Input* input)
	{
		if (input->getFocused())
		{
			if (input->getMouseX() > getWorldPosition().x && input->getMouseX() < (getWorldPosition().x + getWidth()))
			{
				if (input->getMouseY() > getWorldPosition().y && input->getMouseY() < (getWorldPosition().y + getHeight()))
				{
					if (!m_Pressed)
						m_State = 1;

					if (input->getPress((int)Action::ENTER))
						m_Stated = true;

					if (m_Stated)
						m_State = 2;

					if (input->getRelease((int)Action::ENTER) && m_Stated)
					{
						if (m_Pressed)
						{
							m_Pressed = false;
							m_State = 0;
						}
						else
						{
							m_Pressed = true;
							m_State = 3;
						}
					}
				}
				else
				{
					if (!m_Pressed)
						m_State = 0;
					else
						m_State = 3;
				}
			}
			else
			{
				if (!m_Pressed)
					m_State = 0;
				else
					m_State = 3;
			}

			if (!input->getInput((int)Action::ENTER))
			{
				m_Stated = false;
			}
		}
	}

	bool Button::getPressed()
	{
		return m_Pressed;
	}

	float Button::getWidth()
	{
		return 0;
	}

	float Button::getHeight()
	{
		return 0;
	}
}