#include "ButtonArray.hpp"

namespace bas {

	ButtonArray::ButtonArray(std::unique_ptr<Button> buttons[], int numButtons, float width, float height, int align)
		: BaseNode()
		, m_Width(width)
		, m_Height(height)
		, m_NumButtons(numButtons)
	{
		m_Buttons = new Button*[numButtons];

		for (int i = 0; i < numButtons; i++)
		{
			m_Buttons[i] = buttons[i].get();
			attachChild(std::move(buttons[i]));
		}

		/* The vertical is nondependant on the alignment */

		float maxHeight = 0;
		float margin = 0;
		float offset = 0;

		for (int i = 0; i < numButtons; i++)
		{
			maxHeight += (float)m_Buttons[i]->getHeight();
		}

		margin = ((float)m_Height - maxHeight) / (float)(numButtons - 1);
		if (margin < 0)
			utils::FileLogger::Log(utils::FileLogger::LogType::LOG_WARNING, "Graphical error, Button container is too small");

		for (int i = 1; i < numButtons; i++)
		{
			offset += margin + m_Buttons[i - 1]->getHeight();
			m_Buttons[i]->move(0.0f, offset);
		}


		/* Then we do the horizontal */

		if (align == -1) {}		// -1 = Align left

		else if (align == 1)	// 1 = Align right
		{
			for (int i = 0; i < m_NumButtons; i++)
			{
				m_Buttons[i]->move(sf::Vector2f((m_Width - m_Buttons[i]->getWidth()), 0.0f));
			}
		}

		else if (align == 0)	// 0 = Align middle
		{
			for (int i = 0; i < m_NumButtons; i++)
			{
				m_Buttons[i]->move(sf::Vector2f((m_Width - m_Buttons[i]->getWidth()) / 2.0f, 0.0f));
			}
		}

		else
			utils::FileLogger::Log(utils::FileLogger::LogType::LOG_WARNING, "Graphical error, Button container has invalid align; aligning left");
	}

	ButtonArray::~ButtonArray()
	{
		delete m_Buttons;
	}

	void ButtonArray::Interact(Input* input)
	{
		for (int i = 0; i < m_NumButtons; i++)
		{
			m_Buttons[i]->Interact(input);
		}
	}

}