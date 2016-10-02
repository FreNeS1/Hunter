#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

/*
* USAGE: Set the target of reading and then use the functions 
*/

#include <fstream>
#include "Logger.hpp"
#include <boost/filesystem.hpp>

namespace bas {
	namespace utils {

		class FileLogger;

		class FileIO
		{
		public:
			static void			setTarget(const char* target);

			static bool			write(const char* text);
			static std::string	read();
			static bool			append(const char* text);
			static bool			write(int location, int lenght, const char* text);
			static std::string	read(int location, int lenght);

		private:
			static bool			PrepareFile();

		private:
			static boost::filesystem::path	m_Target;
		};

	}
}