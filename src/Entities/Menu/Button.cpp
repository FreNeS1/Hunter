#include "Button.hpp"

namespace bas {

	Button::Button()
		: m_Stated(false)
		, m_Pressed(false)
		, m_Clicked(false)
		, m_PrevState(0)
		, m_State(0)
	{ }

	void Button::Interact(Input* input, bool overriden, bool overrideBounds)
	{
		if (input->getFocused())
		{
			m_Clicked = false;
			m_PrevState = m_State;

			if (overriden && overrideBounds || !overriden && isOnBounds(input))
			{

				if (!m_Pressed)
					m_State = 1;

				if (input->getPress((int)Action::ENTER))
					m_Stated = true;

				if (m_Stated)
				{
					m_State = 2;
					if (m_PrevState != 2)
						m_Clicked = true;
				}

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
					if (m_Stated)
						m_State = 1;
					else
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

	bool Button::isOnBounds(Input* input)
	{
		if (input->getMouseX() > getWorldPosition().x && input->getMouseX() < (getWorldPosition().x + getWidth()))
			if (input->getMouseY() > getWorldPosition().y && input->getMouseY() < (getWorldPosition().y + getHeight()))
				return true;
		return false;
	}

	bool Button::getPressed()
	{
		return m_Pressed;
	}

	void Button::setPressed(bool state)
	{
		if (state)
			m_Clicked = true;
		m_Pressed = state;
	}

	bool Button::getClicked()
	{
		return m_Clicked;
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