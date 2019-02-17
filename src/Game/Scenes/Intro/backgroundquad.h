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

#include <GameEngine.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <Scene.h>

class BackgroundQuad : public GameObject {
  public:
    BackgroundQuad() = delete;
    BackgroundQuad(const Scene& scene, uint8_t zOrder);
    
    virtual ~BackgroundQuad() = default;
    
    virtual void onEvent(const sf::Event& e) override;  
    virtual void onRender(sf::RenderTarget& target, sf::Time gameTime) override;
    virtual void onUpdate(const sf::Time gameTime) override;
    

  private:
    void createBackground();
    sf::Color hsvToRgb(long long hue, float sat, float val);

    sf::Time lastUpdate = sf::Time::Zero;
    sf::Vector2f pos{ 500.f, 500.f};
    sf::Vector2u windowSize;
    std::array<sf::Vertex, 4> quad;
};