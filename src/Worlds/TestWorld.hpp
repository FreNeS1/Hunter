#pragma once

#include "World.hpp"

#include "../Nodes/Graphical/TextNode.hpp"
#include "../Nodes/Graphical/SpriteNode.hpp"
#include "../Nodes/Graphical/AnimationNode.hpp"
#include "../Nodes/Graphical/DynamicNode.hpp"
#include "../Nodes/Physical/MoveNode.hpp"

namespace bas {

	class TestWorld : public World
	{
	public:
		TestWorld(sf::RenderWindow* window, Input* input);

	private:
		/*overload*/ void	buildScene();		// At the start of the world, we create and position all nodes
		/*overload*/ void	loadResources();

	private:
		enum Layer		// All layers from bottom to top
		{
			Background,
			Game,
			UI,
			LayerCount	// Not an used layer, just counts them
		};

	private:
		TextureHolder	m_Textures;
		FontHolder		m_Fonts;

		BaseNode*		m_SceneLayers[LayerCount];

	};



}