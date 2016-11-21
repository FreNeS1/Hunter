#include "MusicPlayer.hpp"

namespace bas {

	MusicPlayer::MusicPlayer(float volume, bool loop)
		: m_Music()
		, m_Filenames()
		, m_Volume(volume)
		, m_Loop(loop)
	{ }

	void MusicPlayer::load(Music::ID ID, std::string path)
	{
		if (!m_Music.openFromFile(path))
		{
			std::stringstream ss;
			ss << "Failed to load music at " << path << ". Can't find or open file";
			utils::FileLogger::Log(utils::FileLogger::LogType::LOG_ERROR, ss.str());
		}
		m_Filenames[ID] = path;
	}

	void MusicPlayer::setVolume(float volume)
	{
		m_Volume = volume;
		m_Music.setVolume(volume);
	}

	void MusicPlayer::setLoop(bool loop)
	{
		m_Loop = loop;
		m_Music.setLoop(loop);
	}

	void MusicPlayer::Play(Music::ID theme)
	{
		std::string filename = m_Filenames[theme];
		if (!m_Music.openFromFile(filename))
		{
			std::stringstream ss;
			ss << "Failed to load music at " << filename;
			utils::FileLogger::Log(utils::FileLogger::LogType::LOG_ERROR, ss.str());
		}
		m_Music.setVolume(m_Volume);
		m_Music.setLoop(m_Loop);
		m_Music.play();
	}

	void MusicPlayer::Pause(bool pause)
	{
		if (pause)
			m_Music.pause();
		else
			m_Music.play();
	}

	void MusicPlayer::Stop()
	{
		m_Music.stop();
	}
}