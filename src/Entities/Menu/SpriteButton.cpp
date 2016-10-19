#include "SpriteButton.hpp"

namespace bas {

	SpriteButton::SpriteButton(const sf::Texture& texture, float width, float height, int stateWidth, int stateHeight)
	{
		m_Stated = false;
		m_State = 0;
		m_Width = width;
		m_Height = height;

		std::unique_ptr<StateNode> display(new StateNode(texture, stateWidth, stateHeight, 4));
		display->setScale(sf::Vector2f(width / (float)stateWidth, height / (float)stateHeight));
		m_Display = display.get();
		attachChild(std::move(display));
	}

	void SpriteButton::updateCurrent(sf::Time dt)
	{
		m_Display->setState(m_State);
	}

	float SpriteButton::getWidth()
	{
		return m_Display->getScale().x * m_Width;
	}

	float SpriteButton::getHeight()
	{
		return m_Display->getScale().y * m_Height;
	}
}