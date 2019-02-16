#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdint>
#include <vector>

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
#include "statusdisplay.h"

StatusDisplay::StatusDisplay(Scene& scene, uint8_t zOrder) : GameObject(scene) { 
  pauseText.setPosition(10, 10);
  pauseText.setFont(getScene().getGameEngine().getFontResource("src/Game/Resources/pixel_operator/PixelOperator8.ttf"));
  pauseText.setFillColor(sf::Color::Red);
  pauseText.setCharacterSize(35);
  pauseText.setString("PAUSED");

  dynamic_cast<GameScene&>(scene).registerObserver(*this);
}

void StatusDisplay::onUpdate(sf::Time gameTime) {
  auto windowSize = getScene().getGameEngine().getWindowSize();
  auto textSize = pauseText.getGlobalBounds();

  sf::Vector2f textPos = sf::Vector2f{(windowSize.x / 2) - (textSize.width / 2), (windowSize.y / 2) - (textSize.height / 2)};
  pauseText.setPosition(textPos.x, textPos.y);
  
  if(int(gameTime.asSeconds()) % 2 == 0) {
    pauseText.setFillColor(sf::Color::Red);
  } else {
    pauseText.setFillColor(sf::Color::Transparent);
  }
}

void StatusDisplay::onRender(sf::RenderTarget& target, sf::Time gameTime) {
  if(isPaused) {
    target.draw(pauseText);
  }
}


void StatusDisplay::onNotify(GameState e) { 
  isPaused = false;
  if(e.gameState == GameState::GamePaused) {
    isPaused = true;

  } else if(e.gameState == GameState::GameRunning) {
    isPaused = false;
  }
}