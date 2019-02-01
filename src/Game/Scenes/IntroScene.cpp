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

#include "introscene.h"
#include "gamescene.h"

#include "../GameObjects/Gui/gui.h"
#include "../GameObjects/IntroGraphics/intrographics.h"
#include "../GameObjects/DebugView/debugview.h"
#include "../../GameEngine/Scene.h"
#include "../../GameEngine/ResourceManager.h"
#include "../../GameEngine/GameEngine.h"


Intro::Intro(GameEngine& engine) : Scene(engine) { 
  std::clog << "Intro scene created!\n"; 

  addGameObject(std::make_unique<Debugview>(*this, 0));
  addGameObject(std::make_unique<Gui>(*this, 10));
  addGameObject(std::make_unique<IntroGraphics>(*this, 1000));
}

Intro::~Intro() { 
  std::clog << "Intro scene destroyed!\n"; 
}

void Intro::onActivate() { 
  Scene::onActivate();

  gameEngine.setFramerateLimit(60);
  std::clog << "Intro::onActivate()\n";

  auto& window{getGameEngine().getWindow()};
  ImGui::SFML::Init(window);

  imFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("/Users/fredrik/Source/c/cpp/GameEngine/src/Game/Resources/8-BIT_WONDER.TTF", 16);
  ImGui::SFML::UpdateFontTexture();
};

void Intro::onDeactivate() {
  Scene::onDeactivate();

  std::clog << "Intro::onDeactivate()\n";

  ImGui::SFML::Shutdown();
};

void Intro::handleEvent(sf::Event& e) {
  Scene::handleEvent(e);

  // if(e.type == sf::Event::MouseButtonPressed) {
  //   gameEngine.addScene("game", std::make_unique<GameScene>(gameEngine));
  //   gameEngine.switchScene("game");
  // }
}

ImFont* Intro::getImFont() const {
  return imFont;
}