#pragma once
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

#include <imgui/imgui.h>
#include <imgui-sfml/imgui-SFML.h>

#include <EventBus.h>

#include <GameEngine.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <Scene.h>

#include "events.h"


class Intro : public Scene {
  public:
    Intro() = delete;
    Intro(GameEngine& engine);
    
    virtual ~Intro() override;

    virtual bool onActivate() override;
    virtual bool onDeactivate() override;

    ImFont* getImFont() const;

    void onStartGameEvent(StartGameEvent& e);
    void onQuitEvent(QuitEvent& e);

  private:
    sf::Text text;
    sf::Font f;
    sf::Time lastUpdate = sf::Time::Zero;

    ImFont* imFont;
};
