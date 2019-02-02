#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/OpenGL.hpp>

#include "GameObject.h"

void GameObject::addGameObject(std::unique_ptr<GameObject> go) {
  gameObjects.insert({go->getZOrder(), std::move(go)});
}

void GameObject::update(const sf::Time gameTime) {
  for(auto go = gameObjects.rbegin(); go != gameObjects.rend(); go++) {
      go->second->update(gameTime);
  }
}

void GameObject::handleEvent(const sf::Event& e) {
  for(auto go = gameObjects.rbegin(); go != gameObjects.rend(); go++) {
      go->second->handleEvent(e);
  }
}

void GameObject::render(sf::RenderTarget& target, sf::Time gameTime) {
  for(auto go = gameObjects.rbegin(); go != gameObjects.rend(); go++) {
    go->second->render(target, gameTime);
  }
}