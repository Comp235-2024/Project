//
// Created by ricka on 2024-03-18.
//

#ifndef A3_POSITION_H
#define A3_POSITION_H
#include <iostream>

/**
 * @struct Position
 * @brief A structure to represent a position in a 2D grid.
 *
 * @var Position::x
 * Member 'x' represents the x-coordinate of the position.
 *
 * @var Position::y
 * Member 'y' represents the y-coordinate of the position.
 */
struct Position {
    int x{}, y{};

    bool checkValidity(int max_x, int max_y) const;
    Position(int x, int y);
    Position();
    struct Position& operator=(const Position& other);
    bool operator==(const Position& other) const;
    bool operator!=(const Position& other) const;
    bool operator<(const Position& rhs) const;
    bool operator>(const Position& rhs) const;
    bool operator<=(const Position& rhs) const;
    bool operator>=(const Position& rhs) const;
    friend std::ostream& operator<<(std::ostream& os, const Position& position);
};

#endif//A3_POSITION_H
