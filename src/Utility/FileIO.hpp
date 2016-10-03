#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

/*
* USAGE: Set the target of reading and then use the functions
* when length or location are -1 they revert to their original
* values, fileLength and 0.
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
			static bool			swap(int location, int length, const char* text);
			static bool			append(const char* text);
			static std::string	read();
			static std::string	read(int location, int length);

		private:
			static bool			PrepareFile();
			static bool			fWrite(const char* text, int location, int length, int mode);
			static bool			fRead(int location, int length, std::string* text);

		private:
			static boost::filesystem::path	m_Target;
		};

	}
}