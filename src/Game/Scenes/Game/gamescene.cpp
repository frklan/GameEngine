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

#include "gameoflife.h"
#include "gamescene.h"

class GameOfLife;

GameScene::GameScene(GameEngine& engine) : Scene(engine) {   
  auto gol = this->addGameObject(std::make_unique<GameOfLife>(*this, 20));
  gameOfLife = dynamic_cast<GameOfLife*>(gol);

  this->addGameObject(std::make_unique<Debugview>(*this, 0));
  this->addGameObject(std::make_unique<Grid>(*this, 10));
  this->addGameObject(std::make_unique<Cursor>(*this, 5));
  this->addGameObject(std::make_unique<StatusDisplay>(*this, 0));
}

bool GameScene::onActivate() { 
  gameEngine.setFramerateLimit(120);
  return true;
}

bool GameScene::onEvent(sf::Event& e) {
  
  // Consume "our" events by returning true
  if(e.type == sf::Event::EventType::KeyPressed) {
    if(e.key.code == sf::Keyboard::P) {
      isPaused = !isPaused;
      if(isPaused) {
        notify({GameState::GamePaused});
      } else {
        notify({GameState::GameRunning});
      }
      return true;
    } else if(e.key.code == sf::Keyboard::Key::C) {
      gameOfLife->killAllCells();
      return true;
    }
  }

  // false == event not handled.
  return false;
}