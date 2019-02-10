#pragma once
#include <iostream>
#include <vector>
#include <set>

#include "Observer.h"
#include "Event.h"

template <typename T>
class Observable {
  public:
    Observable() = default;
    virtual ~Observable() = default;

    virtual void registerObserver(Observer<T>& observer);
    virtual void unregisterObserver(Observer<T>& observer);

    virtual void notify(T e);

  private:
    std::vector<Observer<T>*> observers;
};

template<typename T>
void Observable<T>::registerObserver(Observer<T>& observer) {
  observers.push_back(&observer);
}

template<typename T>
void Observable<T>::unregisterObserver(Observer<T>& removeMe) {
  auto r = std::find(observers.begin(), observers.end(), &removeMe);
  if(r != observers.end()) {
  observers.erase(r);
  }
}

template<typename T>
void Observable<T>::notify(T e) {
  for(auto o : observers) {
    o->onNotify(e);
  }
}