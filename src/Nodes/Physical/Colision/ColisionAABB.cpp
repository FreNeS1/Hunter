#include "ColisionAABB.hpp"

namespace bas
{
	AABBColider::AABBColider(sf::Vector2f position, sf::Vector2f size, bool active, ColiderTag tags[], int numTags)
		: ColisionNode(active, tags, numTags)
		, m_Size(size)
	{ 
		this->move(position);
	}

	sf::Vector2f AABBColider::getSize() const
	{
		return m_Size;
	}

	void AABBColider::Scale(float xScale, float yScale)
	{
		m_Size = sf::Vector2f(m_Size.x * xScale, m_Size.x * yScale);
		scale(xScale, yScale);
	}

	void AABBColider::Scale(const sf::Vector2f* scaleFactor)
	{
		m_Size = sf::Vector2f(m_Size.x * scaleFactor->x, m_Size.x * scaleFactor->y);
		scale(scaleFactor->x, scaleFactor->y);
	}
}