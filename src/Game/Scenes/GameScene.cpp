#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/OpenGL.hpp>

#include "gamescene.h"

#include "../../GameEngine/Scene.h"
#include "../GameObjects/Player/player.h"
#include "../GameObjects/DebugView/debugview.h"

GameScene::GameScene(GameEngine& engine) : Scene(engine) { 
  std::clog << "GameScene scene created!\n"; 
  
  this->addGameObject(std::make_unique<Player>(*this, 50, 0));
  this->addGameObject(std::make_unique<Debugview>(*this, 0));
}

GameScene::~GameScene() { 
  std::clog << "GameScene scene destroyed!\n"; 
}

void GameScene::handleEvent(sf::Event& e) {
  Scene::handleEvent(e);

  if(e.type == sf::Event::MouseButtonPressed) {
    gameEngine.switchScene("intro");
    gameEngine.unloadScene("game");    
  }
}

void GameScene::update(sf::Time gameTimeMs) { 
  Scene::update(gameTimeMs);
};

void GameScene::onActivate() { 
  Scene::onActivate();

  gameEngine.setFramerateLimit(120);
  std::clog << "GameScene::onActivate()\n";
}

void GameScene::onDeactivate() { 
  Scene::onDeactivate();
  
  std::clog << "GameScene::onDeactivate()\n";
}