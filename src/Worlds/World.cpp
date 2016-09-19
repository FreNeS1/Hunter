#include "World.hpp"

namespace bas {

	World::World(sf::RenderWindow* window, Input* input)
		: m_Window(window)
		, m_WorldView(window->getDefaultView())
		, m_Scene()
		, m_Input(input)
	{ }

	void World::build()
	{
		loadResources();
		buildScene();
	}

	void World::loadResources() { /* Here we should load all the resources needed for the world (textures and such) */ }

	void World::buildScene() { /* Here we place all the objects and link everything together */ }

	void World::draw()
	{
		/* Here we draw the world, this shouldn't be accessed since everything should be placed on the scene */

		m_Window->setView(m_WorldView);
		m_Window->draw(m_Scene);
	}

	void World::update(sf::Time dt)
	{
		/* Here we update the world, dt is very important unless constant UPS is fixed allways */

		m_Scene.update(dt);
	}

}