#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

/*
* USAGE: Implementing this node gives states to an object
* when a state is called, it's the one being displayed.
*/

#include "SpriteNode.hpp"

namespace bas {

	class StateNode : public SpriteNode
	{
	public:
					StateNode(const sf::Texture& texture, int stateWidth, int height, int states);
		int			getState();
		void		setState(int state);

	private:
		int			m_States;
		int			m_CurrentState;
		int			m_FrameWidth;
		int			m_Height;
	};

}