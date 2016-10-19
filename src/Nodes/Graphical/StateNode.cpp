#include "StateNode.hpp"

namespace bas {

	StateNode::StateNode(const sf::Texture& texture, int stateWidth, int height, int states)
		: SpriteNode(texture)
		, m_States(states)
		, m_CurrentState(1)
		, m_FrameWidth(stateWidth)
		, m_Height(height)
	{
		setState(0);
	}

	int StateNode::getState()
	{
		return m_CurrentState;
	}

	void StateNode::setState(int state)
	{
		if (state != m_CurrentState)
		{
			if (state < m_States && state >= 0)
			{
				m_CurrentState = state;
				m_Sprite.setTextureRect(sf::IntRect(state * m_FrameWidth, 0, m_FrameWidth, m_Height));
			}
		}
	}
}