#include <iostream>

#include <GameEngine.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <Scene.h>

#include "Scenes/Intro/introscene.h"
#include "Scenes/Test/testscene.h"

int main() {
  std::clog << "<-- GameEngine - engine + demo game #1 -->\n";

  GameEngine ge;

  //ge.addScene("intro", std::make_unique<Intro>(ge));
  ge.addScene("test", std::make_unique<Test>(ge));
  ge.run();

 return 0;
}