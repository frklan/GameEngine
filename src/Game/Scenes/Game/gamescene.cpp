#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/OpenGL.hpp>

#include <Event.h>
#include <GameEngine.h>
#include <GameObject.h>
#include <Observable.h>
#include <Observer.h>
#include <ResourceManager.h>
#include <Scene.h>

#include "gameoflife.h"
#include "grid.h"
#include "cursor.h"
#include "statusdisplay.h"
#include "../Common/DebugView/debugview.h"

#include "gamescene.h"

GameScene::GameScene(GameEngine& engine) : Scene(engine) { 
  std::clog << "GameScene scene created!\n"; 
  
  this->addGameObject(std::make_unique<GameOfLife>(*this, 20));
  this->addGameObject(std::make_unique<Debugview>(*this, 0));
  this->addGameObject(std::make_unique<Grid>(*this, 10));
  this->addGameObject(std::make_unique<GameFsm>(*this, 1000));
  this->addGameObject(std::make_unique<Cursor>(*this, 5));
  this->addGameObject(std::make_unique<StatusDisplay>(*this, 0));
}

GameScene::~GameScene() { 
  std::clog << "GameScene scene destroyed!\n"; 
}

void GameScene::handleEvent(sf::Event& e) {
  Scene::handleEvent(e);

  if(e.type == sf::Event::MouseButtonPressed) {
    //gameEngine.switchScene("intro");
    //gameEngine.unloadScene("game");    
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