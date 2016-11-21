#pragma once

#include "Colision/ColisionNode.hpp"
#include "Colision/ColisionAABB.hpp"
#include "Colision/ColisionCircle.hpp"

namespace bas {

	class Colider {
	public:
		static bool Colide(const CircleColider& c1, const CircleColider& c2);
		static bool Colide(const AABBColider& b1, const AABBColider& b2);
		static bool Colide(const AABBColider& b, const CircleColider& c);
		static bool Colide(const CircleColider& c, const AABBColider& b);
		static bool Colide(const AABBColider& b, const sf::Vector2f p1, sf::Vector2f p2);
		static bool Colide(const CircleColider& c, const sf::Vector2f p1, sf::Vector2f p2);
	};
}