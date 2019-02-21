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

#include <GameEngine.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <Scene.h>
#include <EventBus.h>

#include "events.h"

class Test : public Scene {
  public:
    Test() = delete;
    Test(GameEngine& engine);
    virtual ~Test() = default;

    virtual void onFireEvent(FireEvent& e);
    virtual void onPauseEvent(PauseEvent& e);

    virtual bool onActivate() override;
    virtual bool onDeactivate() override;

    eventbus::EventBus eventBus;
  private:
    
};