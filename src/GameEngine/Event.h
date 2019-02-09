#pragma once


class Event {
  public:
    enum EventType
    {
      GameOver,
      GamePause,
      GameStart
    };

    EventType event;
};