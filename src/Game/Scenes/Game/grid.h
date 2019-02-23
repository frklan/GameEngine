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

#include <GameEngine.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <Scene.h>

#include "gameoflife.h"

class Grid : public GameObject {
  public:
    Grid() = delete;
    Grid(Scene& scene, uint8_t zOrder);
    
    virtual ~Grid() override = default;
     
    virtual void onRender(sf::RenderTarget& target, sf::Time gameTime) override;

    void onWindowResizeEvent(game::WindowResizeEvent& e);

  private:
    void generateGrid();
    
    GameOfLife* gameOfLife;
    const sf::Color gridColor{63, 96, 118, 255};
    std::vector<sf::Vertex> grid;
    sf::Vector2u windowSize; 
    
};
