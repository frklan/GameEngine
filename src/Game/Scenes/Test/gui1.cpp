#include <iostream>

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

#include "../Game/gamescene.h"
#include "testscene.h"
#include "gui1.h"
#include "events.h"

class GameScene;

Gui1::Gui1(Scene& scene, uint8_t zOrder, std::string title) : 
GameObject(scene, zOrder),
testscene(dynamic_cast<Test&>(scene)),
title(title)
{

};


void Gui1::onRender(sf::RenderTarget& target, sf::Time gameTime) {
  auto& window{getScene().getGameEngine().getWindow()};

  ImGui::SFML::Update(window, gameTime);
  
  
  if(ImGui::Begin(title.c_str(), nullptr, ImGuiWindowFlags_None)) {
  

    if (ImGui::Button("Send 'Combat::Fire", {175,55})) {
      std::clog << "ImGui::Button('Send Combat::Fire')\n";
      testscene.eventBus.publish(FireEvent{});
    }

    if (ImGui::Button("Send 'Pause", {175,55})) {
      testscene.eventBus.publish(PauseEvent{});
    }

  }
  ImGui::End();
  
  ImGui::SFML::Render(window);
}
void Gui1::onEvent(const sf::Event& e) {
  ImGui::SFML::ProcessEvent(e);
}
