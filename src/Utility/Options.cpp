#include "Options.hpp"

namespace bas {
	namespace utils {

		bool toBool(int s) 
		{
			return s == 1;
		}

		Options::Options(const std::string& file)
			: m_File(file)
		{ }

		bool Options::loadOptions()
		{
			if (!getFromFile())
			{
				repairOptions();
				return false;
			}
			return true;
		}

		void Options::repairOptions()
		{
			m_Width = WIDTH_DEFAULT;
			m_Height = HEIGHT_DEFAULT;
			m_Fullscreen = toBool(FULLSCREEN_DEFAULT);
			m_FixedFps = toBool(FIXEDFPS_DEFAULT);
			m_MaxFps = MAXFPS_DEFAULT;
			m_FixedUps = toBool(FIXEDUPS_DEFAULT);
			m_MaxUps = MAXUPS_DEFAULT;
			m_DebugMode = toBool(DEBUGMODE_DEFAULT);

			std::stringstream ss;

			ss << "Options file. Modify values at your onw risk." << std::endl;
			ss << "Width = " << WIDTH_DEFAULT << ";" << std::endl;
			ss << "Height = " << HEIGHT_DEFAULT << ";" << std::endl;
			ss << "Fullscreen = " << FULLSCREEN_DEFAULT << ";" << std::endl;
			ss << "FixedFps = " << FIXEDFPS_DEFAULT << ";" << std::endl;
			ss << "MaxFps = " << MAXFPS_DEFAULT << ";" << std::endl;
			ss << "FixedUps = " << FIXEDUPS_DEFAULT << ";" << std::endl;
			ss << "MaxUps = " << MAXUPS_DEFAULT << ";" << std::endl;
			ss << "DebugMode = " << DEBUGMODE_DEFAULT << ";";

			FileIO::setTarget(m_File);
			FileIO::write(ss.str());
		}

		/************/

		int Options::getWidth() const
		{
			return m_Width;
		}

		int Options::getHeight() const
		{
			return m_Height;
		}

		bool Options::getFullscreen() const
		{
			return m_Fullscreen;
		}

		bool Options::getFixedFps() const
		{
			return m_FixedFps;
		}

		int Options::getMaxFps() const
		{
			return m_MaxFps;
		}

		bool Options::getFixedUps() const
		{
			return m_FixedUps;
		}

		int Options::getMaxUps() const
		{
			return m_MaxUps;
		}

		bool Options::getDebugMode() const
		{
			return m_DebugMode;
		}

		/******************/

		int Options::getValue(int location, const std::string& contents)
		{
			m_Start = m_Indeces[location * 2];
			m_End = m_Indeces[(location * 2) + 1];
			std::string s = contents.substr(m_Start, m_End - m_Start);
			return strtol(s.c_str(), NULL, 0);
		}

		bool Options::getFromFile()
		{
			FileIO::setTarget(m_File);
			std::string contents = FileIO::read();
			std::string s;

			if (getContents(contents))		// MANUALLY HANDLE EACH ONE
			{
				m_Width = getValue(WIDTH_LOCATION, contents);
				if (m_Width < 240)
				{
					utils::FileLogger::Log(utils::FileLogger::LogType::LOG_WARNING, "Width value too small!");
					return false;
				}

				m_Height = getValue(HEIGHT_LOCATION, contents);
				if (m_Height < 135)
				{
					utils::FileLogger::Log(utils::FileLogger::LogType::LOG_WARNING, "Height value too small!");
					return false;
				}

				m_Fullscreen = toBool(getValue(FULLSCREEN_LOCATION, contents));

				m_FixedFps = toBool(getValue(FIXEDFPS_LOCATION, contents));

				m_MaxFps = getValue(MAXFPS_LOCATION, contents);
				if (m_MaxFps < 1)
				{
					utils::FileLogger::Log(utils::FileLogger::LogType::LOG_WARNING, "MaxFps must be greater than 0! We recommend at least 30");
					return false;
				}

				m_FixedUps = toBool(getValue(FIXEDUPS_LOCATION, contents));

				m_MaxUps = getValue(MAXUPS_LOCATION, contents);
				if (m_MaxUps < 1)
				{
					utils::FileLogger::Log(utils::FileLogger::LogType::LOG_WARNING, "MaxUps must be greater than 0! We recomend at least 100");
					return false;
				}

				m_DebugMode = toBool(getValue(DEBUGMODE_LOCATION, contents));
				if (m_DebugMode)
					utils::FileLogger::Log(utils::FileLogger::LogType::LOG_INFO, "Starting up in debug mode");

				return true;
			}
			return false;
		}

		bool Options::getContents(const std::string& contents)
		{
			if (contents == "")
			{
				return false;
			}
			else
			{
				std::size_t found = 1;
				std::size_t prev = 0;
				int i = 0;

				while (prev != std::string::npos)
				{
					found = contents.find("=", prev + 1);
					m_Indeces[i] = found + 1;
					found = contents.find(";", found);
					m_Indeces[i + 1] = found;

					i += 2;
					prev = found;
				}

				return true;
			}
		}
	}
}