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
    GameObject(Scene& scene, uint8_t zOrder = 0) : gameObjecZOrder(zOrder), gameScene(scene) {}
    virtual ~GameObject() = default;

    virtual uint8_t getZOrder() const final { return gameObjecZOrder; }
    virtual const Scene& getScene() const final { return gameScene; }
    
    virtual void onEvent(const sf::Event& /* e */) {}
    virtual void onRender(sf::RenderTarget& /* target */, sf::Time /* gameTime */) {}
    virtual void onUpdate(const sf::Time /* gameTime */) {}

  private:
    uint8_t gameObjecZOrder = 0;
    Scene& gameScene;   
};
