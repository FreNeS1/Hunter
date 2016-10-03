#include "FileIO.hpp"

namespace bas {
	namespace utils {

		namespace fs = boost::filesystem;

		fs::path FileIO::m_Target("noTarget");

		void FileIO::setTarget(const char* target)
		{
			m_Target = target;
		}

		bool FileIO::write(const char* text)
		{
			if (PrepareFile())
				if (FileIO::fWrite(text, -1, -1, std::ofstream::out))
					return true;

			return false;
		}

		bool FileIO::swap(int location, int length, const char* text)
		{
			std::string aux;

			if (!fRead(-1, -1, &aux))
				return false;

			aux.replace(location, length, text);
			const char* out = aux.c_str();

			if (PrepareFile())
				if (FileIO::fWrite(out, -1, -1, std::ofstream::out))
					return true;

			return false;
		}

		bool FileIO::append(const char* text)
		{
			if (PrepareFile())
				if (FileIO::fWrite(text, -1, -1, std::ofstream::app))
					return true;

			return false;
		}

		std::string FileIO::read()
		{
			std::string aux;

			if (!fRead(-1, -1, &aux))
				return "";
			else
				return aux;
		}

		std::string FileIO::read(int location, int length)
		{
			std::string aux;

			if (!fRead(location, length, &aux))
				return "";
			else
				return aux;
		}


		/* Internal functions */

		bool FileIO::PrepareFile()	// Returns true if the file is capable of being writen to
		{
			if (fs::exists(m_Target))
			{
				if (fs::is_regular_file(m_Target))
					return true;
				else
				{
					std::string aux2 = m_Target.string();

					std::stringstream ss;
					ss << "Could not create or open file at " << m_Target;			
					FileLogger::Log(FileLogger::LogType::LOG_ERROR, ss.str().c_str());
					
					setTarget(aux2.c_str());
					return false;
				}
			}
			else
			{
				std::string aux = m_Target.string();
				std::size_t found = 0;
				found = aux.find_last_of("/\\");

				if (found > aux.size())
					return true;

				if (fs::exists(fs::path(aux.substr(0, found))))
					return true;

				fs::create_directories(fs::path(aux.substr(0, found)));

				std::stringstream ss;
				ss << "Could not find file folder, creating folder at " << aux.substr(0, found);
				FileLogger::Log(FileLogger::LogType::LOG_INFO, ss.str().c_str());

				setTarget(aux.c_str());
				return true;
			}
		}

		bool FileIO::fWrite(const char* text, int location, int length, int mode)
		{
			std::ofstream os(m_Target.string(), mode);

			if (os)
			{
				if (location != -1)
					os.seekp(location);

				if (length != -1)
					os.write(text, length);
				else
					os.write(text, strlen(text));

				os.close();
				return true;
			}

			std::string aux2 = m_Target.string();

			std::stringstream ss;
			ss << "Could not write file at " << m_Target;
			FileLogger::Log(FileLogger::LogType::LOG_ERROR, ss.str().c_str());

			setTarget(aux2.c_str());
			return false;
		}

		bool FileIO::fRead(int location, int length, std::string* text)
		{
			if ((length < 0 && length != -1) || (location < 0 && location != -1))
			{
				std::string aux2 = m_Target.string();

				std::stringstream ss;
				ss << "Invalid location or length reading file at " << m_Target;
				FileLogger::Log(FileLogger::LogType::LOG_ERROR, ss.str().c_str());

				setTarget(aux2.c_str());
				return false;
			}

			std::ifstream is(m_Target.string());

			if (is) {
				is.seekg(0, is.end);
				int end = (int)is.tellg();

				if (length > end || length == -1)
					length = end;

				char * buffer;

				if (location != -1)
				{
					is.seekg(location, is.beg);
					buffer = new char[length + 1];
					is.read(buffer, length);
					buffer[length] = '\0';
					is.close();
				}
				else
				{
					is.seekg(0, is.beg);
					buffer = new char[length + 1];
					is.read(buffer, length);
					buffer[length] = '\0';
					is.close();
				}

				*text = buffer;
				delete[] buffer;

				return true;
			}

			std::string aux2 = m_Target.string();

			std::stringstream ss;
			ss << "Could not open or read file at " << m_Target;
			FileLogger::Log(FileLogger::LogType::LOG_ERROR, ss.str().c_str());
			
			setTarget(aux2.c_str());
			return false;
		}
	}
}