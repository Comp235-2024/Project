#ifndef PROJECT_PILLAR_H
#define PROJECT_PILLAR_H

#include "../../Items/include/Movable.h"

/**
 * @class Pillar
 * @brief Represents a pillar object in the game.
 * 
 * The Pillar class is a derived class of the Movable class. It represents a pillar object that can be moved in the game.
 * It inherits the properties and methods of the Movable class and adds a textureName member variable.
 */
class Pillar : public Movable {
public:
    /**
     * @brief Constructs a Pillar object with the given Movable object.
     * @param movable The Movable object to be used for constructing the Pillar object.
     */
    explicit Pillar(const Movable& movable) : Movable(movable) {}

    /**
     * @brief Default constructor for the Pillar class.
     */
    Pillar() = default;

    /**
     * @brief Default destructor for the Pillar class.
     */
    ~Pillar() override = default;

    /**
     * @brief The name of the texture used for rendering the pillar.
     */
    string textureName = "column_wall";
};

#endif //PROJECT_PILLAR_H
