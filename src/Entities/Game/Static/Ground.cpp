#include "Ground.hpp"

namespace bas {

	GroundData* GroundData::copyData()
	{
		GroundData* d = new GroundData();
		sf::Vector2f* pos1 = new sf::Vector2f[];
		sf::Vector2f* pos2 = new sf::Vector2f[];

		for (int i = 0; i < lenght; i++)
		{
			pos1[i] = position1[i];
			pos2[i] = position2[i];
		}

		d->position1 = pos1;
		d->position2 = pos2;
		d->lenght = lenght;

		return d;
	}

	Ground::Ground(GroundData* data)
	{
		m_GData = data;
	}
	
	Ground::Ground(const Ground& that)
	{
		m_GData = that.m_GData->copyData();
	}

	Ground::~Ground()
	{
		delete[] m_GData->position1;
		delete[] m_GData->position2;
		delete m_GData;
	}

	Ground& Ground::operator=(const Ground& that)
	{
		if (this != &that)
		{
			delete[] m_GData->position1;
			delete[] m_GData->position2;
			delete m_GData;
			m_GData = that.m_GData->copyData();
		}
		return *this;
	}

	sf::Vector2f Ground::getGround(int i, int point) const
	{
		if (i >= 0 && i < m_GData->lenght)
		{
			if (point == 0)
				return m_GData->position1[i];
			if (point == 1)
				return m_GData->position2[i];
		}

		utils::FileLogger::Log(utils::FileLogger::LogType::LOG_WARNING, "Trying to access unexisting ground data!");
		return sf::Vector2f();
	}

	int Ground::getLenght() const
	{
		return m_GData->lenght;
	}
}