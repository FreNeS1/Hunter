namespace bas {

	namespace Textures
	{
		enum ID
		{
			/* MENU */
			Background,
			Mouse,
			Button1,
			Button2,
			Button3,
			Button4,
			Button5,
			Button6,
			Button7,

			/* DEBUG*/
			Debug1,
			Debug2,
			Debug3,
			Debug4,
			Debug5
		};
	}

	namespace Fonts
	{
		enum ID
		{
			Prototype,
			Debug1,
			Debug2,
			Debug3,
			Debug4,
			Debug5
		};
	}
}

namespace sf
{
	/* forward declaration of all sf classes */
	class Texture;
	class Font;
}

namespace bas {
	template <typename Resource, typename Identifier>
	class ResourceHolder;	// Foward declaration of a base ResourceHolder

	typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
	typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
}
