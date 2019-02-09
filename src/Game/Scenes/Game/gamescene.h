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