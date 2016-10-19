#pragma once

#include "Button.hpp"
#include "SpriteButton.hpp"
#include "TextButton.hpp"

namespace bas {

	class ButtonArray : public BaseNode
	{
	public:
					ButtonArray(std::unique_ptr<Button> buttons[], int numButtons, float width, float height, int align);
					~ButtonArray();
		void		Interact(Input* input);

	private:
		float		m_Width;
		float		m_Height;
		Button**	m_Buttons;
		int			m_NumButtons;

	};

}
