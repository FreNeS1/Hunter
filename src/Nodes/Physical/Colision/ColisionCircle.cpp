#include "ColisionCircle.hpp"

namespace bas
{
	CircleColider::CircleColider(sf::Vector2f position, float radius, bool active, ColiderTag tags[], int numTags)
		: ColisionNode(active, tags, numTags)
		, m_Radius(radius)
	{
		this->move(position);
	}

	float CircleColider::getRadius() const
	{
		return m_Radius;
	}

	void CircleColider::Scale(float xScale, float yScale)
	{
		/* We shouldn't scale circles if the scale factor is not equal, but we take the middle route*/
		m_Radius = m_Radius * ((xScale + yScale) / 2);
		scale(xScale, yScale);
	}

	void CircleColider::Scale(const sf::Vector2f* scaleFactor)
	{
		m_Radius = m_Radius * ((scaleFactor->x + scaleFactor->y) / 2);
		scale(scaleFactor->x, scaleFactor->y);
	}
}