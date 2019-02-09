#pragma once
#include <iostream>
#include <vector>
#include <set>

#include "Observer.h"
#include "Event.h"

class Observer;

class Observable {
  public:
    Observable() = default;
    virtual ~Observable() = default;

    virtual void registerObserver(Observer& observer);
    virtual void unregisterObserver(Observer& observer);

    virtual void notify(Event e);

  private:
    std::vector<Observer*> observers;

};