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

#include <GameEngine.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <Scene.h>

#include "backgroundquad.h"

BackgroundQuad::BackgroundQuad(Scene& scene, uint8_t zOrder) : 
GameObject(scene, zOrder),
windowSize(getScene().getGameEngine().getWindowSize())
{
  createBackground();
}

void BackgroundQuad::onUpdate(const sf::Time gameTime) {
  for(size_t i = 0; i < quad.size(); i++){
    float dT = gameTime.asSeconds() + i / float(quad.size() / 2);
    auto sdT = sin(dT) * 360;
    quad[i].color = sf::Color(hsvToRgb(sdT, 1.0f, 0.2f));
  }
}

void BackgroundQuad::onRender(sf::RenderTarget& target, sf::Time) {
  target.draw(quad.data(), quad.size(), sf::PrimitiveType::Quads);
}

void BackgroundQuad::onEvent(const sf::Event& e) {
  if(e.type == sf::Event::Resized) {
    windowSize = getScene().getGameEngine().getWindowSize();
    createBackground();
  }
}

void BackgroundQuad::createBackground() {
  quad[0] = sf::Vertex{{0, 0}, sf::Color::Blue};
  quad[1] = sf::Vertex{{float(windowSize.x), 0}, sf::Color::Blue};
  quad[2] = sf::Vertex{{float(windowSize.x), float(windowSize.y)}, sf::Color::Blue};
  quad[3] = sf::Vertex{{0, float(windowSize.y)}, sf::Color::Blue};
}

// TODO: fix number formats..
sf::Color BackgroundQuad::hsvToRgb(long long hue, float sat, float val) {
  hue %= 360;
  while(hue<0) hue += 360;

  if(sat<0.f) sat = 0.f;
  if(sat>1.f) sat = 1.f;

  if(val<0.f) val = 0.f;
  if(val>1.f) val = 1.f;

  int h = int(hue/60);
  float f = float(hue)/60-h;
  float p = val*(1.f-sat);
  float q = val*(1.f-sat*f);
  float t = val*(1.f-sat*(1-f));

  switch(h)
  {
    default:
    case 0:
    case 6: return sf::Color(uint8_t(val*255), uint8_t(t*255), uint8_t(p*255));
    case 1: return sf::Color(uint8_t(q*255), uint8_t(val*255), uint8_t(p*255));
    case 2: return sf::Color(uint8_t(p*255), uint8_t(val*255), uint8_t(t*255));
    case 3: return sf::Color(uint8_t(p*255), uint8_t(q*255), uint8_t(val*255));
    case 4: return sf::Color(uint8_t(t*255), uint8_t(p*255), uint8_t(val*255));
    case 5: return sf::Color(uint8_t(val*255), uint8_t(p*255), uint8_t(q*255));
  }
}
