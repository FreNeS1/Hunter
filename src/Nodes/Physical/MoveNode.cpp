#include "MoveNode.hpp"
#include <math.h>

namespace bas
{
	MoveNode::MoveNode(float mass, float drag, bool manual, float xSpeed, float ySpeed)
		: m_Mass(mass)
		, m_Drag(drag)
		, m_Manual(manual)
	{ 
		m_Acc[0] = 0.0f;
		m_Acc[1] = 0.0f;
		m_Force[0] = 0.0f;
		m_Force[1] = 0.0f;
		m_Speed[0] = xSpeed;
		m_Speed[1] = ySpeed;
	}

	void MoveNode::setForce(float xForce, float yForce)
	{
		m_Force[0] = xForce;
		m_Force[1] = yForce;
	}

	void MoveNode::setSpeed(float xSpeed, float ySpeed)
	{
		m_Speed[0] = xSpeed;
		m_Speed[1] = ySpeed;
	}

	void MoveNode::updateCurrent(sf::Time dt)
	{
		if (!m_Manual)
			simulateStep(dt);

		m_Parent->move(sf::Vector2f(m_Speed[0] * dt.asSeconds(), m_Speed[1] * dt.asSeconds()));
	}

	void MoveNode::simulateStep(sf::Time dt)
	{
		for (int i = 0; i < 2; i++)
		{
			m_Acc[i] = m_Force[i] / m_Mass;
			m_Speed[i] = (m_Speed[i] + dt.asSeconds() * m_Acc[i]) * pow(m_Drag, (dt.asSeconds()));

			if (m_Speed[i] < 0.001f && m_Speed[i] > -0.001f)
				m_Speed[i] = 0;
		}
	}
}