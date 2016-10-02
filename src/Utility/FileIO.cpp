#include "FileIO.hpp"

namespace bas {
	namespace utils {

		namespace fs = boost::filesystem;

		fs::path m_Target = "noTarget";

		void FileIO::setTarget(const char* target)
		{
			m_Target = target;
		}

		bool FileIO::PrepareFile()	// Returns 1 when the file is ready
		{
			if (fs::exists(m_Target))
			{
				if (fs::is_regular_file(m_Target))
				{
					return 1;
				}
				return 0;
			}
			else
			{
				std::string aux = m_Target.string();
				std::size_t found = 0;
				found = aux.find_last_of("/\\");
				
				if (fs::exists(fs::path(aux.substr(0, found))))
					return 1;
				
				fs::create_directories(fs::path(aux.substr(0, found)));
				return 1;
			}
		}

		bool FileIO::write(const char* text)
		{
			std::ofstream os(m_Target.string());

			if (os)
			{
				os.write(text, strlen(text));
				if (!os)
				{
					std::stringstream ss;
					ss << "Could not write on the file " << m_Target;
					FileLogger::Log(FileLogger::LogType::LOG_ERROR, ss.str().c_str());
					return false;
				}
				os.close();
				return true;
			}
			std::stringstream ss;
			ss << "Could not open file at " << m_Target;
			FileLogger::Log(FileLogger::LogType::LOG_ERROR, ss.str().c_str());
			return false;
		}

		std::string FileIO::read()
		{
			std::ifstream is(m_Target.string());

			if (is) {
				is.seekg(0, is.end);
				int length = (int) is.tellg();
				is.seekg(0, is.beg);

				char * buffer = new char[length];
				is.read(buffer, length - 1);

				if (!is) // What is happening here I don't know,
				{
					std::stringstream ss;
					ss << "Could not read file at " << m_Target;
					FileLogger::Log(FileLogger::LogType::LOG_ERROR, ss.str().c_str());
				}
				is.close();
				std::string contents = buffer;
				delete[] buffer;
				return contents;
			}
			std::stringstream ss;
			ss << "Could not open file at " << m_Target;
			FileLogger::Log(FileLogger::LogType::LOG_ERROR, ss.str().c_str());
			return "";
		}

		bool FileIO::append(const char* text)
		{
			std::ofstream os(m_Target.string(), std::ofstream::app);

			if (os)
			{
				os.write(text, strlen(text));
				if (!os)
				{
					std::stringstream ss;
					ss << "Could not write on the file " << m_Target;
					FileLogger::Log(FileLogger::LogType::LOG_ERROR, ss.str().c_str());
					return false;
				}
				os.close();
				return true;
			}
			std::stringstream ss;
			ss << "Could not open file at " << m_Target;
			FileLogger::Log(FileLogger::LogType::LOG_ERROR, ss.str().c_str());
			return false;
		}

		bool FileIO::write(int location, int length, const char* text)
		{
			std::ofstream os(m_Target.string());

			if (os)
			{
				os.seekp(location);
				os.write(text, length);

				if (!os)
				{
					std::stringstream ss;
					ss << "Could not write on the file " << m_Target;
					FileLogger::Log(FileLogger::LogType::LOG_ERROR, ss.str().c_str());
					return false;
				}

				os.close();
				return true;
			}
			std::stringstream ss;
			ss << "Could not open file at " << m_Target;
			FileLogger::Log(FileLogger::LogType::LOG_ERROR, ss.str().c_str());
			return false;
		}

		std::string FileIO::read(int location, int length)
		{
			std::ifstream is(m_Target.string());

			if (is) {
				char * buffer = new char[length];
				is.seekg(location);
				is.read(buffer, length);

				if (!is)
				{
					std::stringstream ss;
					ss << "Could not read file at " << m_Target;
					FileLogger::Log(FileLogger::LogType::LOG_ERROR, ss.str().c_str());
				}

				is.close();
				std::string contents = buffer;
				delete[] buffer;
				return contents;
			}
			std::stringstream ss;
			ss << "Could not open file at " << m_Target;
			FileLogger::Log(FileLogger::LogType::LOG_ERROR, ss.str().c_str());
			return "";
		}
	}
}