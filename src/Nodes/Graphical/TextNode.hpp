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
							TextNode(const sf::Font& font, unsigned int size = 20, sf::Color color = sf::Color::White, sf::Uint32 style = 0);
							
							TextNode(const TextNode& that);
		TextNode&			operator=(const TextNode& that);

		void				setText(std::string const& text);
		void				setColor(sf::Color color);
		void				setSize(int size);

		/*override*/ void	Scale(float xScale, float yScale);
		/*override*/ void	SetScale(float xScale, float yScale);

		std::string	const&	getText() const;
		int					getSize() const;
		float				getWidth() const;
		float				getHeight() const;

		int					getSizeFor(float width, float height);		// Can't be const because they check the scale by resizing
		int					getMaxSizeFor(float width, float height);

	private:
		/*override*/ void	drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		sf::Text		m_Text;
		float			m_ScaleX;
		float			m_ScaleY;
	};

	typedef std::unique_ptr<TextNode> TextNodePtr;
}