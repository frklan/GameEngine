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

#include <GameEngine.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <Scene.h>

#include "gameoflife.h"
#include "events.h"

class GameOfLife;

struct GameState {
  enum State {
    GameRunning,
    GameOver,
    GamePaused,
    GameGui,
    GameQuit
  };

  State gameState;
};

class GameScene : public Scene {
  public:
    GameScene() = delete;
    GameScene(GameEngine& engine);
    
    virtual ~GameScene() override = default;

    virtual bool onActivate() override;
    virtual bool onDeactivate() override;
    virtual bool onEvent(sf::Event& e) override;

    void onGameEndEvent(game::GameEndEvent& e);

  private:

  GameOfLife* gameOfLife = nullptr;
};
