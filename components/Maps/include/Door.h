//
// Created by ricka on 2024-03-12.
//

#ifndef A3_DOOR_H
#define A3_DOOR_H

#include "../../Items/include/Movable.h"

class Door : public Movable {
public:
    explicit Door(const Movable& movable) : Movable(movable) {}
    Door(bool start, bool exit);
    Door() = default;
    ~Door() override = default;
    //Door logic

    bool getStart() const;
    bool getExit() const;
    bool getIsOpen() const;
    bool getIsLocked() const;

private:
    bool start;
    bool exit;
    bool isOpen;
    bool isLocked;
    //
};

#endif //A3_DOOR_H
