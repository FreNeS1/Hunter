#include "Player.hpp"

namespace bas {

	Player::Player(const sf::Texture& texture)
		: DynamicNode(texture)
	{
		MoveNodePtr Mover = MoveNodePtr(new MoveNode(0, 0, true));
		m_Mover = Mover.get();
		this->attachChild(std::move(Mover));

		m_CurrentAnim = "Spawn1";
		m_NextAnim = "Spawn2";
		this->createAnimation("Spawn1", 0, 0, 64, 80, 10, 10.0f, false);
		this->createAnimation("Spawn2", 0, 80, 64, 80, 10, 10.0f / 24.0f, false);
		this->setAnimation(m_CurrentAnim);
	}

	Player::~Player()
	{
		delete m_Mover;
	}

	Player::Player(const Player& that)
		: DynamicNode(that)
	{
		MoveNodePtr Mover = MoveNodePtr(m_Mover->;
		m_Mover = Mover.get();
		this->attachChild(std::move(Mover));
		m_CurrentAnim = that.m_CurrentAnim;
		m_NextAnim = that.m_NextAnim;
	}


	Player&	operator=(const Player& that);


	void Player::Interact(Input* input)
	{
		float xSpeed = 0;
		float ySpeed = 0;

		if (input->getInput((int)Action::RIGHT))
			xSpeed += 200;
		if (input->getInput((int)Action::LEFT))
			xSpeed -= 200;
		if (input->getInput((int)Action::UP))
			ySpeed -= 200;
		if (input->getInput((int)Action::DOWN))
			ySpeed += 200;

		m_Mover->setSpeed(xSpeed, ySpeed);

		if (this->getCurrentAnimationEnd())
		{
			this->setAnimation(m_NextAnim);
			std::string aux = m_NextAnim;
			m_NextAnim = m_CurrentAnim;
			m_CurrentAnim = aux;
		}
	}
}