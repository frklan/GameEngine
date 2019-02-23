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

class Cursor : public GameObject {
  public:
    Cursor() = delete;
    Cursor(Scene& scene, uint8_t zOrder);

    virtual ~Cursor() override;
    
    virtual void onEvent(const sf::Event& e) override;  
    virtual void onRender(sf::RenderTarget& target, sf::Time gameTime) override;

    void onGuiEvent(game::GuiEvent& e);
    void onWindowResizeEvent(game::WindowResizeEvent& e);

  private:
    sf::Vector2u windowSize;
    std::array<sf::Vertex, 4> cursor;
    GameOfLife* gameOfLife = nullptr;
    sf::Color cursorColor{185, 118, 93, 255};

    bool isEnabled = true;
};
