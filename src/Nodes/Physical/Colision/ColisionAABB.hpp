#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

#include "ColisionNode.hpp"

namespace bas {

	typedef std::unique_ptr<AABBColider> AABBColiderPtr;

	class AABBColider : public ColisionNode
	{
	public:
						AABBColider(sf::Vector2f position, sf::Vector2f size, bool active, ColiderTag tags[], int numTags);
		sf::Vector2f	getSize() const;

		void			Scale(const sf::Vector2f* scale);
		void			Scale(float xScale, float yScale);

	private:
		sf::Vector2f	m_Size;
	};

}