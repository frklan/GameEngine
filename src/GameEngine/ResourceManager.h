#pragma once

#include <exception>
#include <string>
#include <unordered_map>

#include <boost/filesystem.hpp>
#include <mach-o/dyld.h>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>

template<typename T>
struct Resource {
  std::string absolutePath;
  T data;
};

template<typename T>
class ResourceManager {
  public:
    const T& get(const std::string& path);
    const T& loadResource(const std::string& path);
    std::string getAbsoluteResourcePath(const std::string path) const;

  protected:
    std::string findResource(std::string resourceName);

  private:
    std::unordered_map<std::string, Resource<T>> resources;
};

template<typename T>
const T& ResourceManager<T>::get(const std::string& path) {
  if(resources.find(path) != resources.end()) {
    return resources.at(path).data;
  } else {
    return loadResource(path);
  }
}

template<typename T>
std::string ResourceManager<T>::getAbsoluteResourcePath(const std::string path) const {
  if(resources.find(path) != resources.end()) {
    return resources.at(path).absolutePath;
  } else {
    throw std::runtime_error("resource " + path + " not loaded");
  }
}

template<typename T>
const T& ResourceManager<T>::loadResource(const std::string& path) {
  if(resources.find(path) != resources.end() ){
    return resources.at(path).data;
  }

  T res;
  auto absolutePath = findResource(path);
  if( (res.loadFromFile(absolutePath)) < 0){
    throw std::runtime_error("could not load resource: " + path);
  }
  resources.insert({path, {absolutePath, res}});
  return resources.at(path).data;
}


template<typename T>
std::string ResourceManager<T>::findResource(std::string resourceName) {
  char pathbuff[PATH_MAX];
  uint32_t pathLen = sizeof(pathbuff);

  if(_NSGetExecutablePath(pathbuff, &pathLen) != 0) {
    throw std::runtime_error("Could not find executable directory..");
  }

  boost::filesystem::path basePath{pathbuff}; 
  boost::filesystem::path resource{resourceName};

  for(auto i = 0; i < 4; i++) {
    basePath = basePath.parent_path();
    auto testPath = basePath;
    testPath /= resource;
        
    if(boost::filesystem::exists(testPath)) {
      return testPath.string();
    }
  }

  // we did not find the resoruce, throw
  throw std::runtime_error("Resource not found");
}
