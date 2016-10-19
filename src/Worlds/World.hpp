#pragma once 

/*
* AUTHOR: Jos� Antonio D�az Mata
*/

#include <SFML/System/NonCopyable.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>

#include "../Nodes/BaseNode.hpp"
#include "../Resources/ResourceHolder.hpp"
#include "../Resources/ResourceHolderNames.hpp"
#include "../Input/Input.hpp"

namespace bas {

	class World : private sf::NonCopyable
	{
	public:
						World(sf::RenderWindow* window, Input* input);	// Default constructor

		void			build();				// Builds and places the world
		virtual void	update(sf::Time dt);	// Update method
		void			draw();					// Draw method

	private:
		virtual void	loadResources();	// At the start of the world, we load it's resources
		virtual void	buildScene();		// At the start of the world, we create and position all nodes

	protected:
		sf::RenderWindow*	m_Window;		// The window
		sf::View			m_WorldView;	// The camera
		
		Input*		m_Input;		// Input to the world
		BaseNode	m_Scene;		// Main world node
	};

}