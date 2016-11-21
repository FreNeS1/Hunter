#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

/*
* USAGE: This node should be added whenever something
* might move with newtonian physics. You can apply
* force and let math work it's way or modify speed
* and simulate the movement yourself.
*/

#include "../BaseNode.hpp"

namespace bas {

	typedef std::unique_ptr<MoveNode> MoveNodePtr;
	
	class MoveNode : public BaseNode
	{
	public:
				MoveNode(float mass, float drag, bool manual = false, float xSpeed = 0, float ySpeed = 0);

		void	setForce(float xForce, float yForce);
		void	setSpeed(float xSpeed, float ySpeed);

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