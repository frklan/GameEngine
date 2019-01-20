#include <iostream>
#include <sstream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/OpenGL.hpp>

#include "player.h"

#include "../../../GameEngine/Scene.h"
#include "../../../GameEngine/ResourceManager.h"
#include "../../../GameEngine/GameObject.h"

Player::Player(const Scene& scene, uint8_t zOrder, float xOffset) : GameObject(scene, zOrder) {
  auto gameWindowSize = scene.getGameEngine().getWindowSize();

  rectangle.setFillColor(sf::Color::Red);
  rectangle.setSize(sf::Vector2f(25, 25));
  rectangle.setOrigin(sf::Vector2f(12.5f, 12.5f));
  rectangle.setPosition(sf::Vector2f(gameWindowSize.x / 2, gameWindowSize.y - 50));
}

void Player::update(sf::Time gameTime) {
  GameObject::update(gameTime);
  
  auto pos = this->rectangle.getPosition();
  auto psize = this->rectangle.getSize();
  auto winSize = getScene().getGameEngine().getWindowSize(); 
  sf::Vector2f newPos{0.f, 0.f};
  
  newPos.x = this->playerDirection.x * (gameTime.asSeconds() - frameTime.asSeconds());
  newPos.y = this->playerDirection.y * (gameTime.asSeconds() - frameTime.asSeconds());
    
  if(pos.x - psize.x < 0 && newPos.x < 0) {
    newPos.x = 0;
  } else if(pos.x + psize.x > winSize.x && newPos.x > 0) {
    newPos.x = 0;
  }
  if(pos.y - psize.y < 0 && newPos.y < 0) {
    newPos.y = 0;
  } else  if(pos.y + psize.y > winSize.y && newPos.y > 0) {
    newPos.y = 0;
  }
  
  this->rectangle.move(newPos);
  frameTime = gameTime;
}

void Player::render(sf::RenderTarget& target, sf::Time gameTime) {
  GameObject::render(target, gameTime);
  target.draw(rectangle);
}

void Player::handleEvent(const sf::Event& e) {
  if(e.type == sf::Event::KeyPressed){
    if (e.key.code == sf::Keyboard::Right) {
      playerDirection.x = speed;
    } else if (e.key.code == sf::Keyboard::Left) {
      playerDirection.x = -speed;
    } else if (e.key.code == sf::Keyboard::Up) {
      playerDirection.y = -speed;
    } else if (e.key.code == sf::Keyboard::Down) {
      playerDirection.y = speed;
    }
  } else if(e.type == sf::Event::KeyReleased){
    if (e.key.code == sf::Keyboard::Right || e.key.code == sf::Keyboard::Left) {
      playerDirection.x = 0;
    } else if (e.key.code == sf::Keyboard::Up || e.key.code == sf::Keyboard::Down) {
      playerDirection.y = 0.f;
    }
  }
}
