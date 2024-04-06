#ifndef A3_WALL_H
#define A3_WALL_H

#include "Movable.h"

/**
 * @class Wall
 * @brief Represents a wall object that inherits from the Movable class.
 * 
 * The Wall class represents a wall object in a game. It inherits from the Movable class
 * and provides additional functionality specific to walls.
 */
class Wall : public Movable {
public:
    /**
     * @brief Constructs a Wall object using a Movable object.
     * @param movable The Movable object to initialize the Wall with.
     */
    explicit Wall(const Movable& movable) : Movable(movable) {}

    /**
     * @brief Default constructor for the Wall class.
     */
    Wall() = default;

    /**
     * @brief Default destructor for the Wall class.
     */
    ~Wall() override = default;

    /**
     * @brief The name of the texture used for rendering the wall.
     */
    string textureName = "wall_mid";
};

#endif //A3_WALL_H
