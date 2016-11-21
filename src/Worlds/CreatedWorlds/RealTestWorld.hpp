#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

#include "../World.hpp"
#include "../LevelData.hpp"
#include "../../Utility/Options.hpp"

#include "../../Nodes/Physical/MoveNode.hpp"
#include "../../Nodes/Physical/ColisionHandler.hpp"
#include "../../Nodes/Graphical/StateNode.hpp"

#include "../../Entities/Game/Active/Player.hpp"

namespace bas {

	class RealTestWorld : public World
	{
	public:
							RealTestWorld(sf::RenderWindow* window, Input* input);
		void				CleanWorld();

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
		Ground*		m_Ground;
		TextureHolder		m_Textures;
		/*FontHolder			m_Fonts;
		SoundBufferHolder	m_Sounds;
		*/
		BaseNode*		m_SceneLayers[LayerCount];
		AABBColider*	m_Colider;
		StateNode*		m_Display;
		MoveNode*		m_Mover;
		Player*			m_Player;
			/*TextNode*		m_Title;
		ButtonArray*	m_ButtonArray;
		SpriteNode*		m_Mouse;
		SoundNode*		m_Audio;
		MusicPlayer		m_Music;*/
	};
}