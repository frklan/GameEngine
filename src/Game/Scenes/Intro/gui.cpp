#include <iostream>

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

#include "../Game/gamescene.h"
#include "introscene.h"
#include "gui.h"

class GameScene;

Gui::Gui(const Scene& scene, uint8_t zOrder) : GameObject(scene, zOrder) {
};


void Gui::onUpdate(const sf::Time gameTime) {

}

void Gui::onRender(sf::RenderTarget& target, sf::Time gameTime) {
  auto& window{getScene().getGameEngine().getWindow()};

  ImGui::SFML::Update(window, gameTime);
  
  if(ImGui::Begin("Main menu", nullptr, 
    ImGuiWindowFlags_NoTitleBar | 
    ImGuiWindowFlags_NoBackground |
    ImGuiWindowFlags_NoResize | 
    ImGuiWindowFlags_NoMove)) {
  
    auto winSize{window.getSize()};
    ImVec2 dialogSize {195, 400};
    ImGui::SetWindowSize(dialogSize);
    ImGui::SetWindowPos(ImVec2(winSize.x / 2 - dialogSize.x / 2, winSize.y / 2 - dialogSize.y / 2), true);

    const Intro& intro = dynamic_cast<const Intro&>(getScene());
    ImGui::PushFont(intro.getImFont());

    if (ImGui::Button("Start Game!", {175,55})) {
      this->getScene().getGameEngine().addScene("game", std::make_unique<GameScene>(this->getScene().getGameEngine()));
      this->getScene().getGameEngine().switchScene("game");
      return;
    }

    if (ImGui::Button("Quit", {175,55})) {
      this->getScene().getGameEngine().getWindow().close();
    }

    ImGui::PopFont();
  }
  ImGui::End();
  
  ImGui::SFML::Render(window);
}
void Gui::onEvent(const sf::Event& e) {
  ImGui::SFML::ProcessEvent(e);
}
