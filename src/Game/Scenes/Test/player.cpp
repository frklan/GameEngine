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
#include <EventBus.h>

#include "testscene.h"
#include "player.h"
#include "events.h"

class GameScene;

Player::Player(Scene& scene, uint8_t zOrder) : 
GameObject(scene, zOrder),
testscene(dynamic_cast<Test&>(scene))
{
  testscene.eventBus.subscribe(this, &Player::onFireEvent);
  
  std::clog << "Player created and ready.\n";
};


void Player::onRender(sf::RenderTarget& target, sf::Time gameTime) {
  auto& window{getScene().getGameEngine().getWindow()};
}

void Player::onEvent(const sf::Event& e) {
  
}

void Player::onFireEvent(FireEvent&) {
  std::clog << "Player::onFireEvent()\n";
}