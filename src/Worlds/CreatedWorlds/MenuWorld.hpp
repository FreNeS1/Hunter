#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

#include "../World.hpp"
#include "../../Utility/Options.hpp"

#include "../../Resources/ResourceHolder.hpp"
#include "../../Resources/ResourceHolderNames.hpp"

#include "../../Resources/MusicPlayer.hpp"

#include "../../Nodes/Graphical/SpriteNode.hpp"
#include "../../Nodes/Physical/SoundNode.hpp"
#include "../../Entities/Menu/ButtonArray.hpp"

namespace bas {
	
	class MenuWorld : public World
	{
	public:
							MenuWorld(sf::RenderWindow* window, Input* input);
							~MenuWorld();

		/*overload*/ void	update(sf::Time dt);

	private:
		/*overload*/ void	loadResources();
		/*overload*/ void	buildScene();

	protected:
		enum Layer		// All layers from bottom to top
		{
			Background,
			Menu,
			UI,
			LayerCount	// Not an used layer, just counts them
		};

	protected:
		TextureHolder		m_Textures;
		FontHolder			m_Fonts;
		SoundBufferHolder	m_Sounds;
		
		BaseNode*		m_SceneLayers[LayerCount];
		SpriteNode*		m_Background;
		TextNode*		m_Title;
		ButtonArray*	m_ButtonArray;
		SpriteNode*		m_Mouse;
		SoundNode*		m_Audio;
		MusicPlayer		m_Music;
	};
}