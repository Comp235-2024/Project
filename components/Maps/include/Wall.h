#ifndef A3_WALL_H
#define A3_WALL_H

#include "Movable.h"

class Wall : public Movable {
public:
    explicit Wall(const Movable& movable) : Movable(movable) {}
    Wall() = default;
    ~Wall() override = default;
    //Wall logic
    string textureName = "wall_mid";
};


#endif //A3_WALL_H
