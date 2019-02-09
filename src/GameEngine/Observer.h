#pragma once
#include <iostream>

#include "Observable.h"

#include "Event.h"

class Observer {
  public:
    Observer() = default;
    virtual ~Observer() = default;

    virtual void onNotify(Event) {};
};