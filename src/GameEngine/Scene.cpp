#include "Scene.h"
#include "GameEngine.h"

Scene::Scene(GameEngine& engine) : gameEngine(engine){ 
  std::clog << "Scene created\n"; 
}

Scene::~Scene() { 
  std::clog << "Scene destroyed\n"; 
}

GameObject* Scene::addGameObject(std::unique_ptr<GameObject> gameObject) {
  auto i = gameObjects.insert({gameObject->getZOrder(), std::move(gameObject)});
  return i->second.get();
}

// const GameObject* Scene::getGameObject(std::string name) const {
//   throw std::runtime_error("Scene::getGameObject is not implemented!");
//   return nullptr;
// }

void Scene::deleteGameObject(GameObject* removeMe) {
  //throw std::runtime_error("Scene::deleteGameObject is not implemented!");
  for(auto c = gameObjects.begin(); c != gameObjects.end(); c++) {
    if(c->second.get() == removeMe) {
      std::clog << "found! removing";
      gameObjects.erase(c);
      return;
    }
  }
}

void Scene::update(sf::Time gameTime) { 
  for(auto c = gameObjects.rbegin(); c != gameObjects.rend(); c++) {
    try{
      c->second->update(gameTime);
    } catch(std::exception& e) {
      std::cerr << "Warning! exception: " << e.what() << '\n';
      continue;
    }
  }
};

void Scene::handleEvent(sf::Event& e) {
  for(auto c = gameObjects.rbegin(); c != gameObjects.rend(); c++) {
    try{
      c->second->handleEvent(e);
    } catch(std::exception& e) {
      std::cerr << "Warning! exception: " << e.what() << '\n';
      continue;
    }
  }
}

void Scene::render(sf::RenderTarget& rt, sf::Time gameTime) {
  for(auto go = gameObjects.rbegin(); go != gameObjects.rend(); go++) {
    try{
      go->second->render(rt, gameTime);
    } catch(std::exception& e) {
      std::cerr << "Warning! exception: " << e.what() << '\n';
      continue;
    }
  }
}

GameEngine& Scene::getGameEngine() const  {
  return gameEngine;
}

const int Scene::getNumOfEntities() const {
  return gameObjects.size();
}