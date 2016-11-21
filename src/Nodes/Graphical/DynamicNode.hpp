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
		
							Animation(const Animation& that);
		Animation&			operator=(const Animation& that);
									
		std::string const&	getName() const;
		bool				getLoop() const;
		float				getDuration() const;
		int					getNumFrames() const;
		sf::IntRect			getFrame(int index) const;
	
	private:
		std::vector<sf::IntRect>	m_Frames;
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

							DynamicNode(const DynamicNode& that);
		DynamicNode&		operator=(const DynamicNode& that);

		Animation*			createAnimation(std::string const& name, int xOffset, int yOffset, int frameWidth, int height, int numFrames, float duration, bool loop = false);
		bool				setAnimation(std::string const& name);
		std::string	const&	getCurrentAnimationName() const;
		bool				getCurrentAnimationEnd() const;

	protected:
		/*override*/ void	updateCurrent(sf::Time dt);

	private:
		void				setAnimation(Animation* animation);
		Animation*			findAnimation(std::string const& name);

	private:
		std::vector<Animation>	m_AnimationList;
		Animation*				m_CurrentAnimation;
		int						m_CurrentFrame;
		std::string				m_CurrentAnimationName;
		float					m_CurrentAnimationTime;
	};

	typedef std::unique_ptr<DynamicNode> DynamicNodePtr;
}