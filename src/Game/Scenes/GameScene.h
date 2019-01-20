#pragma once
#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/OpenGL.hpp>

#include "../../GameEngine/Scene.h"
#include "../../GameEngine/ResourceManager.h"
#include "../GameObjects/Player/player.h"

class GameScene : public Scene {
  public:
    GameScene() = delete;
    GameScene(GameEngine& engine);
    ~GameScene();

    void handleEvent(sf::Event& e);
    void update(sf::Time gameTimeMs);
    void onActivate();
    void onDeactivate();

  private:
};