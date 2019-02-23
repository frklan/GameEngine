#include <iostream>
#include <exception>
#include <vector>
#include <sstream>
#include <cstdint>
#include <exception>
#include <unordered_map>
#include <thread>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/OpenGL.hpp>

#include "GameEngine.h"

using namespace std;

GameEngine::GameEngine() : 
gameWindow{sf::VideoMode(WIDTH, HEIGHT), "<--- GameEngine --->"},
frameLag(sf::Time::Zero),
TPS(20),
timePerTick(sf::seconds(1.0f / TPS))
{
  auto winSize = gameWindow.getSize();
  gameView.setSize(sf::Vector2f(winSize.x, winSize.y));
  gameView.setCenter(sf::Vector2f(winSize.x / 2, winSize.y / 2));
  gameWindow.setView(gameView);

  auto icon = getImageResource("src/Game/Resources/logo.png");
  gameWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

  gameWindow.display();
  setVerticalSyncEnabled(false);

  // auto fullScreenModes = getFullscreenVideoModes();
  // std::clog << "Available full screen video modes are:\n";
  // for(auto m : fullScreenModes) {
  //   std::clog << m.width << 'x' << m.height << ':' << m.bitsPerPixel << '\n';
  // }

  // auto desktopMode = getWindowedVideoMode();
  // std::clog << "Available desktop video mode are:\n";
  // std::clog << desktopMode.width << 'x' << desktopMode.height << ':' << desktopMode.bitsPerPixel << '\n';
}

void GameEngine::addScene(std::string name, std::unique_ptr<Scene> scene) {
  auto s = this->scenes.insert({name, std::move(scene)});
  if(!s.second) {
    throw std::runtime_error("Scene \"" + name + "\" already present");
  }

  if(currentScene == nullptr) {
    switchScene(name);
  }
}

void GameEngine::switchScene(std::string name) {
  auto s = scenes.find(name);
  if(s != scenes.end()) {
    if(currentScene != nullptr) {
      currentScene->onDeactivate();
    }
    currentScene = s->second.get();
    currentScene->onActivate();
  } else {
    std::cerr << "could not switch to scene " << name << '\n';
  }
}

void GameEngine::unloadScene(std::string name) {
  auto toUnload = scenes.find(name);

  if(toUnload == scenes.end()) {
    throw std::runtime_error("could not unload: scene \"" + name + "\" does not exists\n");
  } else if(toUnload->second.get() == this->currentScene) {
    throw std::runtime_error("could not unload: scene \"" + name + "\" is current scene\n");
  } else {
    scenes.erase(toUnload);
  }
}

int GameEngine::run() {
  cout << "<-- GameEngine::run() -->" << endl;

  sf::Event ev;
  while(gameWindow.isOpen()) {
    /* Handle events */
    while(gameWindow.pollEvent(ev)) {
      if(ev.type == sf::Event::Closed) {
          gameWindow.close();
      } else if(ev.type == sf::Event::Resized) {
        auto winSize = gameWindow.getSize();
        gameView.setSize(sf::Vector2f(winSize.x, winSize.y));
        gameView.setCenter(sf::Vector2f(winSize.x / 2, winSize.y / 2));
        gameWindow.setView(gameView);
      }
      currentScene->event(ev);
    }

     /* Update all data and entites */
      frameLag += frameClock.restart();
      
      while(frameLag > timePerTick) {
        // call update() on current scence here.
        currentScene->update(gameClock.getElapsedTime());

        currentTPS = 1 / frameLag.asSeconds();
        frameLag -= timePerTick;
      }

      /* Draw stuff */
      fps = 1.f / fpsClock.restart().asSeconds();
      gameWindow.clear(sf::Color::Black);

      // call render() on current cene
      currentScene->render(gameWindow, gameClock.getElapsedTime());
      
      gameWindow.display();
  }
  std::clog << "Game loop finished!" << '\n';
  return 0; 
}

const sf::Font& GameEngine::getFontResource(const std::string& name) {
  return fontManager.get(name);
}

const sf::Texture& GameEngine::getTextureResource(const std::string& name) {
  return textureManager.get(name);
}

const sf::Image& GameEngine::getImageResource(const std::string& name) {
  return imageManager.get(name);
}

void GameEngine::setVerticalSyncEnabled(bool enabled) {
  gameWindow.setVerticalSyncEnabled(enabled);
}
void GameEngine::setFramerateLimit(uint8_t fpsLimit) {
  gameWindow.setFramerateLimit(fpsLimit);
}

float GameEngine::getFps() const { 
  return this->fps;
};

float GameEngine::getTps() const { 
  return this->currentTPS; 
};

void GameEngine::setTps(float newTps) {
  this->tps = newTps;
};

const std::chrono::milliseconds GameEngine::getFrameLag() const {
  return std::chrono::milliseconds(this->frameLag.asMilliseconds());
}

const sf::Vector2u GameEngine::getWindowSize() const {
  return gameWindow.getSize();
}

sf::RenderWindow& GameEngine::getWindow() {
  return gameWindow;
}

const GlInfo GameEngine::getGlInfo() {
  return GlInfo{
    reinterpret_cast<const char *>(glGetString(GL_RENDERER)),
    reinterpret_cast<const char *>(glGetString(GL_VENDOR)),
    reinterpret_cast<const char *>(glGetString(GL_VERSION)),
    reinterpret_cast<const char *>(glGetString(GL_SHADING_LANGUAGE_VERSION))
  };
}

const std::vector<sf::VideoMode>& GameEngine::getFullscreenVideoModes() {
  return sf::VideoMode::getFullscreenModes();
}

const sf::VideoMode GameEngine::getWindowedVideoMode() {
  return sf::VideoMode::getDesktopMode();
}
