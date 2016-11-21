#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

/*
* USAGE:
*
*	bas::utils::FileLogger Start([version], [nameOfFile]);
*	bas::utils::FileLogger::Log(bas::utils::FileLogger::LogType::[Type], [message]);
*	bas::utils::FileLogger::End();
*/

#include <SFML\System.hpp>
#include <sstream>
#include <ctime>
#include "FileIO.hpp"

namespace bas {
	namespace utils {

		class FileLogger : public sf::NonCopyable
		{
		public:
			enum class LogType
			{
				LOG_ERROR,
				LOG_WARNING,
				LOG_INFO,
				LOG_DEBUG
			};

			static void Set(const std::string& program_version = "noVersion", bool useDate = true);
			static void End();

			static void Log(FileLogger::LogType l_Type, const std::string& text);

		private:
								FileLogger();
			static std::string	getTime();

		private:
			static std::string			m_File;
			static sf::Clock			m_Clock;
			static unsigned int			m_NumWarnings;
			static unsigned int			m_NumErrors;
		};
	}
}