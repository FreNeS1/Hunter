/*#pragma once

#include "../ButtonArray.hpp";

namespace bas {

	class OptionsMenu : public SpriteNode
	{
	public:
						OptionsMenu();
		virtual void	Interact(Input* input, bool overrideBounds);

		bool			getClicked();
		bool			getPressed();
		void			setPressed(bool state);

		virtual float	getWidth();
		virtual float	getHeight();

	private:
		bool			isOnBounds(Input* input);

	protected:
		unsigned short	m_State;

	private:
		bool			m_Stated;
		int				m_PrevState;

		bool			m_Clicked;
		bool			m_Pressed;
	};

}*/