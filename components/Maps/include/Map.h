/**
 * @file Map.h
 * @author Tymofiy Kovalenko
 * @coauthor Ricardo Raji Chahine
 * @date 24 February 2024
 * @brief This file contains the declaration of the Map class and related structures and aliases.
 * @details
 * 1. The Rules for the map are not fully defined yet. However, the map should have a start and end cell, and the map should be valid in order to be used in the game.
 * 2. The design of the map consists of a 2D grid of cells, where each cell can contain a Movable object. The map is a 2d vector of pointers to Movable objects. It allows easy
 * movement of objects on the map and easy access to the objects on the map. Validation happens by checking if the path from the start to the end cell is valid. This is done 
 * with the Breadth First Search algorithm.
 * 3. The libraries used in this file are memory, ostream, string, strstream, and vector. Memory is used for shared pointers, ostream is used for output streams, string is used
 * for strings, strstream is used for string streams, and vector is used for vectors.
 */

#ifndef A3_MAP_H
#define A3_MAP_H

//#include "Cell.h"
#include "../../Characters/include/Character.h"
#include "../../Items/include/Item.h"
#include "../../ItemContainers/include/TreasureChest.h"
#include "../../ItemContainers/include/ItemContainer.h"

#include "../../Items/include/Movable.h"
#include "Door.h"
#include "Observable.h"
#include "Pillar.h"
#include "Position.h"
#include "Wall.h"
#include <memory>
#include <ostream>
#include <string>
#include <strstream>
#include <vector>


/**
 * @brief Alias for a shared pointer to a Movable object.
 */
using Cell = std::shared_ptr<Movable>;
/**
 * @brief Alias for a row of cells in a map.
 */
using Row = std::vector<Cell>;
/**
 * @brief Alias for a grid of rows.
 * 
 * The Grid type represents a grid of rows, where each row is a vector of cells.
 * It is used to represent the map grid.
 */
using Grid = std::vector<Row>;



/**
 * @class Map
 * @brief A class to represent a 2D grid map.
 *
 * @var Map::size_x
 * Member 'size_x' represents the width of the map.
 *
 * @var Map::size_y
 * Member 'size_y' represents the height of the map.
 *
 * @var Map::grid
 * Member 'grid' is a 2D vector representing the map grid.
 */
class Map : public Observable {
public:
    /**
     * @brief Constructs a Map object with the specified dimensions.
     * @param size_x The width of the map.
     * @param size_y The height of the map.
     */

    Map(int size_x, int size_y);


    Map& operator=(const Map& other);

    /**
     * @brief Default Constructor.
     * @param size_x The width of the map.
     * @param size_y The height of the map.
     * @param grid The grid of cells for the map.
     */
    Map();

    /**
     * @brief Copy Constructor.
     * @param other The Map object to copy.
     */
    Map(const Map& other);

    /**
     * @brief Setter for the size of the X-axis
     * @param size_x
     */
    void setSizeX(int size_x);

    /**
     * @brief Getter for the size of the X-axis
     * @return
     */
    int getSizeX() const;

    /**
     * @brief Setter for the size of the Y-axis
     * @param size_y
     */
    void setSizeY(int size_y);

    /**
     * @brief Getter for the size of the Y-axis
     * @return
     */
    int getSizeY() const;

    /**
     * @brief Setter for the grid of the map
     * @param grid
     */
    void setGrid(const Grid& grid);

    /**
     * @brief Getter for the grid of the map
     * @return
     */
    const Grid getGrid() const;

    /**
     * @brief Sets the row of cells at the specified y-coordinate.
     * @param row The row of cells to set.
     * @param y The y-coordinate of the row.
     */
    void setRow(const Row& row, int y);

    /**
     * @brief Setter for the start cell of the map
     * @param startCell
     */
    void setStartCell(const Position& startCell);

    void setStartCell(const sf::Vector2i& startCell){
        setStartCell(Position(startCell));
    }

    /**
     * @brief Getter for the start cell of the map
     * @return
     */
    Position getStartCell() const;

    /**
     * @brief Setter for the end cell of the map
     * @param endCell
     */
    void setEndCell(const Position& endCell);

    void setEndCell(const sf::Vector2i& endCell){
        setEndCell(Position(endCell));
    }

    /**
     * @brief Getter for the end cell of the map
     * @return
     */
    Position getEndCell() const;

    /**
     * @brief Getter for the name of the map
     * @return
     */
    string getName() const;

    /**
     * @brief Setter for the name of the map
     * @param name
     */
    void setName(string name);

    /**
     * @brief Gets a constant reference to the map grid.
     * @return Constant reference to the map grid.
     */
    const Grid& getMap() const;

    //TODO IMPLEMENT THIS METHOD FOR CHARACTER TO KNOW WHO IS AROUND THEM
    Position** getAroundACharacter(Character &character);

    /**
     * @brief Validates the map by checking if it meets certain criteria.
     * @return True if the map is valid, false otherwise.
     */
    bool validateMap() const;

    /**
     * @brief Places a movable object on the map at the specified position.
     * @tparam T The type of the movable object.
     * @param obj The movable object to place on the map.
     * @param Position The position at which to place the object.
     * @return True if the object was successfully placed, false otherwise.
     */
    template<typename T>
    bool place(const T &obj, const Position &pos) {
        if (checkEmpty(pos)) {
            grid[pos.y][pos.x] = make_shared<T>(std::move(obj));
            notify();
            return true;
        }
        return false;
    }

    template<typename T>
    bool place(const shared_ptr<T> &obj, const Position &pos) {
        if (checkEmpty(pos)) {
            grid[pos.y][pos.x] = obj;
            notify();
            return true;
        }
        return false;
    }

    template<typename T>
    bool place(const T& obj, const sf::Vector2i& position){
        return place(obj, Position(position));
    }

    /**
     * @brief Removes a movable object from the map at the specified position.
     * @param Position The position from which to remove the object.
     * @return True if the object was successfully removed, false otherwise.
     */
    bool remove(const Position& position);

    bool remove(const sf::Vector2i& position){
        return remove(Position(position));
    }

    /**
     * @brief Moves a movable object from one position to another on the map.
     * @param pos_start The starting position of the object.
     * @param pos_end The ending position of the object.
     * @return True if the object was successfully moved, false otherwise.
     */
    bool move(const Position& pos_start, const Position& pos_end);

    bool move(const sf::Vector2i&_pos_start, const sf::Vector2i&_pos_end){
        return move(Position(_pos_start), Position(_pos_end));
    }

    /**
     * @brief Calculates the distance between two positions on the map.
     * @param pos_start The starting position.
     * @param pos_end The ending position.
     * @return The distance between the two positions.
     */
    int getDistance(const Position& pos_start, const Position& pos_end) const;

    int getDistance(const sf::Vector2i& pos_start, const sf::Vector2i& pos_end) const{
        return getDistance(Position(pos_start), Position(pos_end));
    }

    /**
     * @brief Checks if a position on the map is empty.
     * @param pos The position to check.
     * @return True if the position is empty, false otherwise.
     */
    bool checkEmpty(const Position& pos) const;

    /**
     * @brief Finds a path from the start position to the end position on the map.
     * @param start The starting position.
     * @param end The ending position.
     * @return A vector of positions representing the path from start to end.
     */
    std::vector<Position> findPath(Position start, Position end) const;

    /**
     * @brief Less than comparison operator for Map class.
     * @param rhs The Map object to compare with.
     * @return True if this map is less than the rhs map, false otherwise.
     */
    bool operator<(const Map& rhs) const;

    /**
     * @brief Greater than comparison operator for Map class.
     * @param rhs The Map object to compare with.
     * @return True if this map is greater than the rhs map, false otherwise.
     */
    bool operator>(const Map& rhs) const;

    /**
     * @brief Less than or equal to comparison operator for Map class.
     * @param rhs The Map object to compare with.
     * @return True if this map is less than or equal to the rhs map, false otherwise.
     */
    bool operator<=(const Map& rhs) const;

    /**
     * @brief Greater than or equal to comparison operator for Map class.
     * @param rhs The Map object to compare with.
     * @return True if this map is greater than or equal to the rhs map, false otherwise.
     */
    bool operator>=(const Map& rhs) const;

    /**
     * @brief Equality comparison operator for Map class.
     * @param rhs The Map object to compare with.
     * @return True if this map is equal to the rhs map, false otherwise.
     */
    bool operator==(const Map& rhs) const;

    /**
     * @brief Inequality comparison operator for Map class.
     * @param rhs The Map object to compare with.
     * @return True if this map is not equal to the rhs map, false otherwise.
     */
    bool operator!=(const Map& rhs) const;

    /**
     * @brief Overloaded stream insertion operator for Map class.
     * @param os The output stream.
     * @param map The Map object to insert into the stream.
     * @return Reference to the output stream.
     */
    friend std::ostream& operator<<(std::ostream& os, const Map& map);

    /**
     * @brief Gets a random cell position on the map.
     * @return A random cell position.
     */
    Position getRandomCell() const;

    ostream& displayRevMap(ostream& os) const;

    static bool mapBuilderTest();

    template<typename T>
    bool specialPlace(const T &obj, const Position &pos) {
        if (checkEmpty(pos)) {
            grid[pos.y][pos.x] = make_shared<T>(std::move(obj));
            return true;
        }
        return false;
    }

    bool specialMove(const Position &pos_start, const Position &pos_end);

    bool isInBounds(const sf::Vector2i &pos) const;

private:
    /**
     * @brief The name of the map.
     */
    string name;

    //Removed const
    /**
     * @brief The width of the map.
     */
    int size_x;

    //Removed const
    /**
     * @brief The height of the map.
     */
    int size_y;

    /**
     * @brief The start cell of the map.
     * @brief The end cell of the map.
     */
    Position startCell{}, endCell{};

    //Made grid a private member
    /**
     * @brief The grid of cells for the map.
     */
    Grid grid;

    /**
     * @brief This function is used to test the functionality of the Map class.
     *
     * @return true if the test passes, false otherwise.
     */
    static bool map_test();



};

/**
 * @brief MapBuilder abstract class to implement Builder pattern for Map class.
 */
class MapBuilder {
public:
    /**
     * @brief Builds the grid of the map.
     * @return True if the grid was successfully built, false otherwise.
     */
    virtual bool buildGrid() = 0;

    //TODO virtual void placeCharacter()=0;
    };

/**
 * @brief DefaultMapBuilder class acts as Concrete Map Builder to implement the MapBuilder interface.

 */
class DefaultMapBuilder : public MapBuilder {
    private:
    /**
     * @brief The map to build.
     */
    Map map;

    public:
        /**
         * @brief Builds the grid of the map.
         * @return True if the grid was successfully built, false otherwise.
         */
        bool buildGrid() override;

        /**
         * @brief Gets the map that was built.
         * @return The map that was built.
         */
        Map getMap();
};

/**
 * @brief SavedMapBuilder class acts as Concrete Map Builder to implement the MapBuilder interface.
 */
class SavedMapBuilderFromStringRepresentation : public MapBuilder {
    private:
    /**
     * @brief The map to build.
     */
    Map map;

    public:

        /**
         * @Asks the user to choose a map from the list of saved maps.
         * @return
         */
        static string chooseMap();

        /**
         * @brief Builds the grid of the map.
         * @return True if the grid was successfully built, false otherwise.
         */
        bool buildGrid() override;

        /**
         * @brief Reads a string representation of a Row and parses it into a Row object along with its position.
         * @param line the string representation of the row.
         * @param map the map to build
         * @param y the y-coordinate of the row.
         * @return The parsed row.
         */
        Row parseGrid(const string& line, Map& map, int y);

        /**
         * @brief Gets the map that was built.
         * @return The map that was built.
         */
        Map getMap();


};

/**
 * @brief MapDirector class to use the implemented Builder Pattern to build specific Maps.
 */
class MapDirector{
    public:
    /**
     * @brief Constructs a map using the SavedMapBuilderFromStringRepresentation.
     * @param builder The MapBuilder to use.
     */
    bool constructSavedMap(MapBuilder& builder);

    /**
     * @brief Constructs a map using the DefaultMapBuilder.
     * @param builder The MapBuilder to use.
     */
    bool constructDefaultMap(MapBuilder& builder);

};



#endif
