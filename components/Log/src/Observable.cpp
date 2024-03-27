/**
 * @file Observable.cpp
 * @author Tymofiy Kovalenko
 * @date 08-Mar-2024
 * @brief
 */

#include "Observable.h"
#include <iostream>
using namespace std;


Observable::Observable() : observers(new list<Observer*>()) {};

Observable::~Observable() {
    //TODO REMOVE THIS COMMENT
    //delete observers;
}

void Observable::notify() const {
    if (observers == nullptr) {
        cout << "No observers attached" << endl;
        return;
    }
    for (auto observer: *observers) {
        observer->update();
    }
}

void Observable::attach(Observer *observer) { 
    observers->push_back(observer); 
}
void Observable::detach(Observer *observer) {
    observers->remove(observer); 
}
