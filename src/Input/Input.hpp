#pragma once

/*
* AUTHOR: Jos� Antonio D�az Mata
*/

/*
* This first gets all the game class events as set(Type, code, value), flanks
* get stored in the m_flanks array, and input in the m_Input. For a set to be
* considered a valid option, m_Triggers for that action has to have that code
* in the array.
*
* When someone inputs something the both arrays return 1. As long as the input
* isn't cleared, flank won't return to zero. Normal usage is
* (Update the world -> Clear input) for each update tick
*/

#include <SFML/Window/Event.hpp>

namespace bas {

#define NUM_TRIGGERS 3

	enum class InputType /* This sets the basic offset of the input code */
	{
		Keyboard = 0,
		Mouse = sf::Keyboard::KeyCount,
		Controller = sf::Keyboard::KeyCount + sf::Mouse::ButtonCount,
	};

	enum class Action
	{
		UP,
		DOWN,
		LEFT,
		RIGHT,
		ATTACK,
		DEFEND,
		JUMP,
		ACTION,
		ENTER,
		TOTAL
	};

	namespace config {
		static int config1[(int)Action::TOTAL][NUM_TRIGGERS] =
		{
			/* UP */	{ sf::Keyboard::W ,		-2, -2 },
			/* DOWN */	{ sf::Keyboard::S ,		-2, -2 },
			/* LEFT */	{ sf::Keyboard::A,		-2, -2 },
			/* RIGHT */	{ sf::Keyboard::D,		-2, -2 },
			/* ATTACK */{ sf::Keyboard::Q ,		-2, -2 },
			/* DEFEND */{ sf::Keyboard::E ,		-2, -2 },
			/* JUMP */	{ sf::Keyboard::Space,	-2, -2 },
			/* ACTION */{ sf::Keyboard::F,		-2, -2 },
			/* ENTER */ { sf::Keyboard::Return, (int)InputType::Mouse + sf::Mouse::Left, -2 }
		};
	}

	class Input {

	public:
				Input();
		void	load();

		void	set(InputType type, int code, bool value);
		void	setMouse(int x, int y);
		void	setFocused(bool focus);

		bool	getInput(int k);
		bool	getPress(int k);
		bool	getRelease(int k);

		int		getMouseX();
		int		getMouseY();

		bool	getFocused();
		bool	getMouseUsed();
		
		void	clear();
		
	private:
		int		getCode(InputType type, int k);

	private:
		int 	m_Triggers[(int)Action::TOTAL][NUM_TRIGGERS];

		bool	m_Input[(int)Action::TOTAL];
		int		m_Flank[(int)Action::TOTAL];

		bool	m_Focused;
		bool	m_MouseUsed;

		int		m_MouseX;
		int		m_MouseY;
	};

}