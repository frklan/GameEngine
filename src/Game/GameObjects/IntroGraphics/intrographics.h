#pragma once
#include <iostream>
#include <array>

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

class IntroGraphics : public GameObject {
  public:
    IntroGraphics() = delete;
    IntroGraphics(const Scene& scene, uint8_t zOrder);
    
    virtual ~IntroGraphics() = default;
    
    virtual void update(const sf::Time gameTime) override;
    virtual void render(sf::RenderTarget& target, sf::Time gameTime) override;
    virtual void handleEvent(const sf::Event& e) override;
    

  private:
    sf::Color hsvToRgb(long long hue, float sat, float val);
    sf::Time lastUpdate = sf::Time::Zero;
    sf:: Vector2f pos{ 500.f, 500.f};
    sf::Vector2u windowSize;
    
    std::array<sf::Vertex, 251> vs;
    sf::Clock vertexClock;

    std::array<sf::Vertex, 4> quad;
    
};