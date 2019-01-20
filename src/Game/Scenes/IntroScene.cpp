#include <iostream>
#include <sstream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/OpenGL.hpp>

#include "introscene.h"
#include "gamescene.h"

#include "../GameObjects/DebugView/debugview.h"
#include "../../GameEngine/Scene.h"
#include "../../GameEngine/ResourceManager.h"
#include "../../GameEngine/GameEngine.h"

Intro::Intro(GameEngine& engine) : Scene(engine) { 
  std::clog << "Intro scene created!\n"; 

  addGameObject(std::make_unique<Debugview>(*this, 0));
}

Intro::~Intro() { 
  std::clog << "Intro scene destroyed!\n"; 
}

void Intro::onActivate() { 
  Scene::onDeactivate();

  gameEngine.setFramerateLimit(0);
  std::clog << "Intro::onActivate()\n";
};

void Intro::onDeactivate() {
  Scene::onDeactivate();

  std::clog << "Intro::onDeactivate()\n";
};

void Intro::handleEvent(sf::Event& e) {
  Scene::handleEvent(e);

  if(e.type == sf::Event::MouseButtonPressed) {
    gameEngine.addScene("game", std::make_unique<GameScene>(gameEngine));
    gameEngine.switchScene("game");
  }
}