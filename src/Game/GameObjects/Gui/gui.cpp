#include <iostream>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/OpenGL.hpp>

#include "gui.h"
#include "../../Scenes/gamescene.h"
#include "../../Scenes/introscene.h"

Gui::Gui(const Scene& scene, uint8_t zOrder) : GameObject(scene, zOrder) {
};

Gui::~Gui() {
}

void Gui::update(const sf::Time gameTime) {

}

void Gui::render(sf::RenderTarget& target, sf::Time gameTime) {
  auto& window{getScene().getGameEngine().getWindow()};
  ImGui::SFML::Update(window, gameTime);
  
  if(ImGui::Begin("Sample window", nullptr, 
    ImGuiWindowFlags_NoTitleBar | 
    ImGuiWindowFlags_NoBackground | 
    ImGuiWindowFlags_NoResize | 
    ImGuiWindowFlags_NoMove)) {
  
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

  ImGui::ShowDemoWindow();
  ImGui::ShowUserGuide();

  ImGui::Begin("Window2");
  ImGui::LabelText("Hello World!", "");
  ImGui::End();

  ImGui::SFML::Render(window);
}
void Gui::handleEvent(const sf::Event& e) {
  GameObject::handleEvent(e);
  ImGui::SFML::ProcessEvent(e);
}
