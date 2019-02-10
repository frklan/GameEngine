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

  struct GameRunningData {
    bool running = true;
  };

  State gameState = GameRunning;

  union stateData {
    GameRunningData runningData;
  };
};

class GameFsm : public GameObject, public Observable<GameState> {
  public:
    GameFsm() = delete;
    GameFsm(const Scene& scene, uint8_t zOrder = 0);
    virtual ~GameFsm() = default;
    
    virtual void update(const sf::Time gameTime);
    virtual void handleEvent(const sf::Event& e);  

  private:
  bool isPaused = false;
  GameOfLife* gameOfLife = nullptr;
};