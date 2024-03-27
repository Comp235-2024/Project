#ifndef A3_MOVABLE_H
#define A3_MOVABLE_H

class Movable
{
public:
    Movable() = default;
    Movable(const Movable&) = default;
    Movable(Movable&&) = default;
    Movable& operator=(const Movable&) = default;
    Movable& operator=(Movable&&) = delete;
    virtual ~Movable() = default;
};

#endif
