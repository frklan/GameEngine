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

#include <GameEngine.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <Scene.h>

#include "gameoflife.h"
#include "statusdisplay.h"

StatusDisplay::StatusDisplay(Scene& scene, uint8_t zOrder) : GameObject(scene, zOrder) { 
  pauseText.setPosition(10, 10);
  pauseText.setFont(getScene().getGameEngine().getFontResource("Resources/pixel_operator/PixelOperator8.ttf"));
  pauseText.setFillColor(sf::Color::Red);
  pauseText.setCharacterSize(35);
  pauseText.setString("PAUSED");

  scene.getEventBus().subscribe(this, &StatusDisplay::onGamePauseEvent);
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

void StatusDisplay::onRender(sf::RenderTarget& target, sf::Time) {
  if(isPaused) {
    target.draw(pauseText);
  }
}

void StatusDisplay::onGamePauseEvent(game::GamePauseEvent&) {
  isPaused = !isPaused;
}
