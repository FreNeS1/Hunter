#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

#include "../../BaseNode.hpp"

namespace bas {

	enum ColiderTag
	{
		ColiderTag1,
		ColiderTag2,
		ColiderTag3
	};

	class ColisionNode : public BaseNode
	{
	public:
						~ColisionNode();
		bool			isActive() const;
		bool			isTag(ColiderTag tag) const;

	protected:
						ColisionNode(bool active, ColiderTag tags[], int numTags);
		virtual void	Scale(const sf::Vector2f* scale);
		virtual void	Scale(float xScale, float yScale);

	private:
		bool			m_Coliding;
		ColiderTag*		m_Tags;
		int				m_NumTags;
	};

}