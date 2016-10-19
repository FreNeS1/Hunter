#pragma once

/*
* AUTHOR: Jos� Antonio D�az Mata
*/

/*
* USAGE: This node should be added whenever something
* might move with newtonian physics. You can apply
* force and let math work it's way or modify speed
* and simulate the movement yourself.
*/

#include "../BaseNode.hpp"

namespace bas {

	class MoveNode : public BaseNode
	{
	public:
				MoveNode(float mass, float drag, bool manual = false, float xSpeed = 0, float ySpeed = 0);

		void	setForce(float xForce, float yForce);

	private:
		/*override*/ void	updateCurrent(sf::Time dt);
		void				simulateStep(sf::Time dt);

	private:
		bool	m_Manual;

		float	m_Mass;
		float	m_Drag;
		float	m_Force[2];
		float	m_Acc[2];
		float	m_Speed[2];
		float	m_Pos[2];
	};

}