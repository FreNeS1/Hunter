#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

#include "../BaseNode.hpp"

namespace bas {

	typedef std::unique_ptr<SoundNode> SoundNodePtr;
	
	class SoundNode : public BaseNode
	{
	public:
				SoundNode(sf::Sound sounds[], int numSounds);
		void	Play(int ID);

	private:
		std::vector<sf::Sound>	m_Sounds;
		int						m_NumSounds;
	};

}