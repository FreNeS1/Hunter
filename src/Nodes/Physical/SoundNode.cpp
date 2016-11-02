#include "SoundNode.hpp"

namespace bas
{
	SoundNode::SoundNode(sf::Sound sounds[], int numSounds)
		: m_Sounds()
		, m_NumSounds(numSounds)
	{
		for (int i = 0; i < numSounds; i++)
			m_Sounds.push_back(sounds[i]);
	}

	void SoundNode::Play(int ID)
	{
		if (ID < 0 || ID >= m_NumSounds)
			utils::FileLogger::Log(utils::FileLogger::LogType::LOG_WARNING, "Trying to play a non-existing sound");
		else
			m_Sounds[ID].play();
	}
}