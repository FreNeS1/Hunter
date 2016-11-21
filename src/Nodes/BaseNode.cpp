#include "BaseNode.hpp"

namespace bas {

	BaseNode::BaseNode()
		: m_Children()
		, m_Parent(nullptr)
		, m_Active(true)
	{ }

	BaseNode::BaseNode(const BaseNode& that)
	{
		m_Parent = that.m_Parent;
		m_Children = that.m_Children;
		m_Active = that.m_Active;
	}

	BaseNode::~BaseNode()
	{
		m_Parent->detachChild(*this);
	}

	BaseNode& BaseNode::operator=(const BaseNode& that)
	{
		if (this != &that)
		{
			m_Parent = that.m_Parent;
			m_Children = that.m_Children;
			m_Active = that.m_Active;
		}
		return *this;
	}

	void BaseNode::attachChild(Ptr newChild)
	{
		newChild->m_Parent = std::make_shared<BaseNode>(this);
		m_Children.push_back(std::move(newChild));
	}

	BaseNode::Ptr BaseNode::detachChild(const BaseNode& node)
	{
		auto found = std::find_if(m_Children.begin(), m_Children.end(),
			[&](Ptr& p) -> bool {return (&node == p.get()); });

		if (found != m_Children.end())
		{
			Ptr result = std::move(*found);
			result->m_Parent = nullptr;
			m_Children.erase(found);
			return result;
		}
		else
		{
			utils::FileLogger::Log(utils::FileLogger::LogType::LOG_ERROR, "Trying to detatch an unknow child from a parent!");
			return nullptr;
		}
	}

	bool BaseNode::setActive(bool active)
	{
		if (m_Parent != nullptr)
		{
			if (m_Parent->getActive())
			{
				m_Active = active;
				return true;
			}
			else
				return false;
		}
		else
		{
			m_Active = active;
			return true;
		}				
	}

	bool BaseNode::getActive()
	{
		return m_Active;
	}

	void BaseNode::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		if (m_Active)
		{
			states.transform *= getTransform();
			drawCurrent(target, states);
			drawChildren(target, states);
		}
	}

	void BaseNode::update(sf::Time dt)
	{
		if (m_Active)
		{
			updateCurrent(dt);
			updateChildren(dt);
		}
	}


	void BaseNode::drawCurrent(sf::RenderTarget&, sf::RenderStates) const { }

	void BaseNode::drawChildren(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (const Ptr& child : m_Children)
		{
			child->draw(target, states);
		}
	}


	void BaseNode::updateCurrent(sf::Time dt) { }

	void BaseNode::updateChildren(sf::Time dt)
	{
		for (const Ptr& child : m_Children)
		{
			child->update(dt);
		}
	}


	sf::Transform BaseNode::getWorldTransform() const
	{
		sf::Transform transform = sf::Transform::Identity;

		for (const BaseNode* node = this; node != nullptr; node = node->m_Parent)
			transform = node->getTransform() * transform;

		return transform;
	}

	sf::Vector2f BaseNode::getWorldPosition() const
	{
		return getWorldTransform() * sf::Vector2f();
	}
}