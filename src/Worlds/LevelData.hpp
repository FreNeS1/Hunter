#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

#include <string>

#include "WorldNumbers.hpp"
#include "../Utility/FileIO.hpp"
#include "../Entities/Game/Static/Ground.hpp"

namespace bas {
	
	struct LevelData
	{
	public:
		std::string	d_Name;
		GroundData*	d_GroundData = new GroundData();
	};

	static LevelData* LoadLevelData(Worlds::ID ID)
	{
			/* Create the data variable */
			LevelData* dataOut = new LevelData();

			/* Load the raw data */
			utils::FileIO::setTarget(Worlds::paths[ID].c_str());
			std::string rawData = utils::FileIO::read();
			dataOut->d_Name = Worlds::names[ID];

			/* Load utilities */
			std::size_t prev = 0;
			std::size_t found = 1;
			bool exitFlag = false;

			/* Load the ground */
			dataOut->d_GroundData->lenght = 0;
			prev = rawData.find("G", 0) + 2;
			found = prev + 1;
			exitFlag = false;

			while (!exitFlag)
			{
				float aux[4];

				for (int i = 0; i < 3; i++)
				{
					found = rawData.find(",", found);
					aux[i] = strtof(rawData.substr(prev, found - prev).c_str(), NULL);
					prev = found + 1;
					found += 2;
				}

				found = rawData.find(";", found);
				aux[3] = strtof(rawData.substr(prev, found - prev).c_str(), NULL);
				
				if (rawData[found + 1] == ';')
					exitFlag = true;
				else
				{
					prev = found + 1;
					found += 2;
				}

				sf::Vector2f* position = dataOut->d_GroundData->position1;
				*position = sf::Vector2f(aux[0], aux[1]);

				sf::Vector2f* direction = dataOut->d_GroundData->position2;
				*direction = sf::Vector2f(aux[2], aux[3]);

				dataOut->d_GroundData->position1++;
				dataOut->d_GroundData->position2++;
				dataOut->d_GroundData->lenght++;
			}

			dataOut->d_GroundData->position1 -= dataOut->d_GroundData->lenght;
			dataOut->d_GroundData->position2 -= dataOut->d_GroundData->lenght;

			/* Return the loaded data */
			return dataOut;
	}
}