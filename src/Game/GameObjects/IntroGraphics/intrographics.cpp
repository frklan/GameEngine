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

IntroGraphics::IntroGraphics(const Scene& scene, uint8_t zOrder) : GameObject(scene, zOrder) {
  windowSize.x = getScene().getGameEngine().getWindowSize().x;
  windowSize.y = getScene().getGameEngine().getWindowSize().y;

  for(auto i = 0; i < vs.size(); i++){
    vs[i] = sf::Vertex{{float((float(windowSize.x) / (float(vs.size()) - 1.f) * i)), 100}, sf::Color::Blue};    
  }
  quad[0] = sf::Vertex{{0, 0}, sf::Color::Blue};
  quad[1] = sf::Vertex{{float(windowSize.x), 0}, sf::Color::Blue};
  quad[2] = sf::Vertex{{float(windowSize.x), float(windowSize.y)}, sf::Color::Blue};
  quad[3] = sf::Vertex{{0, float(windowSize.y)}, sf::Color::Blue};
  vertexClock.restart();
}

void IntroGraphics::update(const sf::Time gameTime) {
  for(auto i = 0; i < vs.size(); i++) {
    auto p = vs[i].position;

    float dT = gameTime.asSeconds() + i / float(vs.size() / 2);
    auto sdT = sin(dT);
    p.y = sdT * (windowSize.y / 2 - 25) + windowSize.y / 2;
    vs[i].position = p;

    auto hue = 360 * sdT;
    vs[i].color = sf::Color(hsvToRgb(hue, 128, 255 ));
  }

  for(auto i = 0; i < quad.size(); i++){
    float dT = gameTime.asSeconds() + i / float(quad.size() / 2);
    auto sdT = sin(dT);
    quad[i].color = sf::Color(hsvToRgb(360 * sdT, 1, 0.2 ));
  }
  return;
}

void IntroGraphics::render(sf::RenderTarget& target, sf::Time gameTime) {  
  target.draw(quad.data(), quad.size(), sf::PrimitiveType::Quads);
  target.draw(vs.data(), vs.size(), sf::PrimitiveType::LineStrip);
}

void IntroGraphics::handleEvent(const sf::Event& e) {
  if(e.type == sf::Event::Resized) {
    windowSize.x = e.size.width;
    windowSize.y = e.size.height;

    quad[0] = sf::Vertex{{0, 0}, sf::Color::Blue};
    quad[1] = sf::Vertex{{float(windowSize.x), 0}, sf::Color::Blue};
    quad[2] = sf::Vertex{{float(windowSize.x), float(windowSize.y)}, sf::Color::Blue};
    quad[3] = sf::Vertex{{0, float(windowSize.y)}, sf::Color::Blue};
  }
}

sf::Color IntroGraphics::hsvToRgb(long long hue, float sat, float val) {
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