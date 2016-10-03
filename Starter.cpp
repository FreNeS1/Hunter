#include "src/Basen.hpp"
#include "src/Utility/Logger.hpp"
#include <string>
#include <sstream>

int main()
{
	bas::Basen game("Basen Test", "HunterGame", "0.1.0");
	game.run();
}