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

#include "../../GameEngine/Scene.h"
#include "../../GameEngine/ResourceManager.h"
#include "../../GameEngine/GameEngine.h"


class Intro : public Scene {
  public:
    Intro() = delete;
    Intro(GameEngine& engine);
    ~Intro();

    void handleEvent(sf::Event& e) override;
    void onActivate() override;
    void onDeactivate() override;

    ImFont* getImFont() const;

  private:
    sf::Text text;
    sf::Font f;
    sf::Time lastUpdate = sf::Time::Zero;

    ImFont* imFont;
};