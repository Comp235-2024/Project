//
// Created by ricka on 2024-03-12.
//

#ifndef A3_DOOR_H
#define A3_DOOR_H

#include "../../Items/include/Movable.h"
#include <string>
using namespace std;
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
    string textureName = "doors_leaf_closed";

private:
    bool start;
    bool exit;
    bool isOpen;
    bool isLocked;
    //
};

#endif //A3_DOOR_H
