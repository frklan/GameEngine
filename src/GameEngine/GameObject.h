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

    uint8_t getZOrder() const { return zOrder; };
    virtual void addGameObject(std::unique_ptr<GameObject> go) final;
    virtual void update(const sf::Time gameTime);
    virtual void handleEvent(const sf::Event& e);

    virtual const Scene& getScene() const final { return scene; };

    /* A derived class shall renders its own sprites, shapes etc. and then
     * any GameObjects contained herein will be called to also render it's
     * members. */
    virtual void render(sf::RenderTarget& target, sf::Time gameTime);

  private:
    uint8_t zOrder = 0;
    const Scene& scene;
    std::multimap<uint8_t, std::unique_ptr<GameObject>> gameObjects;
    
};