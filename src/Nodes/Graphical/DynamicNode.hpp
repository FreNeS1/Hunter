#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

/*
* USAGE: Implementing this node gives multiple animations to an object
* the animation can be customized and changed mid run. This animations
* must all reference a single texture file.
*/

#include "SpriteNode.hpp"

namespace bas {

	struct Animation
	{
	public:
									Animation(std::string const& name, int xOffset, int yOffset, int frameWidth, int height, int frames, float duration, bool loop);
		std::string const&			getName() const;
		bool						getLoop() const;
		float						getDuration() const;
		int							getNumFrames() const;
		std::vector<sf::IntRect>	m_Frames;
	
	private:
		std::string					m_Name;
		bool						m_Loop;
		float						m_AnimDuration;
		int							m_NumFrames;
	};

	class DynamicNode : public SpriteNode
	{
	public:
						DynamicNode(const sf::Texture& texture);
						~DynamicNode();
		Animation*		createAnimation(std::string const& name, int xOffset, int yOffset, int frameWidth, int height, int numFrames, float duration, bool loop = false);
		bool			setAnimation(std::string const& name);
		std::string		getCurrentAnimationName() const;

	protected:
		void					setAnimation(Animation* animation);
		/*override*/ void		updateCurrent(sf::Time dt);

	private:
		Animation*				findAnimation(std::string const& name);

	private:
		std::vector<Animation>	m_AnimationList;
		Animation*				m_CurrentAnimation;
		int						m_CurrentFrame;
		std::string				m_CurrentAnimationName;
		float					m_CurrentAnimationTime;
	};

}