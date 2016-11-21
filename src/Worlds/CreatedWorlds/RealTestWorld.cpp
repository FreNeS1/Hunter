#include "RealTestWorld.hpp"

namespace bas {

	RealTestWorld::RealTestWorld(sf::RenderWindow * window, Input * input) : World(window, input)
		, m_Ground()
	{
		m_Delete = false;
		m_Exit = false;
		m_Next = Worlds::MainMenu;
	}

	void RealTestWorld::CleanWorld()
	{
		delete m_Ground;
	}

	void RealTestWorld::loadResources()
	{
		m_Textures.load(Textures::Debug1, "res/Textures/ButtonTest.png");
		m_Textures.load(Textures::Debug2, "res/Textures/SpriteTest.png");
		/*for each (int i in Textures::MENU)
			m_Textures.load(Textures::ID(i), Textures::paths[i]);

		for each (int i in Fonts::MENU)
			m_Fonts.load(Fonts::ID(i), Fonts::paths[i]);

		for each (int i in Sounds::MENU)
			m_Sounds.load(Sounds::ID(i), Sounds::paths[i]);

		for each (int i in Music::MENU)
			m_Music.load(Music::ID(i), Music::paths[i]);*/
	}

	void RealTestWorld::buildScene()
	{
		/* Load the ground */
		m_Ground = new Ground(LoadLevelData(Worlds::RealTest)->d_GroundData);
		for (int i = 0; i < m_Ground->getLenght(); i++)
		{
			std::stringstream ss;
			ss << m_Ground->getGround(i, 0).x << "/" << m_Ground->getGround(i, 0).y;
			ss << "/" << m_Ground->getGround(i, 1).x << "/" << m_Ground->getGround(i, 1).y;
			utils::FileLogger::Log(utils::FileLogger::LogType::LOG_DEBUG, ss.str().c_str());
		}

		/* Load the layers */
		for (std::size_t i = 0; i < LayerCount; i++)
		{
			BaseNode::Ptr layer(new BaseNode());
			m_SceneLayers[i] = layer.get();

			m_Scene.attachChild(std::move(layer));
		}

		/* Start the thing */
		sf::Texture& displayTex = m_Textures.get(Textures::Debug1);
		std::unique_ptr<StateNode> Display(new StateNode(displayTex, (424 / 4), 40, 2));
		
		std::unique_ptr<AABBColider> Colider(new AABBColider(sf::Vector2f(0, 0), sf::Vector2f((424 / 4), 40), true, NULL, NULL));
		m_Colider = Colider.get();
		Display->attachChild(std::move(Colider));

		std::unique_ptr<MoveNode> Mover(new MoveNode(20, 0.98f, false, 0.0f, 100.0f));
		m_Mover = Mover.get();
		Display->attachChild(std::move(Mover));

		m_Display = Display.get();
		m_SceneLayers[Menu]->attachChild(std::move(Display));

		sf::Texture& playerTex = m_Textures.get(Textures::Debug2);
		std::unique_ptr<Player> Player(new Player(playerTex));
		m_Player = Player.get();
		Player->setScale(4.0f, 4.0f);
		m_SceneLayers[UI]->attachChild(std::move(Player));

			/*m_Window->setMouseCursorVisible(false);

			for (std::size_t i = 0; i < LayerCount; i++)
			{
				BaseNode::Ptr layer(new BaseNode());
				m_SceneLayers[i] = layer.get();

				m_Scene.attachChild(std::move(layer));
			}

			sf::Texture& BackgroundTex = m_Textures.get(Textures::MenuBackground);
			std::unique_ptr<SpriteNode> BackgroundNode(new SpriteNode(BackgroundTex));
			BackgroundNode->setScale(sf::Vector2f(m_WorldView.getSize().x / (float)BackgroundTex.getSize().x, m_WorldView.getSize().y / (float)BackgroundTex.getSize().y));
			m_Background = BackgroundNode.get();
			m_SceneLayers[Background]->attachChild(std::move(BackgroundNode));

			sf::Font& textFont = m_Fonts.get(Fonts::Prototype);

			std::unique_ptr<TextNode> title(new TextNode(textFont, (int)(m_WorldView.getSize().x / 10)));
			title->setText("Hunter - The fall");
			m_Title = title.get();
			title->move((m_WorldView.getSize().x - title->getWidth()) / 2.0f, m_WorldView.getSize().y / 15.0f);
			m_SceneLayers[Menu]->attachChild(std::move(title));

			std::unique_ptr<Button> bArray[5];
			std::string text[5] = { "New Game", "Continue", "Achivements", "Options", "Exit" };


			for (int i = 0; i < 5; i++)
			{
				std::unique_ptr<TextButton> ButtonNode(new TextButton(textFont, text[i], (int)(m_WorldView.getSize().y / 15), sf::Color(), sf::Color(0x666666ff), sf::Color(0xff9933ff), sf::Color(0xe67300ff)));
				bArray[i] = std::move(ButtonNode);
			}

			std::unique_ptr<ButtonArray> buttArray(new ButtonArray(bArray, 5, m_WorldView.getSize().x, (m_WorldView.getSize().y / 15) * 6, 0));
			buttArray->move(0.0f, m_WorldView.getSize().y - (m_WorldView.getSize().y / 15) * 8);
			m_ButtonArray = buttArray.get();
			m_SceneLayers[Menu]->attachChild(std::move(buttArray));

			sf::Texture& mouseTex = m_Textures.get(Textures::Mouse);
			std::unique_ptr<SpriteNode> mouse(new SpriteNode(mouseTex));
			int mScale = (int)m_WorldView.getSize().y / 720;
			m_Mouse = mouse.get();
			m_SceneLayers[UI]->attachChild(std::move(mouse));

			sf::SoundBuffer& soundTestBuff = m_Sounds.get(Sounds::buttonClick);
			sf::Sound soundTest[] = { sf::Sound(soundTestBuff) };
			std::unique_ptr<SoundNode> sTest(new SoundNode(soundTest, 1));
			m_Audio = sTest.get();
			m_SceneLayers[UI]->attachChild(std::move(sTest));

			m_Music.Play(Music::Menu);*/
	}

	void RealTestWorld::update(sf::Time dt)
	{
		if (Colider::Colide(m_Colider, m_Ground->getGround(0, 0), m_Ground->getGround(0, 1)))
		{
			m_Display->setState(1);
		}
		else
		{
			m_Display->setState(0);
		}

		m_Player->Interact(m_Input);
		/*m_ButtonArray->Interact(m_Input);

		m_Mouse->setActive(m_Input->getMouseUsed());

		for (int i = 0; i < m_ButtonArray->getLength(); i++)
			if (m_ButtonArray->getClicked(i))
				m_Audio->Play(0);

		if (m_ButtonArray->getClicked(3))
			m_Delete = true;

		if (m_ButtonArray->getClicked(4))
			m_Exit = true;

		m_Mouse->setPosition((float)m_Input->getMouseX(), (float)m_Input->getMouseY());*/
		m_Scene.update(dt);

		if (m_Input->getPress((int)Action::ENTER))
			m_Delete = true;
	}
}