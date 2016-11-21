#pragma once

#include <string>

namespace bas {
	namespace Worlds {

		enum ID
		{
			MainMenu,
			Test,
			RealTest
		};

		static std::string paths[] = { "NOPATH", "NOPATH", "levels/TestLevel.lvl" };
		static std::string names[] = { "NONAME", "NONAME", "TestLevel" };
	}
}