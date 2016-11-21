#pragma once

#include <SFML/System/Vector2.hpp>
#include "../../../Utility/Logger.hpp"

namespace bas
{
	struct GroundData
	{
	public:
		GroundData*		copyData();

	public:
		int				lenght;
		sf::Vector2f*	position1 = new sf::Vector2f[];
		sf::Vector2f*	position2 = new sf::Vector2f[];
	};

	class Ground
	{
	public:
						Ground(GroundData* data);
						~Ground();
						Ground(const Ground& that);
		Ground&			operator=(const Ground& that);

		sf::Vector2f	getGround(int i, int p) const;
		int				getLenght() const;

	private:
		GroundData*	m_GData;
	};
}