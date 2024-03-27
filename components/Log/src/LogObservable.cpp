/**
 * @file LogObservable.cpp
 * @author Tymofiy Kovalenko
 * @date 21-Mar-2024
 * @brief
 */


#include <iostream>
#include <string>
#include "../include/LogObservable.h"

LogObservable::LogObservable() {
    logObservers = new std::list<LogObserver*>;
}
LogObservable::~LogObservable() = default;


void LogObservable::notify(const std::string &message, string module) const {
    if (logObservers == nullptr) {
        cout << "No observers attached" << endl;
        return;
    }
    for (auto observer: *logObservers) {
        if (module == "Map") {
            if (!observer->enabledModules.map) {
                continue;
            }
        } else if (module == "Character") {
            if (!observer->enabledModules.character) {
                continue;
            }
        } else if (module == "System") {
            if (!observer->enabledModules.system) {
                continue;
            }
        } else if (module == "Dice") {
            if (!observer->enabledModules.dice) {
                continue;
            }
        }

        observer->update(message);
    }
}

void LogObservable::attach(LogObserver *observer) {
    logObservers->push_back(observer);
}

void LogObservable::detach(LogObserver *observer) {
    logObservers->remove(observer);
}