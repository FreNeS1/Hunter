#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

/*
* USAGE: Implementing this node gives an animation to an object
* the animation can be customized and references a single texture file. 
*/

#include "SpriteNode.hpp"

namespace bas {

	class AnimationNode : public SpriteNode
	{
	public:
							AnimationNode(const sf::Texture& texture, int frameWidth, int height, int frames, float duration, bool loop = true);								// For defining a sprite as the whole texture

	private:
		/*override*/ void	updateCurrent(sf::Time dt);

	private:
		float		m_ElapsedTime;
		float		m_AnimDuration;
		bool		m_Loop;
		int			m_CurrentFrame;
		int			m_Frames;
		int			m_FrameWidth;
		int			m_Height;
	};
	
}