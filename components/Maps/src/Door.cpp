//
// Created by ricka on 2024-03-12.
//

#include "../include/Door.h"

Door::Door(bool start, bool exit){
    this->start = start;
    this->exit = exit;
}

bool Door::getStart() const {
    return start;
}

bool Door::getExit() const {
    return exit;
}

bool Door::getIsOpen() const {
    return isOpen;
}

bool Door::getIsLocked() const {
    return isLocked;
}
