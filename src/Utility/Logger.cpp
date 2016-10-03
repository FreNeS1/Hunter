#include "Logger.hpp"

namespace bas {
	namespace utils {

		std::string FileLogger::m_File = "logger.log";
		sf::Clock FileLogger::m_Clock = sf::Clock();
		unsigned int FileLogger::m_NumWarnings = 0U;
		unsigned int FileLogger::m_NumErrors = 0U;

		void FileLogger::Set(const char *program_version, bool useDate)
		{
			m_NumWarnings = 0U;
			m_NumErrors = 0U;
			m_Clock.restart();

			if (useDate)
			{
				std::stringstream temp;

				time_t t = time(0);		//time now
				struct tm now;
				localtime_s(&now, &t);
				temp << "logs/log " << (now.tm_year + 1900) << '-' << (now.tm_mon + 1) << '-' << now.tm_mday
					<< '-' << now.tm_hour << '-' << now.tm_min << '-' << now.tm_sec << ".log";
				m_File = temp.str().c_str();
			}
			else
				m_File = "logger.log";

			FileIO::setTarget(m_File.c_str());

			std::stringstream ss;
			ss << "Log file, program version " << program_version << std::endl << std::endl;
			ss << "[ " << FileLogger::getTime() << " ms ] (INFO): Log file created" << std::endl;
			FileIO::write(ss.str().c_str());
		}

		void FileLogger::End()
		{
			std::stringstream ss;

			ss << std::endl;
			ss << "Program finished on " << FileLogger::getTime() << " ms with:" << std::endl;
			ss << "- " << m_NumWarnings << " warnings" << std::endl;
			ss << "- " << m_NumErrors << " errors" << std::endl;

			FileIO::setTarget(m_File.c_str());
			FileIO::append(ss.str().c_str());
		}

		void FileLogger::Log(FileLogger::LogType l_Type, const char* text)
		{
			std::stringstream ss;

			switch (l_Type) {
			case FileLogger::LogType::LOG_ERROR:
				ss << "[ " << FileLogger::getTime() << " ms ] ";
				ss << "(ERROR): ";
				FileLogger::m_NumErrors++;
				break;

			case FileLogger::LogType::LOG_WARNING:
				ss << "[ " << FileLogger::getTime() << " ms ] ";
				ss << "(WARNING): ";
				FileLogger::m_NumWarnings++;
				break;

			case FileLogger::LogType::LOG_INFO:
				ss << "[ " << FileLogger::getTime() << " ms ] ";
				ss << "(INFO): ";
				break;

			default:
				ss << "[ " << FileLogger::getTime() << " ms ] ";
				ss << "(DEBUG): ";
				break;
			}

			ss << text << std::endl;

			FileIO::setTarget(FileLogger::m_File.c_str());
			FileIO::append(ss.str().c_str());
		};

		int FileLogger::getTime() {
			sf::Time currentTime = m_Clock.getElapsedTime();
			int time = currentTime.asMilliseconds();
			return time;
		}
	}
}