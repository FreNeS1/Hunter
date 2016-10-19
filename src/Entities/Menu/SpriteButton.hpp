#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

/*
* USAGE: Button with sprites
*/

#include "Button.hpp"
#include "../../Nodes/Graphical/StateNode.hpp"

namespace bas {

	class SpriteButton : public Button
	{
	public:
							SpriteButton(const sf::Texture& texture, float width, float height, int stateWidth, int stateHeight);

		/*override*/ float	getWidth();
		/*override*/ float	getHeight();

	private:
		/*override*/ void	updateCurrent(sf::Time dt);

	private:
		StateNode*	m_Display;
		float		m_Width;
		float		m_Height;
	};	

}
