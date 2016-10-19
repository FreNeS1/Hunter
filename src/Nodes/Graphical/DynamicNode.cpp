#include "DynamicNode.hpp"

namespace bas {

	Animation::Animation(std::string const& name, int xOffset, int yOffset, int frameWidth, int height, int frames, float duration, bool loop)
		: m_Name(name)
		, m_Frames()
		, m_Loop(loop)
		, m_AnimDuration(duration)
		, m_NumFrames(frames)
	{
		for (int i = 0; i < frames; i++)
		{
			m_Frames.push_back(sf::IntRect(xOffset + frameWidth * i, yOffset, frameWidth, height));
		}
	}

	std::string const& Animation::getName() const
	{
		return m_Name;
	}

	bool Animation::getLoop() const
	{
		return m_Loop;
	}

	float Animation::getDuration() const
	{
		return m_AnimDuration;
	}

	int Animation::getNumFrames() const
	{
		return m_NumFrames;
	}

	/***********************************/

	DynamicNode::DynamicNode(const sf::Texture& texture)
		: SpriteNode(texture)
		, m_AnimationList()
		, m_CurrentAnimation()
		, m_CurrentFrame(0)
		, m_CurrentAnimationName()
		, m_CurrentAnimationTime()
	{
		updateCurrent(sf::Time::Zero);
	}

	DynamicNode::~DynamicNode()
	{
		m_CurrentAnimation = nullptr;
		delete m_CurrentAnimation;
	}

	Animation* DynamicNode::createAnimation(std::string const& name, int xOffset, int yOffset, int frameWidth, int height, int numFrames, float duration, bool loop)
	{
		m_AnimationList.push_back(Animation(name, xOffset, yOffset, frameWidth, height, numFrames, duration, loop));

		return &m_AnimationList.back();
	}

	Animation* DynamicNode::findAnimation(std::string const& name)
	{
		for (auto item = m_AnimationList.begin(); item != m_AnimationList.end(); item++)
		{
			if (item->getName() == name)
				return &*item;				
		}

		return nullptr;
	}

	bool DynamicNode::setAnimation(std::string const& name)
	{
		Animation* animation = findAnimation(name);

		if (animation != nullptr)
		{
			setAnimation(animation);
			return true;
		}

		return false;
	}

	void DynamicNode::setAnimation(Animation* animation)
	{
		m_CurrentAnimation = animation;
		m_CurrentAnimationName = animation->getName();
		m_CurrentAnimationTime = 0.0f;
	}

	std::string DynamicNode::getCurrentAnimationName() const
	{
		return m_CurrentAnimationName;
	}


	void DynamicNode::updateCurrent(sf::Time dt)
	{
		if (m_CurrentAnimation == nullptr)
			return;

		m_CurrentAnimationTime += dt.asSeconds();

		float animState = (m_CurrentAnimationTime / m_CurrentAnimation->getDuration());

		if (animState >= 1)
		{
			if (m_CurrentAnimation->getLoop())
			{
				animState = 0;
				m_CurrentAnimationTime = 0;
			}
			else
			{
				animState = 1;
				m_CurrentAnimationTime = m_CurrentAnimation->getDuration() * 1.2f;	// Avoid overflow;
			}
		}

		int currentFrame = (int)(animState * m_CurrentAnimation->getNumFrames());

		if (m_CurrentFrame != currentFrame)
		{
			m_CurrentFrame = currentFrame;
			sf::IntRect& currentRect = m_CurrentAnimation->m_Frames[currentFrame];
			m_Sprite.setTextureRect(sf::IntRect(currentRect));
		}
	}
}