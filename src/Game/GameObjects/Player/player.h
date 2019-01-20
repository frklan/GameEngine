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

#include "../../../GameEngine/Scene.h"
#include "../../../GameEngine/ResourceManager.h"
#include "../../../GameEngine/GameObject.h"

class Player : public GameObject {
  public:
    Player() = delete;
    Player(const Scene& scene, uint8_t zOrder, float xOffset);
    
    virtual ~Player() = default;
    
    virtual void update(const sf::Time gameTime) override;
    virtual void render(sf::RenderTarget& target, sf::Time gameTime) override;
    virtual void handleEvent(const sf::Event& e) override;

  private:
    sf::RectangleShape rectangle;
    sf::Vector2f playerDirection{0.f, 0.f};
    const float speed = 250.f;
    
    sf::Time frameTime = sf::Time::Zero;
};