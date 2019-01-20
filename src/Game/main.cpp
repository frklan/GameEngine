#include <iostream>

#include "../GameEngine/GameEngine.h"
#include "Scenes/IntroScene.h"
#include "Scenes/GameScene.h"

int main() {
  std::clog << "<-- GameEngine - engine + demo game #1 -->\n";

  GameEngine ge;

  ge.addScene("intro", std::make_unique<Intro>(ge));
  ge.run();

 return 0;
}