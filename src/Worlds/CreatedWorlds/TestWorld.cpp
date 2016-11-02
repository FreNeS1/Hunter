#include "TestWorld.hpp"

namespace bas {

	TestWorld::TestWorld(sf::RenderWindow* window, Input* input)
		: World(window, input)
	{
		m_Delete = false;
		m_Exit = false;
		m_Next = Worlds::MainMenu;
	}

	void TestWorld::loadResources()
	{
		m_Textures.load(Textures::Debug1, "res/Textures/FinishLine.png");
		m_Textures.load(Textures::Debug2, "res/Textures/coin.png");
		m_Textures.load(Textures::Debug3, "res/Textures/Explosion.png");

		m_Fonts.load(Fonts::Debug1, "res/Fonts/Debug.ttf");
	}

	void TestWorld::buildScene()
	{
		for (std::size_t i = 0; i < LayerCount; i++)
		{
			BaseNode::Ptr layer(new BaseNode());
			m_SceneLayers[i] = layer.get();

			m_Scene.attachChild(std::move(layer));
		}

		sf::Font& font1 = m_Fonts.get(Fonts::Debug1);
		std::unique_ptr<TextNode> example(new TextNode(font1, 20));
		example->setText("HEY");
		m_Text = example.get();
		m_Scene.attachChild(std::move(example));

		sf::Texture& exampleTexture = m_Textures.get(Textures::Debug1);
		std::unique_ptr<SpriteNode> example2(new SpriteNode(exampleTexture));
		example2->setActive(false);
		
		sf::Texture& dynamicTexture = m_Textures.get(Textures::Debug3);
		std::unique_ptr<DynamicNode> dynamic(new DynamicNode(dynamicTexture));
		dynamic->setPosition(50.0f, 200.0f);
		dynamic->createAnimation("1", 0, 256 * 0, 256, 256, 5, 1.0f, true);
		dynamic->createAnimation("2", 0, 256 * 1, 256, 256, 5, 0.7f, true);
		dynamic->createAnimation("3", 0, 256 * 2, 256, 256, 5, 0.4f, true);
		dynamic->createAnimation("4", 0, 256 * 3, 256, 256, 4, 0.25f, true);
		dynamic->setAnimation("1");
		dynamic->setActive(true);
		
		example2->attachChild(std::move(dynamic));
		m_SceneLayers[UI]->attachChild(std::move(example2));

		sf::Texture& animatedTexture = m_Textures.get(Textures::Debug2);
		std::unique_ptr<AnimationNode> animation(new AnimationNode(animatedTexture, 100, 100, 10, 0.56f, true));
		animation->setPosition(200.0f, 0.0f);
		animation->setActive(true);
		m_Coin = animation.get();

		std::unique_ptr<MoveNode> movement(new MoveNode(50, 0.8f, false, 160, 140));
		movement->setActive(true);
		animation->attachChild(std::move(movement));

		m_SceneLayers[UI]->attachChild(std::move(animation));
	}

	void TestWorld::update(sf::Time dt)
	{
		m_Scene.update(dt);

		std::stringstream ss;
		ss << m_Coin->getWorldPosition().x;
		m_Text->setText(ss.str().c_str());

		if (m_Coin->getWorldPosition().x > 600)
			m_Delete = true;
	}
}