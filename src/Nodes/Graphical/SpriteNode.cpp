#include "SpriteNode.hpp"

namespace bas {

	SpriteNode::SpriteNode(const sf::Texture& texture)
		: m_Sprite(texture)
	{ }

	SpriteNode::SpriteNode(const sf::Texture& texture, const sf::IntRect& textureRect)
		: m_Sprite(texture, textureRect)
	{ }

	SpriteNode::SpriteNode(const SpriteNode& that)
		: m_Sprite(that.m_Sprite)
	{ }

	void SpriteNode::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(m_Sprite, states);
	}

}