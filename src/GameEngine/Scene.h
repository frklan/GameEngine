#pragma once

#include <iostream>
#include <map>

#include "GameEngine.h"
#include "GameObject.h"

class GameEngine;
class GameObject;

class Scene {
  public:
    Scene() = delete;
    Scene(GameEngine&);
    virtual ~Scene();
    
    virtual void handleEvent(sf::Event& e);
    virtual void update(sf::Time gameTime);
    virtual void render(sf::RenderTarget& w, sf::Time gameTime);
    virtual void onActivate() {};
    virtual void onDeactivate() {};

    void addGameObject(std::unique_ptr<GameObject> gameObject);
    //const GameObject* Scene::getGameObject(std::string name) const
    template<typename T> std::vector<T*> getGameObjects() const;
    void deleteGameObject(std::string name);
    
    const int getNumOfEntities() const;
    GameEngine& getGameEngine() const;

  protected:
    GameEngine& gameEngine;

  private:
    std::multimap<uint8_t, std::unique_ptr<GameObject>> gameObjects;
};

template<typename T> 
std::vector<T*> Scene::getGameObjects() const {
  std::vector<T*> objects;
  for(auto g = gameObjects.begin(); g != gameObjects.end(); g++) {
    T* t = dynamic_cast<T*>(g->second.get());
    if(t != nullptr) {
      objects.push_back(t);
    }
  }
  return objects;
}
