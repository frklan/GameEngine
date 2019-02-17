#pragma once
#include <iostream>

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

class Debugview : public GameObject {
  public:
    Debugview() = delete;
    Debugview(const Scene& scene, uint8_t zOrder);
    
    virtual ~Debugview() = default;
    
    virtual void onEvent(const sf::Event& e) override;  
    virtual void onRender(sf::RenderTarget& target, sf::Time gameTime) override;
    virtual void onUpdate(const sf::Time gameTime) override;

  private:
    bool showDebug = true;
    sf::Text debugText;
    sf::Text gpuInfo;
    sf::Time lastUpdate = sf::Time::Zero;
};