#pragma once

#include <Event.h>

namespace game {
  struct GamePauseEvent : public eventbus::Event {
      
  };

  struct GuiEvent : public eventbus::Event {
  
  };

  struct GameClearEvent : public eventbus::Event {
  
  };

  struct GameResetEvent : public eventbus::Event {
  
  };

  struct QuitEvent : public eventbus::Event {
  
  };

  struct WindowResizeEvent : public eventbus::Event {
    WindowResizeEvent(sf::Vector2u size) : windowSize(size) {}
    sf::Vector2u windowSize;
  };
}
