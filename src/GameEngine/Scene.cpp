#include "Scene.h"
#include "GameEngine.h"

Scene::Scene(GameEngine& engine) : gameEngine(engine){ 
  std::clog << "Scene created\n"; 
}

Scene::~Scene() { 
  std::clog << "Scene destroyed\n"; 
}

void Scene::addGameObject(std::unique_ptr<GameObject> gameObject) {
  gameObjects.insert({gameObject->getZOrder(), std::move(gameObject)});
}

// const GameObject* Scene::getGameObject(std::string name) const {
//   throw std::runtime_error("Scene::getGameObject is not implemented!");
//   return nullptr;
// }

void Scene::deleteGameObject(std::string name) {
  throw std::runtime_error("Scene::deleteGameObject is not implemented!");
}

void Scene::update(sf::Time gameTime) { 
  for(auto c = gameObjects.rbegin(); c != gameObjects.rend(); c++) {
    c->second->update(gameTime);
  }
};

void Scene::handleEvent(sf::Event& e) {
  for(auto c = gameObjects.rbegin(); c != gameObjects.rend(); c++) {
    c->second->handleEvent(e);
  }
}

void Scene::render(sf::RenderTarget& rt, sf::Time gameTime) {
  for(auto go = gameObjects.rbegin(); go != gameObjects.rend(); go++) {
    go->second->render(rt, gameTime);
  }
}

GameEngine& Scene::getGameEngine() const  {
  return gameEngine;
}

const int Scene::getNumOfEntities() const {
  return gameObjects.size();
}