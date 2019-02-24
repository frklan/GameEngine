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

#include <imgui/imgui.h>
#include <imgui-sfml/imgui-SFML.h>

#include "gameoflife.h"
#include "grid.h"
#include "cursor.h"
#include "statusdisplay.h"
#include "../Common/DebugView/debugview.h"

#include "gameoflife.h"
#include "gamescene.h"
#include "gui.h"
#include "events.h"

class GameOfLife;

GameScene::GameScene(GameEngine& engine) : Scene(engine) {   
  
}

bool GameScene::onActivate() { 
  gameEngine.setFramerateLimit(120);
    
  ImGui::SFML::Init(getGameEngine().getWindow());
  ImGui::GetIO().IniFilename = nullptr;

  //imFont = ImGui::GetIO().Fonts->AddFontFromFileTTF("src/Game/Resources/undefined-medium.ttf", 16);
  //ImGui::SFML::UpdateFontTexture();

  auto gol = this->addGameObject(std::make_unique<GameOfLife>(*this, 20));
  gameOfLife = dynamic_cast<GameOfLife*>(gol);

  this->addGameObject(std::make_unique<Debugview>(*this, 0));
  this->addGameObject(std::make_unique<Grid>(*this, 10));
  this->addGameObject(std::make_unique<Cursor>(*this, 5));
  this->addGameObject(std::make_unique<StatusDisplay>(*this, 0));
  this->addGameObject(std::make_unique<gamescene::Gui>(*this, 0));

  getEventBus().subscribe(this, &GameScene::onGameEndEvent);

  return true;
}

 bool GameScene::onDeactivate() {
   ImGui::SFML::Shutdown();

   auto gos = this->getGameObjects<GameObject>();
   for(auto g : gos) {
     this->deleteGameObject(g);
   }
   
  getEventBus().reset();
   
  return true;

   
 }

bool GameScene::onEvent(sf::Event& e) {
  
  // Consume "our" events by returning true
  if(e.type == sf::Event::EventType::Resized) {
    getEventBus().publish(game::WindowResizeEvent{{e.size.width, e.size.height}});
    return false; // TODO: return true when all our children listen to this event.
  } else if(e.type == sf::Event::EventType::KeyPressed) {
    if(e.key.code == sf::Keyboard::P) {
      getEventBus().publish(game::GamePauseEvent{});  
      return true;
    } else if(e.key.code == sf::Keyboard::Key::C) {
      //gameOfLife->killAllCells();
      getEventBus().publish(game::GameClearEvent{});
      return true;
    } else if(e.key.code == sf::Keyboard::Key::Escape) {
      getEventBus().publish(game::GuiEvent{});      
      return true;
    }
  }

  // false == event not handled.
  return false;
}

void GameScene::onGameEndEvent(game::GameEndEvent&) {
    gameEngine.switchScene("intro");
}
