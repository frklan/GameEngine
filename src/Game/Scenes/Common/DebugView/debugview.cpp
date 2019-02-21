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

#include "debugview.h"

Debugview::Debugview(const Scene& scene, uint8_t zOrder) : GameObject(scene, zOrder) {
  std::clog << "debugView created!\n";
  this->debugText.setPosition(10, 10);
  this->debugText.setFont(getScene().getGameEngine().getFontResource("src/Game/Resources/undefined-medium.ttf"));
  this->debugText.setFillColor(sf::Color::White);
  this->debugText.setCharacterSize(20);
  this->debugText.setLineSpacing(1);
  this->debugText.setString("<debug text goes here>");

  std::stringstream info;
  auto glInfo = scene.getGameEngine().getGlInfo();
  info << glInfo.glVendor << " " << glInfo.glRenderer << '\n'
       << glInfo.glVersion << " / " << glInfo.glShaderVersion;
  this->gpuInfo.setFont(getScene().getGameEngine().getFontResource("src/Game/Resources/undefined-medium.ttf"));
  this->gpuInfo.setFillColor(sf::Color::White);
  this->gpuInfo.setCharacterSize(20);
  this->gpuInfo.setLineSpacing(1);
  this->debugText.setPosition(10, 10);
  this->gpuInfo.setString(info.str());

  auto gpuInfoBounds(this->gpuInfo.getLocalBounds());
  auto windowSize = scene.getGameEngine().getWindowSize();
  this->gpuInfo.setOrigin(gpuInfoBounds.width, 0);
  this->gpuInfo.setPosition(windowSize.x - 10, 10);
}

void Debugview::onUpdate(const sf::Time gameTime) {
  if(gameTime - lastUpdate > sf::seconds(0.5f)) {
    std::stringstream debugString;
    debugString << "GameEngine v" << "0.1.0" << '\n' \
      << getScene().getNumOfEntities() << " entities\n" \
      << "fps: " << getScene().getGameEngine().getFps() << '\n' \
      << "tps: " << getScene().getGameEngine().getTps()<< '\n' \
      << "tps lag: " <<  getScene().getGameEngine().getFrameLag().count() << " mS\n"
      << "fps lag: " <<  1000.0f / getScene().getGameEngine().getFps() << " mS\n";
    
    this->debugText.setString(debugString.str());
    lastUpdate = gameTime;
  }
}

void Debugview::onRender(sf::RenderTarget& target, sf::Time gameTime) {
  if(showDebug) {
    target.draw(this->debugText);
    target.draw(this->gpuInfo);
  }
}

void Debugview::onEvent(const sf::Event& e) {
  if(e.type == sf::Event::Resized) {
    auto gpuInfoBounds(this->gpuInfo.getLocalBounds());
    sf::FloatRect windowSize(0, 0, e.size.width, e.size.height);

    this->gpuInfo.setOrigin(gpuInfoBounds.width, 0);
    this->gpuInfo.setPosition(windowSize.width - 10, 10);
  } else if(e.type == sf::Event::KeyPressed) {
    if (e.key.code == sf::Keyboard::F3)
    {
      this->showDebug = !this->showDebug;
      std::clog << showDebug << '\n';
    }
  }
}