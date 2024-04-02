#ifndef PROJECT_PILLAR_H
#define PROJECT_PILLAR_H

#include "../../Items/include/Movable.h"

class Pillar : public Movable {
public:
    explicit Pillar(const Movable& movable) : Movable(movable) {}
    Pillar() = default;
    ~Pillar() override = default;
};


#endif //PROJECT_PILLAR_H
