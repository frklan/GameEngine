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

#include "../../../GameEngine/Scene.h"
#include "../../../GameEngine/ResourceManager.h"
#include "../../../GameEngine/GameObject.h"
#include "../../../GameEngine/Observer.h"
#include "../../../GameEngine/Event.h"

#include "gameoflife.h"


class StatusDisplay : public GameObject, public Observer {
  public:
    StatusDisplay() = delete;
    StatusDisplay(const Scene& scene, uint8_t zOrder);
    
    virtual ~StatusDisplay() = default;
    
    virtual void update(const sf::Time gameTime) override;
    virtual void render(sf::RenderTarget& target, sf::Time gameTime) override;
    virtual void handleEvent(const sf::Event& e) override;

    virtual void onNotify(Event e) override;

  private:
    sf::Text pauseText;
    bool isPaused = false;
    sf::Clock blinkOn;
};

