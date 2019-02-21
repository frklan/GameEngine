#include <iostream>
#include <sstream>
#include <memory>

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


#include "testscene.h"
#include "gui1.h"
#include "player.h"
#include "../Common/DebugView/debugview.h"
#include "events.h"


Test::Test(GameEngine& engine) : Scene(engine) { 
  
  eventBus.subscribe(this, &Test::onFireEvent);
  eventBus.subscribe(this, &Test::onPauseEvent);

  addGameObject(std::make_unique<Gui1>(*this, 5, "Gui #1"));
  addGameObject(std::make_unique<Player>(*this, 5));

  addGameObject(std::make_unique<Debugview>(*this, 0));
  
}

void Test::onFireEvent(FireEvent&) {
  std::clog << "Test::onFireEvent() - Event reveived!\n";
}

void Test::onPauseEvent(PauseEvent&) {
  std::clog << "Test::onPauseEvent() - Event reveived!\n";
}

bool Test::onActivate() { 
 
  auto& window{getGameEngine().getWindow()};
  ImGui::SFML::Init(window);

  return true;
};

bool Test::onDeactivate() {
 
  ImGui::SFML::Shutdown();
  return true;
};
