#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

/*
* USAGE: This generates all randomnes within bas.
* It's a simple on call randomizer that is based on Super Mario 64.
* For better understanding watch https://www.youtube.com/watch?v=MiuLeTE2MeQ
* It allows for RNG manipulation, if you don't want it, just seed it with another random.
* It traces all range of shorts in an unordered manner so each number is almost equally likely.
*/

namespace bas {
	namespace utils {

		class Randomizer
		{
		public:
			static void SetSeed(unsigned short seed);
			static float GetRandom(float rangeMin, float rangeMax);
			static int GetRandomWhole(int rangeMin, int rangeMax);
			static bool GetRamdomBool(float ratio);

		private:
			static unsigned short Randomize();

		private:
			static unsigned short m_PreviousValue;
		};
	}
}