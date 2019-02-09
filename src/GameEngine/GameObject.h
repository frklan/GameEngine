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

#include "Scene.h"

class Scene;

class GameObject{
  public:
    GameObject() = delete;
    GameObject(const Scene& scene, uint8_t zOrder = 0) : zOrder(zOrder), scene(scene) {};
    virtual ~GameObject() = default;

    virtual uint8_t getZOrder() const final { return zOrder; };
    virtual const Scene& getScene() const final { return scene; };
    
    virtual void update(const sf::Time gameTime) {};
    virtual void handleEvent(const sf::Event& e) {};  
    
    /* A derived class shall renders its own sprites, shapes etc. */
    virtual void render(sf::RenderTarget& target, sf::Time gameTime) {};

  private:
    uint8_t zOrder = 0;
    const Scene& scene;   
};