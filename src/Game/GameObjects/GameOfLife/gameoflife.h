#pragma once
#include <iostream>
#include <array>
#include <set>
#include <random>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/OpenGL.hpp>

#include "../../../GameEngine/Scene.h"
#include "../../../GameEngine/ResourceManager.h"
#include "../../../GameEngine/GameObject.h"

class GameOfLife : public GameObject {
  enum CellState {
    off = 0,
    on = 1,
  };

  public:
    GameOfLife() = delete;
    GameOfLife(const Scene& scene, uint8_t zOrder);
    
    virtual ~GameOfLife() = default;
    
    virtual void update(const sf::Time gameTime) override;
    virtual void render(sf::RenderTarget& target, sf::Time gameTime) override;
    virtual void handleEvent(const sf::Event& e) override;

  private:
    static const uint16_t HEGHT = 108;
    static const uint16_t WIDTH = 192;
    static const uint8_t CELLSIZE = 10;

    std::array<CellState, (GameOfLife::HEGHT * GameOfLife::WIDTH)> cells;
    std::array<sf::Vertex, (GameOfLife::HEGHT * GameOfLife::WIDTH * 4)> vertexs;   
    sf::Clock gameSpeed;
    std::mt19937 rng;
    
    int getRandom(int min, int max);
    uint32_t rowAndColToIndex(uint16_t x, uint16_t y);
    void forEachCell(std::function<void(uint16_t, uint16_t)> f);
    uint32_t getAliveNeighbors(uint16_t x, uint16_t y);
};