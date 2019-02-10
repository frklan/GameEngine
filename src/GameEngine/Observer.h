#pragma once
#include <iostream>

template<typename T>
class Observer {
  public:
    Observer() = default;
    virtual ~Observer() = default;

    virtual void onNotify(T) = 0;
};