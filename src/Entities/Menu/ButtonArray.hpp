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
		bool		getPressed(int i);
		bool		getClicked(int i);
		int			getLength();
		void		setPressed(int i, bool state);

	private:
		float		m_Width;
		float		m_Height;
		Button**	m_Buttons;
		int			m_NumButtons;

		int			m_Selected;
		bool		m_Activation;
	};

}
