#pragma once

#include "CreatedWorlds/MenuWorld.hpp"
#include "CreatedWorlds/TestWorld.hpp" /* TO BE DELETED */

namespace bas {
	namespace Worlds {

		static World* getStartWorld(sf::RenderWindow* window, Input* input)
		{
			return new MenuWorld(window, input);
		}

		static World* getWorld(int i, sf::RenderWindow* window, Input* input)
		{
			switch (i)
			{
			case MainMenu:
				return new MenuWorld(window, input);
				break;

			case Test:
				return new TestWorld(window, input);
				break;

			default:
				utils::FileLogger::Log(utils::FileLogger::LogType::LOG_ERROR, "Trying to initialize an unexisting world!");
				return nullptr;
				break;
			}
		}
	}
}