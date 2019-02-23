#pragma once

#include <iostream>
#include <map>

#include <EventBus.h>

#include "GameEngine.h"
#include "GameObject.h"

class GameEngine;
class GameObject;

class Scene {
  public:
    Scene() = delete;
    Scene(GameEngine&);
    virtual ~Scene() = default;
    
    virtual void event(sf::Event& e) final;
    virtual void update(sf::Time gameTime) final;
    virtual void render(sf::RenderTarget& w, sf::Time gameTime) final;
    
    virtual bool onActivate() { return false; };
    virtual bool onDeactivate() { return false; };
    virtual bool onEvent(sf::Event& e) { return false; };
    virtual bool onRender(sf::RenderTarget& w, sf::Time gameTime) { return false; };
    virtual bool onUpdate(sf::Time gameTime) { return false; };
    

    GameObject* addGameObject(std::unique_ptr<GameObject> gameObject);
    template<typename T> std::vector<T*> getGameObjects() const;
    bool deleteGameObject(GameObject*);
    
    const int getNumOfEntities() const;
    GameEngine& getGameEngine() const;

    eventbus::EventBus& getEventBus() { return eventbus; };

  protected:
    GameEngine& gameEngine;
    std::multimap<uint8_t, std::unique_ptr<GameObject>> gameObjects;

  private:
    eventbus::EventBus eventbus;

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
