#include "ColisionHandler.hpp"
#include <cmath>

/*
* AUTHOR: José Antonio Díaz Mata
*/

namespace bas {

	bool Colider::Colide(const CircleColider& c1, const CircleColider& c2)
	{
		float dx = c1.getWorldPosition().x - c2.getWorldPosition().x;
		float dy = c1.getWorldPosition().y - c2.getWorldPosition().y;
		float dr = c1.getRadius() + c2.getRadius();

		if (dx * dx + dy * dy < dr * dr)
			return true;

		return false;
	}

	bool Colider::Colide(const AABBColider& b1, const AABBColider& b2)
	{
		if (b1.getWorldPosition().x < b2.getWorldPosition().x + b2.getSize().x &&
			b1.getWorldPosition().x + b1.getSize().x > b2.getWorldPosition().x &&
			b1.getWorldPosition().y < b2.getWorldPosition().y + b2.getSize().y &&
			b1.getSize().y + b1.getWorldPosition().y > b2.getWorldPosition().y) {
			return true;
		}

		return false;
	}

	bool Colider::Colide(const AABBColider& b, const CircleColider& c)
	{
		/* We need to check the general relatve position of b and c */
		if (std::abs(c.getWorldPosition().x - b.getWorldPosition().x) < (b.getSize().x / 2))
		{
			/* We can check just the Y coordinates like 2 AABB */
			if (std::abs(c.getWorldPosition().y - b.getWorldPosition().y) < (b.getSize().y / 2) + c.getRadius())
			{
				return true;
			}
			return false;
		}

		if (std::abs(c.getWorldPosition().y - b.getWorldPosition().y) < (b.getSize().y / 2))
		{
			/* We can check just the X coordinates like 2 AABB */
			if (std::abs(c.getWorldPosition().y - b.getWorldPosition().y) < (b.getSize().y / 2) + c.getRadius())
			{
				return true;
			}
			return false;
		}

		/* If neither condition applies, we need to check the edges because the circle is not directly on any side of the AABB */
		float px = b.getWorldPosition().x;
		float py = b.getWorldPosition().y;

		if (c.getWorldPosition().x > px)
			px += b.getSize().x;
		if (c.getWorldPosition().y > py)
			py += b.getSize().y;

		/* Now check if the distance to de point is greater than the radius */
		float dx = c.getWorldPosition().x - px;
		float dy = c.getWorldPosition().y - py;
		float r = c.getRadius();

		if (dx * dx + dy * dy < r * r)
			return true;

		return false;
	}

	bool Colider::Colide(const CircleColider& c, const AABBColider& b)
	{
		return Colide(b, c);
	}

	bool Colider::Colide(const AABBColider& b, sf::Vector2f p1, sf::Vector2f p2)
	{
		/* noonat.github.io/intersect */
		sf::Vector2f delta = p2 - p1;
		float scaleX = 1.0f / delta.x;
		float scaleY = 1.0f / delta.y;

		float nearX, farX, nearY, farY, near, far;

		if (scaleX > 0)
		{
			nearX = (b.getWorldPosition().x - p1.x) * scaleX;
			farX = (b.getWorldPosition().x + b.getSize().x - p1.x) * scaleX;
		}
		else
		{
			farX = (b.getWorldPosition().x - p1.x) * scaleX;
			nearX = (b.getWorldPosition().x + b.getSize().x - p1.x) * scaleX;
		}

		if (scaleY > 0)
		{
			nearY = (b.getWorldPosition().y - p1.y) * scaleY;
			farY = (b.getWorldPosition().y + b.getSize().y - p1.y) * scaleY;
		}
		else
		{
			farY = (b.getWorldPosition().y - p1.y) * scaleY;
			nearY = (b.getWorldPosition().y + b.getSize().y - p1.y) * scaleY;
		}

		if (nearX > farY || nearY > farX)
			return false;

		if (nearX > nearY)
			near = nearX;
		else
			near = nearY;

		if (farX > farY)
			far = farY;
		else
			far = farX;

		if (near >= 1 || far <= 0)
			return false;

		return true;
	}

	bool Colider::Colide(const CircleColider& c, sf::Vector2f p1, sf::Vector2f p2)
	{
		/* Calculate projection point of c in segment (p1, p2) */
		sf::Vector2f d = p2 - p1;
		float mod = std::sqrt(d.x * d.x + d.y * d.y);
		sf::Vector2f dn = sf::Vector2f(d.x / mod, d.y / mod);
		d = (c.getWorldPosition() - p1);
		float proj = d.x * dn.x + d.y * dn.y;

		/* Check if d is in bounds (p1+r, p2+r)*/
		if (proj < -c.getRadius() || proj > mod + c.getRadius())
			return false;

		if (proj < 0)
		{
			/* Check if p1 is inside c */
			float dx = c.getWorldPosition().x - p1.x;
			float dy = c.getWorldPosition().y - p1.y;
			float r = c.getRadius();

			if (dx * dx + dy * dy < r * r)
				return true;

			return false;
		}

		if (proj > mod)
		{
			/* Check if p2 is inside c */
			float dx = c.getWorldPosition().x - p2.x;
			float dy = c.getWorldPosition().y - p2.y;
			float r = c.getRadius();

			if (dx * dx + dy * dy < r * r)
				return true;

			return false;
		}

		/* It's in bounds then. We check if the projection point is inside */
		sf::Vector2f p = p1 + dn * mod;
		float dx = c.getWorldPosition().x - p.x;
		float dy = c.getWorldPosition().y - p.y;
		float r = c.getRadius();

		if (dx * dx + dy * dy < r * r)
			return true;

		return false;
	}

}