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

	Animation::Animation(const Animation& that)
		: m_Name(that.m_Name)
		, m_Frames(that.m_Frames)
		, m_Loop(that.m_Loop)
		, m_AnimDuration(that.m_AnimDuration)
		, m_NumFrames(that.m_NumFrames)
	{ }

	Animation& Animation::operator=(const Animation& that)
	{
		if (this != &that)
		{
			m_Name = that.m_Name;
			m_Frames = that.m_Frames;
			m_Loop = that.m_Loop;
			m_AnimDuration = that.m_AnimDuration;
			m_NumFrames = that.m_NumFrames;
		}
		return *this;
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

	sf::IntRect Animation::getFrame(int index) const
	{
		return m_Frames[index];
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
		delete m_CurrentAnimation;
		m_CurrentAnimation = nullptr;
	}

	DynamicNode::DynamicNode(const DynamicNode& that)
		: SpriteNode(that)
		, m_AnimationList(that.m_AnimationList)
		, m_CurrentFrame(that.m_CurrentFrame)
		, m_CurrentAnimationName(that.m_CurrentAnimationName)
		, m_CurrentAnimationTime(that.m_CurrentAnimationTime)
	{
		m_CurrentAnimation = new Animation(*m_CurrentAnimation);
		updateCurrent(sf::Time::Zero);
	}

	DynamicNode& DynamicNode::operator=(const DynamicNode& that)
	{
		if (this != &that)
		{
			(SpriteNode)*this = that;
			m_AnimationList = that.m_AnimationList;
			m_CurrentFrame = that.m_CurrentFrame;
			m_CurrentAnimationName = that.m_CurrentAnimationName;
			m_CurrentAnimationTime = that.m_CurrentAnimationTime;
			m_CurrentAnimation = new Animation(*m_CurrentAnimation);
			updateCurrent(sf::Time::Zero);
		}
		return *this;
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
		m_CurrentFrame = 1;
		m_CurrentAnimationName = animation->getName();
		m_CurrentAnimationTime = 0.0f;
		updateCurrent(sf::Time::Zero);
	}

	std::string const& DynamicNode::getCurrentAnimationName() const
	{
		return m_CurrentAnimationName;
	}

	bool DynamicNode::getCurrentAnimationEnd() const
	{
		return m_CurrentAnimationTime >= m_CurrentAnimation->getDuration();
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
				animState = 0.999f;
				m_CurrentAnimationTime = m_CurrentAnimation->getDuration() * 1.2f;	// Avoid overflow;
			}
		}

		int currentFrame = (int)(animState * m_CurrentAnimation->getNumFrames());

		if (m_CurrentFrame != currentFrame)
		{
			m_CurrentFrame = currentFrame;
			sf::IntRect& currentRect = m_CurrentAnimation->getFrame(currentFrame);
			m_Sprite.setTextureRect(sf::IntRect(currentRect));
		}
	}
}