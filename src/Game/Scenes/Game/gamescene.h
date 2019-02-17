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

#include <Event.h>
#include <GameEngine.h>
#include <GameObject.h>
#include <Observable.h>
#include <Observer.h>
#include <ResourceManager.h>
#include <Scene.h>

#include "gameoflife.h"

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

class GameScene : public Scene, public Observable<GameState> {
  public:
    GameScene() = delete;
    GameScene(GameEngine& engine);
    ~GameScene() = default;

    virtual bool onActivate() override;
    virtual bool onEvent(sf::Event& e) override;

  private:

  GameOfLife* gameOfLife = nullptr;
  bool isPaused = false;
  bool isGuiActive = false;
};