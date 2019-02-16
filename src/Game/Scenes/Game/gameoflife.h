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

#include <Event.h>
#include <GameEngine.h>
#include <GameObject.h>
#include <Observable.h>
#include <Observer.h>
#include <ResourceManager.h>
#include <Scene.h>

#include "gamescene.h"

struct GameState;
class GameScene;

class GameOfLife : public GameObject, public Observer<GameState> {
  public:
    enum CellState {
      off = 0,
      on = 1,
    };
    GameOfLife() = delete;
    GameOfLife(Scene& scene, uint8_t zOrder);
    
    virtual ~GameOfLife() = default;
    
    virtual void onEvent(const sf::Event& e) override;  
    virtual void onRender(sf::RenderTarget& target, sf::Time gameTime) override;
    virtual void onUpdate(const sf::Time gameTime) override;

    virtual const uint8_t getCellSize() const noexcept {return GameOfLife::CELLSIZE; }
    virtual const sf::Vector2u getGameboardSize() const noexcept {return sf::Vector2u{GameOfLife::WIDTH, GameOfLife::HEGHT}; }
    virtual const uint32_t rowAndColToIndex(uint16_t x, uint16_t y) const noexcept;
    virtual void forEachCell(std::function<void(uint16_t, uint16_t)> f) noexcept;
    virtual const std::pair<uint16_t, uint16_t> getCellCount() const noexcept;
    virtual void flipCell(sf::Vector2u);
    virtual void setCell(sf::Vector2u, CellState);
    virtual void  killAllCells() { cells.fill(CellState::off); };

    virtual void onNotify(GameState) override;

  private:
    static const uint16_t HEGHT = 216;
    static const uint16_t WIDTH = 384;
    static const uint8_t CELLSIZE = 15;
    const sf::Color deadCellColor{8, 3, 0, 255};
    const sf::Color livingCellColor{126, 192, 236, 255};
    uint64_t generation = 0;
    bool paused = false;

    std::array<CellState, (GameOfLife::HEGHT * GameOfLife::WIDTH)> cells;
    std::array<sf::Vertex, (GameOfLife::HEGHT * GameOfLife::WIDTH * 4)> vertexs;   
    sf::Vector2u windowSize;
    std::mt19937 rng;
    sf::Clock gameSpeed;
    
    const int getRandom(int min, int max);
    const uint32_t getAliveNeighbors(uint16_t x, uint16_t y) const noexcept;
    void generateRandomCellStructure();
    void updateCellVertex(uint16_t x, uint16_t y, CellState& cell);
};

