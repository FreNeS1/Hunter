#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

#include "../../Nodes/BaseNode.hpp"
#include "../../Input/Input.hpp"

namespace bas {



	class Button : public BaseNode
	{
	private:
		enum State
		{
			STATE_IDLE,
			STATE_HIGHLIGHTED,
			STATE_PRESSED,
			STATE_ACTIVE
		};

	public:
						Button();
		virtual void	Interact(Input* input, bool overriden, bool overrideBounds);

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

}
