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
#include "grid.h"

Grid::Grid(Scene& scene, uint8_t zOrder) : 
GameObject(scene, zOrder), 
windowSize(getScene().getGameEngine().getWindowSize())
{ 
  assert(scene.getGameObjects<GameOfLife>().size() == 1);
  gameOfLife = getScene().getGameObjects<GameOfLife>()[0];

  scene.getEventBus().subscribe(this, &Grid::onWindowResizeEvent);

  generateGrid();
}

void Grid::onRender(sf::RenderTarget& target, sf::Time) {
  target.draw(grid.data(), grid.size(), sf::PrimitiveType::Lines);
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
  
  auto [numGridLinesX, numGridLinesY] = gameOfLife->getCellCount();

  for(auto i = 0; i < numGridLinesX; i++){
    auto x = i * gameOfLife->getCellSize();
    grid.emplace_back(sf::Vertex{sf::Vector2f{float(x), 0.f}, gridColor});
    grid.emplace_back(sf::Vertex{sf::Vector2f{float(x), float(windowSize.y)}, gridColor});
  }

  for(auto i = 0; i < numGridLinesY; i++){
    auto y = i * gameOfLife->getCellSize();
    grid.emplace_back(sf::Vertex{sf::Vector2f{0.f, float(y)}, gridColor});
    grid.emplace_back(sf::Vertex{sf::Vector2f{float(windowSize.x), float(y)}, gridColor});
  } 
}

void Grid::onWindowResizeEvent(game::WindowResizeEvent& e) {  
  windowSize = e.windowSize;
  generateGrid();
}
