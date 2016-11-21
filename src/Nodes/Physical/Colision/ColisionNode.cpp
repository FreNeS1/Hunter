#include "ColisionNode.hpp"

namespace bas
{
	ColisionNode::ColisionNode(bool active, ColiderTag tags[], int numTags)
		: m_Coliding(active)
		, m_Tags(tags)
		, m_NumTags(numTags)
	{ }

	ColisionNode::~ColisionNode()
	{
		delete[] m_Tags;
	}

	bool ColisionNode::isActive() const
	{
		return m_Active;
	}

	bool ColisionNode::isTag(ColiderTag tag) const
	{
		for (int i = 0; i < m_NumTags; i++)
			if (tag == m_Tags[i])
				return true;

		return false;
	}

	void ColisionNode::Scale(float xScale, float yScale) { }

	void ColisionNode::Scale(const sf::Vector2f* scale) { }
}