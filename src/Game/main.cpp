#include <iostream>

#include "../GameEngine/GameEngine.h"
#include "Scenes/introscene.h"
#include "Scenes/gamescene.h"

int main() {
  std::clog << "<-- GameEngine - engine + demo game #1 -->\n";

  GameEngine ge;

  ge.addScene("intro", std::make_unique<Intro>(ge));
  ge.run();

 return 0;
}