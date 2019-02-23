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

namespace gamescene {
  class Gui : public GameObject {
    public:
      Gui() = delete;
      Gui(Scene& scene, uint8_t zOrder);
      
      virtual ~Gui() = default;
      
      virtual void onEvent(const sf::Event& e) override;
      virtual void onRender(sf::RenderTarget& target, sf::Time gameTime) override;
      
      void onGuiEvent(game::GuiEvent& e);

    private:
      Scene& scene;
      sf::Text text;
      sf::RenderWindow& window;
      bool isEnabled = false;
      sf::Vector2u windowSize;
  };
}
