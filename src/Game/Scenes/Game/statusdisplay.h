#pragma once
#include <iostream>
#include <array>
#include <set>
#include <random>

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

#include "gameoflife.h"

class StatusDisplay : public GameObject, public Observer<GameState> {
  public:
    StatusDisplay() = delete;
    StatusDisplay(Scene& scene, uint8_t zOrder);
    
    virtual ~StatusDisplay() = default;
    
    virtual void onRender(sf::RenderTarget& target, sf::Time gameTime) override;
    virtual void onUpdate(const sf::Time gameTime) override;
    
    virtual void onNotify(GameState e) override;

  private:
    sf::Text pauseText;
    bool isPaused = false;
    sf::Clock blinkOn;
};

