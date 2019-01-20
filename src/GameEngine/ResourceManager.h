#pragma once

#include <exception>
#include <string>
#include <unordered_map>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

template<typename T>
class ResourceManager {
  public:
    const T& get(const std::string& path);
    const T& loadResource(const std::string& path);

  private:
    std::unordered_map<std::string, T> resources;
};

template<typename T>
const T& ResourceManager<T>::get(const std::string& path) {
  if(resources.find(path) != resources.end()) {
    return resources.at(path);
  } else {
    return loadResource(path);
  }
}

template<typename T>
const T& ResourceManager<T>::loadResource(const std::string& path) {
  if(resources.find(path) != resources.end() ){
    return resources.at(path);
  }

  T res;
  if( (res.loadFromFile(path)) < 0){
    throw std::runtime_error("could not load resource: " + path);
  }
  resources.insert({path, res});
  return resources.at(path);
}