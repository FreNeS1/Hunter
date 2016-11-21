#include "MenuWorld.hpp"

namespace bas {

	MenuWorld::MenuWorld(sf::RenderWindow * window, Input * input) : World(window, input)
		, m_Music()
		, m_Audio()
	{
		m_Delete = false;
		m_Exit = false;
		m_Next = Worlds::MainMenu;
	}

	MenuWorld::~MenuWorld()
	{
		m_Music.Stop();
		delete m_Background;
		delete m_Title;
		delete m_ButtonArray;
		delete m_Mouse;
		delete m_Audio;
	}

	void MenuWorld::loadResources()
	{
		for each (int i in Textures::MENU)
			m_Textures.load(Textures::ID(i), Textures::paths[i]);

		for each (int i in Fonts::MENU)
			m_Fonts.load(Fonts::ID(i), Fonts::paths[i]);

		for each (int i in Sounds::MENU)
			m_Sounds.load(Sounds::ID(i), Sounds::paths[i]);

		for each (int i in Music::MENU)
			m_Music.load(Music::ID(i), Music::paths[i]);
	}

	void MenuWorld::buildScene()
	{
		m_Window->setMouseCursorVisible(false);

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

		m_Music.Play(Music::Menu);
	}

	void MenuWorld::update(sf::Time dt)
	{
		m_ButtonArray->Interact(m_Input);

		m_Mouse->setActive(m_Input->getMouseUsed());

		for (int i = 0; i < m_ButtonArray->getLength(); i++)
			if (m_ButtonArray->getClicked(i))
				m_Audio->Play(0);

		if (m_ButtonArray->getClicked(3))
			m_Delete = true;

		if (m_ButtonArray->getClicked(4))
			m_Exit = true;

		m_Mouse->setPosition((float)m_Input->getMouseX(), (float)m_Input->getMouseY());
		m_Scene.update(dt);
	}
}