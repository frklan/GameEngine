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

#include "intrographics.h"
#include "sincurve.h"
#include "backgroundquad.h"

IntroGraphics::IntroGraphics(const Scene& scene, uint8_t zOrder) : 
GameObject(scene, zOrder)
 {
  
  addGameObject(std::make_unique<SinCurve>(scene, 0));
  addGameObject(std::make_unique<SinCurve>(scene, 0, 1));
  addGameObject(std::make_unique<SinCurve>(scene, 0, 2));
  addGameObject(std::make_unique<SinCurve>(scene, 0, 0.33f));
  addGameObject(std::make_unique<SinCurve>(scene, 0, 4));
  addGameObject(std::make_unique<SinCurve>(scene, 0, 5));
  addGameObject(std::make_unique<SinCurve>(scene, 0, 0.66f));
  addGameObject(std::make_unique<SinCurve>(scene, 0, 100, 0.75f));
  addGameObject(std::make_unique<SinCurve>(scene, 0, 110, 0.55f));
  addGameObject(std::make_unique<SinCurve>(scene, 0, 120, 0.35f));
  addGameObject(std::make_unique<SinCurve>(scene, 0, 130, 0.25f));
  addGameObject(std::make_unique<SinCurve>(scene, 0, 60, 0.75f));
  addGameObject(std::make_unique<SinCurve>(scene, 0, 170, 0.55f));
  addGameObject(std::make_unique<SinCurve>(scene, 0, 180, 0.35f));
  addGameObject(std::make_unique<SinCurve>(scene, 0, 290, 0.15f));

  addGameObject(std::make_unique<BackgroundQuad>(scene, 1000));
}

void IntroGraphics::update(const sf::Time gameTime) {
  GameObject::update(gameTime);
}

void IntroGraphics::render(sf::RenderTarget& target, sf::Time gameTime) { 
  GameObject::render(target, gameTime);
}

void IntroGraphics::handleEvent(const sf::Event& e) {
  GameObject::handleEvent(e);
}