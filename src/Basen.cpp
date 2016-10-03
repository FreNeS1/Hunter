#include "Basen.hpp"

namespace bas {

	Basen::Basen(const char* name, const char* title, const char* version)
		: m_IsFocused(true)
		, m_Name(name)
		, m_DebugTitle(name)
		, m_Options("Options.stg")
		, m_Input()
	{
		/* First, we start up the logger and it's clock */
		utils::FileLogger::Set(version);

		/* First, we have to handle the settings */
		if (m_Options.loadOptions())
			utils::FileLogger::Log(utils::FileLogger::LogType::LOG_INFO, "Options file loaded");
		else
			utils::FileLogger::Log(utils::FileLogger::LogType::LOG_WARNING, "Options file corrupt, back to defaults");

		/* We initialize the random at seed 0*/
		utils::Randomizer::SetSeed(0);

		/* Then, we create the window and load the default world */
		m_Window = new sf::RenderWindow();
		if (m_Options.getFullscreen())
			m_Window->create(sf::VideoMode(m_Options.getWidth(), m_Options.getHeight()), title, sf::Style::Fullscreen);
		else
			m_Window->create(sf::VideoMode(m_Options.getWidth(), m_Options.getHeight()), title, sf::Style::Close);

		if (m_Options.getDebugMode())
			utils::FileLogger::Log(utils::FileLogger::LogType::LOG_DEBUG, "Window created");

		/* Now we only need to load the current world and request focus for the game*/
		m_CurrentWorld = new World(m_Window, &m_Input);
		m_CurrentWorld->build();
		m_Window->requestFocus();
	}

	Basen::~Basen()
	{
		/* Delete all the stuff I was using */
		delete m_CurrentWorld;
		delete m_Window;

		/* Close the log */
		utils::FileLogger::End();
	}

	void Basen::run()
	{
		/* We create a clock and if the time is set, we limit the render() and update() functions */

		sf::Clock clock;

		sf::Time fpsTimer = sf::Time::Zero;
		sf::Time upsTimer = sf::Time::Zero;

		sf::Time fpsStep = sf::seconds(1.0f / m_Options.getMaxFps());
		sf::Time upsStep = sf::seconds(1.0f / m_Options.getMaxUps());

		/* Main program loop */
		while (m_Window->isOpen())
		{
			sf::Time timeElapsed = clock.restart();
			m_DebugTimer += timeElapsed;
			fpsTimer += timeElapsed;
			upsTimer += timeElapsed;

			if (m_Options.getFixedFps())
			{
				if (fpsTimer > fpsStep)
				{
					fpsTimer -= fpsStep;
					render();
					if (m_Options.getDebugMode())
						m_DebugFrames++;
				}
			}
			else
			{
				render();
				if (m_Options.getDebugMode())
					m_DebugFrames++;
			}

			if (m_Options.getFixedUps())
			{
				if (upsTimer > upsStep)
				{
					upsTimer -= upsStep;
					update(upsStep);
					if (m_Options.getDebugMode())
						m_DebugUpdates++;
				}
			}
			else
			{
				update(timeElapsed);
				if (m_Options.getDebugMode())
					m_DebugUpdates++;
			}

			if (m_Options.getDebugMode() && m_DebugTimer > m_DebugTick)
			{
				std::stringstream ss;
				ss << m_Name << "  //  FPS: " << m_DebugFrames << " / UPS: " << m_DebugUpdates;
				m_DebugTitle = ss.str();

				m_DebugTimer -= m_DebugTick;
				m_DebugFrames = 0;
				m_DebugUpdates = 0;
			}
			processEvents();
		}
	}

	void Basen::processEvents()
	{
		sf::Event event;
		while (m_Window->pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::KeyPressed:
				handleInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handleInput(event.key.code, false);
				break;
			case sf::Event::Closed:
				m_Window->close();
				break;
			case sf::Event::GainedFocus:
				m_IsFocused = true;
				break;
			case sf::Event::LostFocus:
				m_IsFocused = false;
				break;
			}
		}
	}

	void Basen::update(sf::Time deltaTime)
	{
		if (m_IsFocused)
		{
			m_CurrentWorld->update(deltaTime);
			m_Input.clear();
		}
	}

	void Basen::render()
	{
		m_Window->clear(sf::Color::Black);
		m_CurrentWorld->draw();

		if (m_Options.getDebugMode())
			m_Window->setTitle(m_DebugTitle);

		m_Window->display();
	}

	void Basen::handleInput(sf::Keyboard::Key key, bool isPressed)
	{
		m_Input.set(Type::Keyboard, key, isPressed);
	}
}

/*
void Game::updateStatistics(sf::Time elapsedTime)
{
	mStatisticsUpdateTime += elapsedTime;
	mStatisticsNumFrames += 1;

	if (mStatisticsUpdateTime >= sf::seconds(1.0f))
	{
		mStatisticsText.setString(
			"Frames / Second = " + std::to_string(mStatisticsNumFrames) + "\n" +
			"Time / Update = " + std::to_string((mStatisticsUpdateTime.asMicroseconds() / mStatisticsNumFrames)) + "us");

		mStatisticsUpdateTime -= sf::seconds(1.0f);
		mStatisticsNumFrames = 0;
	}
}*/