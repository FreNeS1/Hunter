#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

#include "ColisionNode.hpp"

namespace bas {

	typedef std::unique_ptr<CircleColider> CircleColiderPtr;
	
	class CircleColider : public ColisionNode
	{
	public:
				CircleColider(sf::Vector2f position, float radius, bool active, ColiderTag tags[], int numTags);
		float	getRadius() const;

		void	Scale(const sf::Vector2f* scale);
		void	Scale(float xScale, float yScale);

	private:
		float	m_Radius;
	};

}