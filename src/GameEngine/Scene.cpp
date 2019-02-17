#include "Scene.h"
#include "GameEngine.h"

Scene::Scene(GameEngine& engine) : gameEngine(engine){ 
}

GameObject* Scene::addGameObject(std::unique_ptr<GameObject> gameObject) {
  auto i = gameObjects.insert({gameObject->getZOrder(), std::move(gameObject)});
  return i->second.get();
}

bool Scene::deleteGameObject(GameObject* removeMe) {
  //throw std::runtime_error("Scene::deleteGameObject is not implemented!");
  for(auto c = gameObjects.begin(); c != gameObjects.end(); c++) {
    if(c->second.get() == removeMe) {
      std::clog << "found! removing";
      gameObjects.erase(c);
      return true;
    }
  }

  return false;
}

void Scene::update(sf::Time gameTime) { 
  auto hasUpdated = onUpdate(gameTime);
  
  if(!hasUpdated) {
    for(auto c = gameObjects.rbegin(); c != gameObjects.rend(); c++) {
      try{
        c->second->onUpdate(gameTime);
      } catch(std::exception& e) {
        std::cerr << "Warning! exception: " << e.what() << '\n';
        continue;
      }
    }
  }
}

void Scene::event(sf::Event& e) {
  auto hasHandled = onEvent(e);
 
  if(!hasHandled) {
    for(auto c = gameObjects.rbegin(); c != gameObjects.rend(); c++) {
      try{
        c->second->onEvent(e);      
      } catch(std::exception& e) {
        std::cerr << "Warning! exception: " << e.what() << '\n';
        continue;
      }
    }
  }
}

void Scene::render(sf::RenderTarget& rt, sf::Time gameTime) {
  auto hasRendered = onRender(rt, gameTime);

  if(!hasRendered) { 
    for(auto go = gameObjects.rbegin(); go != gameObjects.rend(); go++) {
      try{
        go->second->onRender(rt, gameTime);
      } catch(std::exception& e) {
        std::cerr << "Warning! exception: " << e.what() << '\n';
        continue;
      }
    }
  }
}

GameEngine& Scene::getGameEngine() const  {
  return gameEngine;
}

const int Scene::getNumOfEntities() const {
  return gameObjects.size();
}