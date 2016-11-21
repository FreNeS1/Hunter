#pragma once

namespace bas {

	namespace Textures
	{
		const int MENU[] = { 0, 1 };

		enum ID
		{
			/* MENU */
			MenuBackground,
			Mouse,

			/* DEBUG */
			Debug1,
			Debug2,
			Debug3,
			Debug4
		};

		static std::string paths[] = { "res/Textures/Space.jpg", "res/Textures/Mouse.png" };
	}

	namespace Fonts
	{
		const int MENU[] = { 0 };

		enum ID
		{
			/* MENU */
			Prototype,

			/* DEBUG */
			Debug1,
			Debug2,
			Debug3,
			Debug4
		};

		static std::string paths[] = { "res/Fonts/Prototype.ttf" };
	}

	namespace Sounds
	{
		const int MENU[] = { 0 };

		enum ID
		{
			/* MENU */
			buttonClick,

			/* DEBUG */
			Debug1,
			Debug2,
			Debug3,
			Debug4
		};

		static std::string paths[] = { "res/Sound/boop.wav" };
	}
}

namespace sf
{
	/* forward declaration of all sf classes */
	class Texture;
	class Font;
	class SoundBuffer;
}

namespace bas {
	template <typename Resource, typename Identifier>
	class ResourceHolder;	// Foward declaration of a base ResourceHolder

	typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
	typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
	typedef ResourceHolder<sf::SoundBuffer, Sounds::ID> SoundBufferHolder;
}
