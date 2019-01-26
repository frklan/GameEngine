#pragma once
#include <iostream>
#include <exception>
#include <vector>
#include <unordered_map>
#include <stdint.h>
#include <chrono>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/OpenGL.hpp>

#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"

class Scene;

struct GlInfo {
  std::string glRenderer;
  std::string glVendor;
  std::string glVersion;
  std::string glShaderVersion;
};

class GameEngine final {
  public:
    GameEngine();
    
    void addScene(std::string name, std::unique_ptr<Scene> scene);
    void switchScene(std::string name);
    void unloadScene(std::string name);
    
    int run();

    const sf::Font& getFontResource(const std::string& name);
    const sf::Texture& getTextureResource(const std::string& name);
    
    void setVerticalSyncEnabled(bool enabled = true);
    void setFramerateLimit(std::uint8_t fpsLimit = 60);

    const float getFps() const;
    const float getTps() const;
    const void setTps(float tps);
    const std::chrono::milliseconds getFrameLag() const;

    const sf::Vector2u getWindowSize() const;
    sf::RenderWindow& getWindow();

    const GlInfo getGlInfo();
    const std::vector<sf::VideoMode>& getFullscreenVideoModes();
    const sf::VideoMode getWindowedVideoMode();

  private:
    std::uint8_t tps  = 30;
    //const unsigned int GAME_WIDTH = 3960;
    //const unsigned int GAME_HEIGHT = 2160;
    const unsigned int WIDTH = 1920;
    const unsigned int HEIGHT = 1080;

    sf::RenderWindow gameWindow;
    sf::View gameView;
    
    std::unordered_map <std::string, std::unique_ptr<Scene>> scenes;
    Scene* currentScene = nullptr;

    sf::Clock gameClock;
    sf::Clock fpsClock;
    float currentTPS;
    sf::Clock frameClock;
    sf::Time frameLag;
    const sf::Uint16 TPS;
    const sf::Time timePerTick;
    float fps; 

    ResourceManager<sf::Font> fontManager;
    ResourceManager<sf::Texture> textureManager;
    ResourceManager<sf::Image> imgageManager;
};