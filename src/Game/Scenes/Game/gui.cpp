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
  Gui::Gui(Scene& scene, uint8_t zOrder) : 
  GameObject(scene),
  scene(scene),
  window(scene.getGameEngine().getWindow())
  { 
    text.setFillColor(sf::Color::Cyan);
    text.setPosition({1000, 500});
    text.setFont(scene.getGameEngine().getFontResource("src/Game/Resources/pixel_operator/PixelOperator8.ttf"));
    text.setCharacterSize(35);
    text.setString("GUI Goes here.");

    ImGui::SFML::Init(window);
    ImGui::GetIO().IniFilename = NULL;
  }

  void Gui::onUpdate(sf::Time gameTime) {

  }

  void Gui::onEvent(const sf::Event& e) {
    ImGui::SFML::ProcessEvent(e);
  }

  void Gui::onRender(sf::RenderTarget& target, sf::Time gameTime) {
    auto windowSize = scene.getGameEngine().getWindowSize();
    
    ImGui::SFML::Update(window, gameTime);

    if(ImGui::Begin("Main menu", nullptr, ImGuiWindowFlags_None)) {
    
      auto winSize{window.getSize()};
      ImVec2 dialogSize {250, 600};
      ImGui::SetWindowSize(dialogSize);
      ImGui::SetWindowPos(ImVec2(winSize.x / 2 - dialogSize.x / 2, winSize.y / 2 - dialogSize.y / 2), true);
    

      if (ImGui::Button("Pause", {175,55})) {
        std::clog << "pause game\n";
      }

      if (ImGui::Button("Close", {175,55})) {
        scene.deleteGameObject(this);
        return;
      }

    }
    ImGui::End();
    
    ImGui::SFML::Render(window);
    
    target.draw(text);
  }
}
