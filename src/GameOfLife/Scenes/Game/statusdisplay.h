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

#include <GameEngine.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <Scene.h>

#include "gameoflife.h"

class StatusDisplay : public GameObject {
  public:
    StatusDisplay() = delete;
    StatusDisplay(Scene& scene, uint8_t zOrder);
    
    virtual ~StatusDisplay() override = default;
    
    virtual void onRender(sf::RenderTarget& target, sf::Time gameTime) override;
    virtual void onUpdate(const sf::Time gameTime) override;

    void onGamePauseEvent(game::GamePauseEvent& e);
    
  private:
    sf::Text pauseText;
    bool isPaused = false;
    sf::Clock blinkOn;
};
