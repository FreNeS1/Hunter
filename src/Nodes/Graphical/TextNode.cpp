#include "TextNode.hpp"

namespace bas {

	TextNode::TextNode(const sf::Font& font, unsigned int size, sf::Color color, sf::Uint32 style)
		: m_Text()
		, m_ScaleX(1)
		, m_ScaleY(1)
	{
		m_Text.setFont(font);
		m_Text.setCharacterSize(size);
		m_Text.setFillColor(color);
		m_Text.setStyle(style);
	}

	void TextNode::setText(std::string const& text)
	{
		m_Text.setString(text);
	}

	void TextNode::setColor(sf::Color color)
	{
		m_Text.setFillColor(color);
	}

	void TextNode::setSize(int size)
	{
		m_Text.setCharacterSize(size);
	}

	std::string TextNode::getText() const
	{
		return m_Text.getString();
	}

	int TextNode::getSize()
	{
		return m_Text.getCharacterSize();
	}

	int TextNode::getSizeFor(float width, float height)
	{
		if (m_Text.getCharacterSize() != 100)
			m_Text.setCharacterSize(100);

		int size = (int)((100.0f / getHeight()) * height);
		m_Text.setCharacterSize(size);

		if (getWidth() <= width)
			m_Text.setCharacterSize(size);
		else
			m_Text.setCharacterSize((int)((width / getWidth()) * size));
		return size;
	}

	int TextNode::getMaxSizeFor(float width, float height)
	{
		if (m_Text.getCharacterSize() != 100)
			m_Text.setCharacterSize(100);

		int size = (int)((100.0f / getHeight()) * height);
		m_Text.setCharacterSize(size);

		if (getWidth() >= width)
			Scale(width / getWidth(), 1.0f);
		else
		{
			float r = width / getWidth();
			m_Text.setCharacterSize((int)(r * size));
			Scale(1.0f, 1 / r);
		}
		return size;

	}

	float TextNode::getWidth()
	{
		return m_Text.getLocalBounds().width * m_ScaleX;
	}

	float TextNode::getHeight()
	{
		std::string family = m_Text.getFont()->getInfo().family;

		if (family == "New weird font that doesnt default")
			return m_Text.getCharacterSize() * (82.0f / 100.0f) * m_ScaleY;
		else
			return m_Text.getCharacterSize() * (82.0f / 100.0f) * m_ScaleY;		// This works for Sansation, Prototype... (82/100)
	}

	void TextNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		this;
		target.draw(m_Text, states);
	}

	void TextNode::Scale(float xScale, float yScale) // The one that should be called when interacting with it
	{
		scale(xScale, yScale);
		m_ScaleX *= xScale;
		m_ScaleY *= yScale;
	}

	void TextNode::SetScale(float xScale, float yScale) // The one that should be called when interacting with it
	{
		setScale(xScale, yScale);
		m_ScaleX *= xScale;
		m_ScaleY *= yScale;
	}
}