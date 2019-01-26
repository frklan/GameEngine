#pragma once
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

#include "../../../GameEngine/Scene.h"
#include "../../../GameEngine/ResourceManager.h"
#include "../../../GameEngine/GameObject.h"



class Gui : public GameObject {
  public:
    Gui() = delete;
    Gui(const Scene& scene, uint8_t zOrder);
    
    virtual ~Gui();
    
    virtual void update(const sf::Time gameTime) override;
    virtual void render(sf::RenderTarget& target, sf::Time gameTime) override;
    virtual void handleEvent(const sf::Event& e) override;
    

  private:
    
};