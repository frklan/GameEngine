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

#include "gameoflife.h"

#include "../../../GameEngine/Scene.h"
#include "../../../GameEngine/ResourceManager.h"
#include "../../../GameEngine/GameObject.h"

GameOfLife::GameOfLife(const Scene& scene, uint8_t zOrder) : 
GameObject(scene, zOrder), 
windowSize(getScene().getGameEngine().getWindowSize()),
rng(std::time(nullptr))
{ 
  assert(GameOfLife::HEGHT > 3);
  assert(GameOfLife::WIDTH > 3);

  generateRandomCellStructure();
  generateGrid();
  gameSpeed.restart();
}

void GameOfLife::update(sf::Time gameTime) {
  GameObject::update(gameTime);

  if(gameSpeed.getElapsedTime().asSeconds() > 1.f || generation == 0) {  
    gameSpeed.restart();
    generation++;

    auto newCells = cells;
    forEachCell([&](uint16_t x, uint16_t y){
      auto i = rowAndColToIndex(x, y);
      auto numAliveNeighbors = getAliveNeighbors(x, y);

      // Generate the new cell state
      // Any live cell == 2 or == 3 live neighbors lives on to the next generation.
      // Any live cell with < 2 or > 3 live neighbors dies
      // Any dead cell == 3 live neighbors becomes a live cell
      if(cells[i] == CellState::off && numAliveNeighbors == 3 ) { 
        newCells[i] = CellState::on;
      }
      if(cells[i] == CellState::on && (numAliveNeighbors < 2 || numAliveNeighbors > 3)) {
        newCells[i] = CellState::off;
      }

      // Calculate render verteces for this cell
      auto topLeft = sf::Vector2f(x * GameOfLife::CELLSIZE, y * GameOfLife::CELLSIZE);
      auto topRight = sf::Vector2f(x * GameOfLife::CELLSIZE + GameOfLife::CELLSIZE,  y * GameOfLife::CELLSIZE);

      auto bottomRight = sf::Vector2f(x * GameOfLife::CELLSIZE + GameOfLife::CELLSIZE,  y * GameOfLife::CELLSIZE + GameOfLife::CELLSIZE);
      auto bottomLeft = sf::Vector2f(x * GameOfLife::CELLSIZE, y * GameOfLife::CELLSIZE + GameOfLife::CELLSIZE);

      auto cellColor = (newCells[i] == CellState::on ? livingCellColor : deadCellColor);
      vertexs[i * 4] = sf::Vertex(topLeft, cellColor);
      vertexs[i * 4 + 1] = sf::Vertex(topRight, cellColor);
      vertexs[i * 4 + 2] = sf::Vertex(bottomRight, cellColor);
      vertexs[i * 4 + 3] = sf::Vertex(bottomLeft, cellColor);
    });
    cells = newCells;
  }
}

void GameOfLife::render(sf::RenderTarget& target, sf::Time gameTime) {
  GameObject::render(target, gameTime);
  target.draw(vertexs.data(), vertexs.size(), sf::PrimitiveType::Quads);
  target.draw(grid.data(), grid.size(), sf::PrimitiveType::Lines);
}

void GameOfLife::handleEvent(const sf::Event& e) {
  if(e.type == sf::Event::EventType::Resized) {
    windowSize.x = getScene().getGameEngine().getWindowSize().x;
    windowSize.y = getScene().getGameEngine().getWindowSize().y;
    generateGrid();
  }
}

int GameOfLife::getRandom(int min, int max) {
  std::uniform_int_distribution<int> dist(min, max);
  return dist(rng);
}

// we have maximum 8 neighbors, minimum 3:
//  1 2 3
//  4 x 5   or   x 5
//  6 7 8        7 8
uint32_t GameOfLife::getAliveNeighbors(uint16_t x, uint16_t y) {
  uint32_t alive = 0;

  // 1
  if(x > 0 && y > 0 && cells[rowAndColToIndex(x - 1, y - 1)] == CellState::on) alive++;
  // 2
  if(y > 0 && cells[rowAndColToIndex(x, y - 1)] == CellState::on) alive++;
  // 3
  if(x < GameOfLife::WIDTH - 1 && y > 0 && cells[rowAndColToIndex(x + 1, y - 1)] == CellState::on) alive++;
  // 4
  if(x > 0 && cells[rowAndColToIndex(x - 1, y)] == CellState::on) alive++;
  // 5
  if(x < GameOfLife::WIDTH - 1 && cells[rowAndColToIndex(x + 1, y)] == CellState::on) alive++;
  // 6
  if(x > 0 && y < GameOfLife::HEGHT - 1 && cells[rowAndColToIndex(x - 1, y + 1)] == CellState::on) alive++;
  // 7
  if(y < GameOfLife::HEGHT - 1 && cells[rowAndColToIndex(x, y + 1)] == CellState::on) alive++;
  // 8
  if(x < GameOfLife::WIDTH - 1 && y < GameOfLife::HEGHT && cells[rowAndColToIndex(x + 1, y + 1)] == CellState::on) alive++;
  
  return alive;
}

uint32_t GameOfLife::rowAndColToIndex(uint16_t x, uint16_t y) {
  return y * GameOfLife::WIDTH + x;
}

std::pair<uint16_t, uint16_t> GameOfLife::getCellCount() {
  auto x = ceil(float(windowSize.x) / float(GameOfLife::CELLSIZE));
  auto y = ceil(float(windowSize.y) / float(GameOfLife::CELLSIZE));

  return std::make_pair<uint16_t, uint16_t>(x, y);
}

void GameOfLife::forEachCell(std::function<void(uint16_t, uint16_t)> f) {
  for(uint16_t y = 0; y < GameOfLife::HEGHT; y++) {
    for(uint16_t x = 0; x < GameOfLife::WIDTH; x++) {
      f(x, y);
    }
  }
}

void GameOfLife::generateRandomCellStructure() { 
  forEachCell([&](uint16_t x, uint16_t y) {
    int i = rowAndColToIndex(x, y);
    auto rand = getRandom(0, 1);
    if(rand < 1) {
      cells[i] = CellState::off;
    } else {
      cells[i] = CellState::on;
    }
  });
}

void GameOfLife::generateGrid() {
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
    auto x = i * GameOfLife::CELLSIZE;
    grid.emplace_back(sf::Vertex{sf::Vector2f{float(x), 0.f}, gridColor});
    grid.emplace_back(sf::Vertex{sf::Vector2f{float(x), float(windowSize.y)}, gridColor});
  }
  std::clog << '\n';

  for(auto i = 0; i < numGridLinesY; i++){
    auto y = i * GameOfLife::CELLSIZE;
    grid.emplace_back(sf::Vertex{sf::Vector2f{0.f, float(y)}, gridColor});
    grid.emplace_back(sf::Vertex{sf::Vector2f{float(windowSize.x), float(y)}, gridColor});
  } 
}