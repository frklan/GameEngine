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

#include <Event.h>
#include <GameEngine.h>
#include <GameObject.h>
#include <Observable.h>
#include <Observer.h>
#include <ResourceManager.h>
#include <Scene.h>

#include "sincurve.h"

SinCurve::SinCurve(const Scene& scene, uint8_t zOrder, uint16_t xOffset, float yOffset) : 
GameObject(scene, zOrder),
curveOffsetX(xOffset),
curveOffsetY(yOffset),
windowSize(getScene().getGameEngine().getWindowSize())
 {
  createCurve();
  vertexClock.restart();
}

void SinCurve::onUpdate(const sf::Time gameTime) {
  auto f = sin(gameTime.asSeconds() / float(curveOffsetX));

  for(auto i = 0; i < curve.size(); i++) {
    auto p = curve[i].position;
       
    float dT = gameTime.asSeconds() + (i  / float(curve.size() / (6 / curveOffsetY) )) + f;
    auto sdT = sin(dT);
    p.y = curveOffsetY * sdT * (windowSize.y / 2 - 25) + (windowSize.y / 2);
    curve[i].position = p;

    auto hue = 360 * sdT;
    curve[i].color = sf::Color(hsvToRgb(hue, 128, 255 ));
  }
}

void SinCurve::onRender(sf::RenderTarget& target, sf::Time gameTime) {  
  target.draw(curve.data(), curve.size(), sf::PrimitiveType::LineStrip);
}

void SinCurve::onEvent(const sf::Event& e) {
  if(e.type == sf::Event::Resized) {
    windowSize = getScene().getGameEngine().getWindowSize();
    createCurve();
  }
}

void SinCurve::createCurve() {
  for(auto i = 0; i < curve.size(); i++){
    curve[i] = sf::Vertex{{float((float(windowSize.x) / (float(curve.size()) - 1.f) * i)), 100}, sf::Color::Blue};    
  }
}

sf::Color SinCurve::hsvToRgb(long long hue, float sat, float val) {
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