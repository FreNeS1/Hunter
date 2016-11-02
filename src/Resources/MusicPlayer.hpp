#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

#include <map>

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Audio/Music.hpp>

#include "../Utility/Logger.hpp"

namespace bas {

	namespace Music
	{
		const int MENU[] = { 0 };

		enum ID
		{
			Menu,

			/* DEBUG */
			Debug1,
			Debug2,
			Debug3,
			Debug4,
			Debug5
		};

		static std::string paths[] = { "res/Music/dark fallout.ogg" };
	}

	class MusicPlayer : private sf::NonCopyable
	{
	public:
				MusicPlayer(float volume = 100.0f, bool loop = true);
		void	load(Music::ID ID, std::string path);

		void	setVolume(float volume);
		void	setLoop(bool loop);

		void	Play(Music::ID track);
		void	Pause(bool paused);				// Can be used to unpause;
		void	Stop();

	private:
		sf::Music							m_Music;
		std::map<Music::ID, std::string>	m_Filenames;
		float								m_Volume;
		bool								m_Loop;
	};
}