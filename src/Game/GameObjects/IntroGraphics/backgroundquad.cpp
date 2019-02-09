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

#include "backgroundquad.h"

BackgroundQuad::BackgroundQuad(const Scene& scene, uint8_t zOrder) : 
GameObject(scene, zOrder),
windowSize(getScene().getGameEngine().getWindowSize())
{
  createBackground();
}

void BackgroundQuad::update(const sf::Time gameTime) {
  for(auto i = 0; i < quad.size(); i++){
    float dT = gameTime.asSeconds() + i / float(quad.size() / 2);
    auto sdT = sin(dT);
    quad[i].color = sf::Color(hsvToRgb(360 * sdT, 1, 0.2 ));
  }
}

void BackgroundQuad::render(sf::RenderTarget& target, sf::Time gameTime) {
  target.draw(quad.data(), quad.size(), sf::PrimitiveType::Quads);
}

void BackgroundQuad::handleEvent(const sf::Event& e) {
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

sf::Color BackgroundQuad::hsvToRgb(long long hue, float sat, float val) {
  hue %= 360;
  while(hue<0) hue += 360;

  if(sat<0.f) sat = 0.f;
  if(sat>1.f) sat = 1.f;

  if(val<0.f) val = 0.f;
  if(val>1.f) val = 1.f;

  int h = hue/60;
  float f = float(hue)/60-h;
  float p = val*(1.f-sat);
  float q = val*(1.f-sat*f);
  float t = val*(1.f-sat*(1-f));

  switch(h)
  {
    default:
    case 0:
    case 6: return sf::Color(val*255, t*255, p*255);
    case 1: return sf::Color(q*255, val*255, p*255);
    case 2: return sf::Color(p*255, val*255, t*255);
    case 3: return sf::Color(p*255, q*255, val*255);
    case 4: return sf::Color(t*255, p*255, val*255);
    case 5: return sf::Color(val*255, p*255, q*255);
  }
}