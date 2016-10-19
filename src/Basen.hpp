#pragma once

/*
* AUTHOR: José Antonio Díaz Mata
*/

#include "Includes.hpp"

namespace bas {

	class Basen
	{
	public:
				Basen(const char* name, const char* title, const char* version);
				~Basen();
		void	run();

	private:
		void	processEvents();
		void	handleInput(sf::Keyboard::Key key, bool isPressed);
		void    handleMouse(sf::Mouse::Button button, bool isPressed);
		void	update(sf::Time dt);
		void	render();

	private:
		sf::RenderWindow*	m_Window;
		World*				m_CurrentWorld;

		utils::Options		m_Options;
		Input				m_Input;

		const char*			m_Name;

		/* DEBUG */
		sf::Time			m_DebugTick = sf::seconds(1);
		sf::Time			m_DebugTimer = sf::Time::Zero;
		int					m_DebugFrames = 0;
		int					m_DebugUpdates = 0;

		std::string			m_DebugTitle;
	};
}