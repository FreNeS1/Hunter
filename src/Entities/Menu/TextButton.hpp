#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

/*
* USAGE: Instead of a texture, this uses text
*/

#include "Button.hpp"
#include "../../Nodes/Graphical/TextNode.hpp"

namespace bas {

	class TextButton : public Button
	{
	public:
							TextButton(const sf::Font& font, std::string text, int size, sf::Color unactive, sf::Color highlighted, sf::Color pressed, sf::Color active);
							TextButton(const sf::Font& font, std::string text, float width, float height, sf::Color unactive, sf::Color highlighted, sf::Color pressed, sf::Color active, bool stretch = false);

		/*override*/ float	getWidth();
		/*override*/ float	getHeight();


	private:
		/*override*/ void	updateCurrent(sf::Time dt);

	private:
		TextNode*			m_Display;
		sf::Color			m_Colors[4];
		int					m_Previous;
	};

}
