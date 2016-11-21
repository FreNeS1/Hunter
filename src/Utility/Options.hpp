#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

/*
* USAGE: This generates an option file, that holds the options you can save.
* Options are handled manually, and if the values are wrong, it resets the
* whole file. You can also reset the whole file using repairOptions.
* For loading the options, you only need to call loadOptions.
*/

#include <sstream>
#include "FileIO.hpp"
#include "Logger.hpp"

namespace bas {
	namespace utils {

		class Options
		{
		public:

					Options(const std::string& file);
			bool	loadOptions();
			void	repairOptions();

			/* Here go all the calls for the options */
			int		getWidth() const;
			int		getHeight() const;
			bool	getFullscreen() const;
			bool	getFixedFps() const;
			int		getMaxFps() const;
			bool	getFixedUps() const;
			int		getMaxUps() const;
			bool	getDebugMode() const;

		private:
			bool	getFromFile();
			bool	getContents(const std::string& contents);
			int		getValue(int location, const std::string& contents);

		private:
			std::string m_File;
			std::size_t m_Indeces[50]; // Can manage up to 50 options
			std::size_t m_Start;
			std::size_t m_End;

			// HERE GO ALL THE OPTIONS

			/* Name for each */
			int			m_Height;
			int			m_Width;
			bool		m_Fullscreen;
			bool		m_FixedFps;
			int			m_MaxFps;
			bool		m_FixedUps;
			int			m_MaxUps;
			bool		m_DebugMode;

			/* Order of aperance */
			const int	WIDTH_LOCATION = 0;
			const int	HEIGHT_LOCATION = 1;
			const int	FULLSCREEN_LOCATION = 2;
			const int	FIXEDFPS_LOCATION = 3;
			const int	MAXFPS_LOCATION = 4;
			const int	FIXEDUPS_LOCATION = 5;
			const int	MAXUPS_LOCATION = 6;
			const int	DEBUGMODE_LOCATION = 7;
			
			/* Defaults in case of error */
			const int	WIDTH_DEFAULT = 1024;
			const int	HEIGHT_DEFAULT = 720;
			const int	FULLSCREEN_DEFAULT = 0;
			const int	FIXEDFPS_DEFAULT = 0;
			const int	MAXFPS_DEFAULT = 100;
			const int	FIXEDUPS_DEFAULT = 0;
			const int	MAXUPS_DEFAULT = 200;
			const int	DEBUGMODE_DEFAULT = 0;
		};

	}
}