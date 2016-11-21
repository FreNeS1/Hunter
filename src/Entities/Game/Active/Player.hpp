#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

#include "../../../Nodes/Graphical/DynamicNode.hpp"
#include "../../../Nodes/Physical/ColisionHandler.hpp"
#include "../../../Nodes/Physical/MoveNode.hpp"
#include "../../../Input/Input.hpp"

namespace bas {

	class Player : public DynamicNode
	{
	public:
				Player(const sf::Texture& texture);
				~Player();
				Player(const Player& that);
		Player&	operator=(const Player& that);

		void	Interact(Input* input);

	private:
		MoveNode*	m_Mover;
		std::string	m_CurrentAnim;
		std::string	m_NextAnim;

		/*AABBColider				m_Hitbody;
		CircleColider				m_HitGround;
		CircleColider				m_HitCeeling;
		std::vector<AABBColider>	m_Hitboxes;
		std::vector<CircleColider>	m_Hitcircles;*/
	};

}