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

#include <Event.h>
#include <GameEngine.h>
#include <GameObject.h>
#include <Observable.h>
#include <Observer.h>
#include <ResourceManager.h>
#include <Scene.h>

class SinCurve : public GameObject {
  public:
    SinCurve() = delete;
    SinCurve(const Scene& scene, uint8_t zOrder, uint16_t xOffset = 0, float yOffset = 1.0);
    
    virtual ~SinCurve() = default;
    
    virtual void onEvent(const sf::Event& e) override;  
    virtual void onRender(sf::RenderTarget& target, sf::Time gameTime) override;
    virtual void onUpdate(const sf::Time gameTime) override;
    
  private:
    void createCurve();
    sf::Color hsvToRgb(long long hue, float sat, float val);
    uint16_t curveOffsetX;
    float curveOffsetY;
    sf::Time lastUpdate = sf::Time::Zero;
    sf::Vector2f pos{ 500.f, 500.f};
    sf::Vector2u windowSize;
    
    std::array<sf::Vertex, 251> curve;
    sf::Clock vertexClock;
};