#include <iostream>
#include <vector>
#include <set>

#include "Observer.h"
#include "Observable.h"

void Observable::registerObserver(Observer& observer) {
  observers.push_back(&observer);
}

void Observable::unregisterObserver(Observer& removeMe) {
  //throw std::runtime_error("Not implemented");
  auto r = std::find(observers.begin(), observers.end(), &removeMe);
  if(r != observers.end()) {
  observers.erase(r);
  }
}

void Observable::notify(Event e) {
  for(auto o : observers) {
    o->onNotify(e);
  }
}