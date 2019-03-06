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

#include "introscene.h"
#include "events.h"
#include "gui.h"
#include "sincurve.h"
#include "backgroundquad.h"
#include "../Game/gamescene.h"
#include "../Common/DebugView/debugview.h"


Intro::Intro(GameEngine& engine) : Scene(engine) { 
  std::clog << "Intro scene created!\n"; 

  getEventBus().subscribe(this, &Intro::onStartGameEvent);
  getEventBus().subscribe(this, &Intro::onQuitEvent);
  

  addGameObject(std::make_unique<Debugview>(*this, 0));
  addGameObject(std::make_unique<Gui>(*this, 10));
  //addGameObject(std::make_unique<IntroGraphics>(*this, 1000));

  addGameObject(std::make_unique<SinCurve>(*this, 100));
  addGameObject(std::make_unique<SinCurve>(*this, 100, 1));
  addGameObject(std::make_unique<SinCurve>(*this, 100, 2));
  addGameObject(std::make_unique<SinCurve>(*this, 100, 0.33f));
  addGameObject(std::make_unique<SinCurve>(*this, 100, 4));
  addGameObject(std::make_unique<SinCurve>(*this, 100, 5));
  addGameObject(std::make_unique<SinCurve>(*this, 100, 0.66f));
  addGameObject(std::make_unique<SinCurve>(*this, 100, 100, 0.75f));
  addGameObject(std::make_unique<SinCurve>(*this, 100, 110, 0.55f));
  addGameObject(std::make_unique<SinCurve>(*this, 100, 120, 0.35f));
  addGameObject(std::make_unique<SinCurve>(*this, 100, 130, 0.25f));
  addGameObject(std::make_unique<SinCurve>(*this, 100, 60, 0.75f));
  addGameObject(std::make_unique<SinCurve>(*this, 100, 170, 0.55f));
  addGameObject(std::make_unique<SinCurve>(*this, 100, 180, 0.35f));
  addGameObject(std::make_unique<SinCurve>(*this, 100, 290, 0.15f));

  addGameObject(std::make_unique<BackgroundQuad>(*this, 1000));
}

Intro::~Intro() { 
  std::clog << "Intro scene destroyed!\n"; 
}

bool Intro::onActivate() { 
  gameEngine.setFramerateLimit(60);
  std::clog << "Intro::onActivate()\n";

  auto& window{getGameEngine().getWindow()};
  ImGui::SFML::Init(window);
  ImGui::GetIO().IniFilename = nullptr;

  auto fontPath = getGameEngine().getFontResourceAboslutePath("Resources/undefined-medium.ttf");
  imFont = ImGui::GetIO().Fonts->AddFontFromFileTTF(fontPath.c_str(), 16);
  ImGui::SFML::UpdateFontTexture();
  return true;
};

bool Intro::onDeactivate() {
  std::clog << "Intro::onDeactivate()\n";
  ImGui::SFML::Shutdown();
  return true;
};

ImFont* Intro::getImFont() const {
  return imFont;
}

void Intro::onStartGameEvent(StartGameEvent&) {
    gameEngine.switchScene("game");
}

void Intro::onQuitEvent(QuitEvent&) {
  std::clog << "QUIT!\n";
  gameEngine.getWindow().close();
}

