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

class Grid : public GameObject {
  public:
    Grid() = delete;
    Grid(const Scene& scene, uint8_t zOrder);
    
    virtual ~Grid() = default;
    
    virtual void update(const sf::Time gameTime) override;
    virtual void render(sf::RenderTarget& target, sf::Time gameTime) override;
    virtual void handleEvent(const sf::Event& e) override;

  private:
    static const uint16_t HEGHT = 216;
    static const uint16_t WIDTH = 384;
    static const uint8_t CELLSIZE = 15;
    const sf::Color gridColor{63, 96, 118, 255};

    std::vector<sf::Vertex> grid;
    sf::Vector2u windowSize;
   
    uint32_t rowAndColToIndex(uint16_t x, uint16_t y);
    void forEachCell(std::function<void(uint16_t, uint16_t)> f);
    void generateGrid();
    std::pair<uint16_t, uint16_t> getCellCount();
   
};

