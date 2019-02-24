#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <cstdint>
#include <vector>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/OpenGL.hpp>

#include <GameEngine.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <Scene.h>

#include <imgui/imgui.h>
#include <imgui-sfml/imgui-SFML.h>

#include "gameoflife.h"
#include "gui.h"

namespace gamescene {
  Gui::Gui(Scene& gameScene, uint8_t zOrder) : 
  GameObject(gameScene, zOrder),
  scene(gameScene),
  window(gameScene.getGameEngine().getWindow())
  { 
    text.setFillColor(sf::Color::Cyan);
    text.setPosition({1000, 500});
    text.setFont(scene.getGameEngine().getFontResource("src/Game/Resources/pixel_operator/PixelOperator8.ttf"));
    text.setCharacterSize(35);
    text.setString("GUI Goes here.");

    ImGui::SFML::Init(window);
    ImGui::GetIO().IniFilename = nullptr;

    scene.getEventBus().subscribe(this, &Gui::onGuiEvent);
  }


  void Gui::onEvent(const sf::Event& e) {
    if(isEnabled) {
      ImGui::SFML::ProcessEvent(e);
    }
  }

  void Gui::onRender(sf::RenderTarget&, sf::Time gameTime) {
    if(isEnabled) {
      ImGui::SFML::Update(window, gameTime);

      if(ImGui::Begin(" ", nullptr, 
        ImGuiWindowFlags_NoMove | 
        ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoCollapse)) {
      

        auto winSize{window.getSize()};
        ImVec2 dialogSize {191, 226};
        ImGui::SetWindowSize(dialogSize);
        ImGui::SetWindowPos(ImVec2(winSize.x - 10 - dialogSize.x, winSize.y / 2 - dialogSize.y / 2), ImGuiCond_Always );

        if (ImGui::Button("Pause", {175,35})) {
          scene.getEventBus().publish(game::GamePauseEvent{});
        }

        if (ImGui::Button("Clear", {175,35})) {
          scene.getEventBus().publish(game::GameClearEvent{});
        }

        if (ImGui::Button("Randomize", {175,35})) {
          scene.getEventBus().publish(game::GameResetEvent{});
        }

        if (ImGui::Button("Close GUI", {175,35})) {
          scene.getEventBus().publish(game::GuiEvent{});
        }

        if (ImGui::Button("End Game", {175,35})) {
          scene.getEventBus().publish(game::GameEndEvent{});
        }
      }
      ImGui::End();
      
      ImGui::SFML::Render(window);
    }
  }

  void Gui::onGuiEvent(game::GuiEvent&) {
    isEnabled = !isEnabled;
  }
}
