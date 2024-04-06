#ifndef A3_MOVABLE_H
#define A3_MOVABLE_H

#include "Placeable.h"

class Movable
{
public:
    Movable() {};
    Movable(const Movable&) = default;
    Movable(Movable&&) = default;
    Movable& operator=(const Movable&) = default;
    Movable& operator=(Movable&&) = delete;
    virtual ~Movable() = default;
};

#endif
