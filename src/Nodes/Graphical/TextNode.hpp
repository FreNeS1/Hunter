#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

/*
* USAGE: This is the simplest way of showing text on screen.
* the SFML library is compatible with .ttf files.
*/

#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>

#include "../BaseNode.hpp"

namespace bas {

	class TextNode : public BaseNode
	{
	public:
		explicit			TextNode(const sf::Font& font, unsigned int size = 20, sf::Color color = sf::Color::White, sf::Uint32 style = 0);
		void				setText(std::string const& text);
		void				setColor(sf::Color);
		void				setSize(int size);

		std::string			getText() const;
		int					getSize();
		int					getSizeFor(float width, float height);
		int					getMaxSizeFor(float width, float height);
		float				getWidth();
		float				getHeight();

		/*override*/ void	Scale(float xScale, float yScale);
		/*override*/ void	SetScale(float xScale, float yScale);

	private:
		/*override*/ void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		sf::Text		m_Text;
		float			m_ScaleX;
		float			m_ScaleY;
	};

}