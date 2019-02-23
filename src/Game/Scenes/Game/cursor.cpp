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

#include "cursor.h"

Cursor::Cursor(Scene& scene, uint8_t zOrder) : 
GameObject(scene, zOrder), 
windowSize(getScene().getGameEngine().getWindowSize())
{ 
  scene.getGameEngine().getWindow().setMouseCursorVisible(false);
  scene.getEventBus().subscribe(this, &Cursor::onGuiEvent);
  scene.getEventBus().subscribe(this, &Cursor::onWindowResizeEvent);

  assert(scene.getGameObjects<GameOfLife>().size() == 1);
  gameOfLife = getScene().getGameObjects<GameOfLife>()[0];
}

Cursor::~Cursor() {
  getScene().getGameEngine().getWindow().setMouseCursorVisible(true);
}

void Cursor::onUpdate(sf::Time gameTime) {
}

void Cursor::onRender(sf::RenderTarget& target, sf::Time gameTime) {
  if(isEnabled) {
    target.draw(cursor.data(), cursor.size(), sf::PrimitiveType::Quads);
  }
}

void Cursor::onEvent(const sf::Event& e) {
  auto cellSize = gameOfLife->getCellSize();

  if(!isEnabled) {
    return;
  }

  if(e.type == sf::Event::EventType::MouseLeft) {
    cursor.fill(sf::Vertex({-1, -1}, sf::Color::Transparent));
  } else if(e.type == sf::Event::EventType::MouseMoved) {
    
    // Which cell are we hovering over?
    auto x = uint(e.mouseMove.x / cellSize);
    auto y = uint(e.mouseMove.y / cellSize);
    
    // calculate cell coordinates:
    auto topLeft = sf::Vector2f(x * cellSize, y * cellSize);
    auto topRight = sf::Vector2f(x * cellSize + cellSize,  y * cellSize);
    auto bottomRight = sf::Vector2f(x * cellSize + cellSize,  y * cellSize + cellSize);
    auto bottomLeft = sf::Vector2f(x * cellSize, y * cellSize + cellSize);

    // update cursor data
    cursor[0] = sf::Vertex(topLeft, cursorColor);
    cursor[1] = sf::Vertex(topRight, cursorColor);
    cursor[2] = sf::Vertex(bottomRight, cursorColor);
    cursor[3] = sf::Vertex(bottomLeft, cursorColor);
    
    // if button is pressed we also need to set cell state..
    if( sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
      gameOfLife->setCell({x, y}, GameOfLife::CellState::on);
    } else if( sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
      gameOfLife->setCell({x, y}, GameOfLife::CellState::off);
    }
  } else if(e.type == sf::Event::EventType::MouseButtonPressed) {
    auto x = uint(e.mouseButton.x / cellSize);
    auto y = uint(e.mouseButton.y / cellSize);
      
    if(e.mouseButton.button == sf::Mouse::Button::Left) {
      gameOfLife->setCell({x, y}, GameOfLife::CellState::on);
    } else if(e.mouseButton.button == sf::Mouse::Button::Left) {
      gameOfLife->setCell({x, y}, GameOfLife::CellState::off);
    } else if(e.mouseButton.button == sf::Mouse::Button::Middle) {
      gameOfLife->killAllCells();
    }
  }
}

void Cursor::onGuiEvent(game::GuiEvent&) {
  isEnabled = !isEnabled;
  getScene().getGameEngine().getWindow().setMouseCursorVisible(!isEnabled);
}

void Cursor::onWindowResizeEvent(game::WindowResizeEvent& e) {  
  windowSize = e.windowSize;
}