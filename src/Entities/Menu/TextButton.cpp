#include "TextButton.hpp"

namespace bas {

	TextButton::TextButton(const sf::Font& font, std::string text, int size, sf::Color unactive, sf::Color highlighted, sf::Color pressed, sf::Color active)
	{
		m_Stated = false;
		m_Pressed = false;
		m_Previous = 5;
		m_State = 0;

		m_Colors[0] = unactive;
		m_Colors[1] = highlighted;
		m_Colors[2] = pressed;
		m_Colors[3] = active;

		std::unique_ptr<TextNode> display(new TextNode(font, size, unactive));
		m_Display = display.get();
		m_Display->setText(text);

		m_Display->move(0, -getHeight() / 3.0f);		// Text position correction

		attachChild(std::move(display));
	}

	TextButton::TextButton(const sf::Font& font, std::string text, float width, float height, sf::Color unactive, sf::Color highlighted, sf::Color pressed, sf::Color active, bool stretch)
	{
		m_Stated = false;
		m_Pressed = false;
		m_Previous = 5;
		m_State = 0;

		m_Colors[0] = unactive;
		m_Colors[1] = highlighted;
		m_Colors[2] = pressed;
		m_Colors[3] = active;

		std::unique_ptr<TextNode> display(new TextNode(font, 100, unactive));
		m_Display = display.get();
		m_Display->setText(text);
		
		if (stretch)
			m_Display->getMaxSizeFor(width, height);
		else
			m_Display->getSizeFor(width, height);

		m_Display->move(0, -getHeight() / 3.0f);		// Text position correction

		attachChild(std::move(display));
	}

	void TextButton::updateCurrent(sf::Time dt)
	{
		if (m_State != m_Previous)
		{
			m_Previous = m_State;
			m_Display->setColor(m_Colors[m_State]);
		}
	}

	float TextButton::getWidth()
	{
		return m_Display->getWidth();
	}

	float TextButton::getHeight()
	{
		return m_Display->getHeight();
	}
}