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
#include "gamefsm.h"


GameFsm::GameFsm(const Scene& scene, uint8_t zOrder) :
GameObject(scene, zOrder) {
  
}

void GameFsm::update(const sf::Time gameTime) {
  if(gameOfLife == nullptr) {
    assert(getScene().getGameObjects<GameOfLife>().size() == 1);
    gameOfLife = getScene().getGameObjects<GameOfLife>()[0];
  }

}

void GameFsm::handleEvent(const sf::Event& e) {
  if(e.type ==sf::Event::EventType::KeyPressed) {
    if(e.key.code == sf::Keyboard::P) {
      isPaused = !isPaused;
      if(isPaused) {
        notify({GameState::GamePaused});
      } else {
        notify({GameState::GameRunning});
      }
    } else if(e.key.code == sf::Keyboard::Num1) {
      notify({GameState::GameOver});
    } else if(e.key.code == sf::Keyboard::Key::C) {
      gameOfLife->killAllCells();
    }
  }
}

