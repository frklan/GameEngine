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

#include "grid.h"

#include "../../../GameEngine/Scene.h"
#include "../../../GameEngine/ResourceManager.h"
#include "../../../GameEngine/GameObject.h"

Grid::Grid(const Scene& scene, uint8_t zOrder) : 
GameObject(scene, zOrder), 
windowSize(getScene().getGameEngine().getWindowSize())
{ 
  assert(Grid::HEGHT > 3);
  assert(Grid::WIDTH > 3);

  generateGrid();
}

void Grid::update(sf::Time gameTime) {
  GameObject::update(gameTime);
}

void Grid::render(sf::RenderTarget& target, sf::Time gameTime) {
  GameObject::render(target, gameTime);
  target.draw(grid.data(), grid.size(), sf::PrimitiveType::Lines);
}

void Grid::handleEvent(const sf::Event& e) {
  if(e.type == sf::Event::EventType::Resized) {
    windowSize.x = getScene().getGameEngine().getWindowSize().x;
    windowSize.y = getScene().getGameEngine().getWindowSize().y;
    generateGrid();
  }
}

std::pair<uint16_t, uint16_t> Grid::getCellCount() {
  auto x = ceil(float(windowSize.x) / float(Grid::CELLSIZE));
  auto y = ceil(float(windowSize.y) / float(Grid::CELLSIZE));

  return std::make_pair<uint16_t, uint16_t>(x, y);
}

void Grid::generateGrid() {
  grid.clear();

  grid.emplace_back(sf::Vertex{sf::Vector2f{0.f, 1.f}, gridColor});
  grid.emplace_back(sf::Vertex{sf::Vector2f{float(windowSize.x - 1), 1.f}, gridColor});

  grid.emplace_back(sf::Vertex{sf::Vector2f{float(windowSize.x), 0.f}, gridColor});
  grid.emplace_back(sf::Vertex{sf::Vector2f{float(windowSize.x), float(windowSize.y + 1)}, gridColor});
  
  grid.emplace_back(sf::Vertex{sf::Vector2f{float(windowSize.x), float(windowSize.y - 1)}, gridColor});
  grid.emplace_back(sf::Vertex{sf::Vector2f{0.f, float(windowSize.y - 1)}, gridColor});
  
  grid.emplace_back(sf::Vertex{sf::Vector2f{1.f, float(windowSize.y + 1)}, gridColor});
  grid.emplace_back(sf::Vertex{sf::Vector2f{1.f, 0.f}, gridColor});
  
  auto [numGridLinesX, numGridLinesY] = getCellCount();

  for(auto i = 0; i < numGridLinesX; i++){
    auto x = i * Grid::CELLSIZE;
    grid.emplace_back(sf::Vertex{sf::Vector2f{float(x), 0.f}, gridColor});
    grid.emplace_back(sf::Vertex{sf::Vector2f{float(x), float(windowSize.y)}, gridColor});
  }
  std::clog << '\n';

  for(auto i = 0; i < numGridLinesY; i++){
    auto y = i * Grid::CELLSIZE;
    grid.emplace_back(sf::Vertex{sf::Vector2f{0.f, float(y)}, gridColor});
    grid.emplace_back(sf::Vertex{sf::Vector2f{float(windowSize.x), float(y)}, gridColor});
  } 
}