#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

/*
* USAGE: We asign a number to each state
*	0 -> idle
*	1 -> highlighted
*	2 -> pressed
*	3 -> active
*/

#include "../../Nodes/BaseNode.hpp"
#include "../../Input/Input.hpp"

namespace bas {

	class Button : public BaseNode
	{
	public:
		virtual void	Interact(Input* input);
		bool			getPressed();
		virtual float	getWidth();
		virtual float	getHeight();

	protected:
		int			m_State;
		bool		m_Stated;

		bool		m_Pressed;
	};

}
