#include "RNG.hpp"

namespace bas {
	namespace utils {

		unsigned short Randomizer::m_PreviousValue = 0;

		void Randomizer::SetSeed(unsigned short seed)
		{
			m_PreviousValue = seed;
		}

		unsigned short Randomizer::Randomize()
		{
			if (m_PreviousValue == 0x560A)
				m_PreviousValue = 0;

			unsigned short aux1 = m_PreviousValue << 8;
			aux1 = aux1 ^ m_PreviousValue;
			m_PreviousValue = ((m_PreviousValue & 0xFF) << 8) | ((aux1 & 0xFF00) >> 8);
			aux1 = (aux1 << 1) ^ m_PreviousValue;
			unsigned short aux2 = (aux1 >> 1) ^ 0xFF80;
			if ((aux1 & 1) == 0)
				m_PreviousValue = aux2 ^ 0x1FF4;
			else
				m_PreviousValue = aux2 ^ 0x8180;

			return m_PreviousValue;
		}

		float Randomizer::GetRandom(float rangeMin, float rangeMax)
		{
			return ((float)Randomize() / 65535) * (rangeMax - rangeMin) + rangeMin;
		}

		int Randomizer::GetRandomWhole(int rangeMin, int rangeMax)
		{
			return (int)(((float)Randomize() / 65535) * (rangeMax - rangeMin) + rangeMin);
		}

		bool Randomizer::GetRamdomBool(float ratio)
		{
			return ((float)Randomize() / 65535) < ratio;
		}

	}
}