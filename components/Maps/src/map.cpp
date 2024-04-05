
/**
 * @file map.cpp
 * @brief Implementation file for the Map class.
 */

#include "../include/Map.h"
#include "Pillar.h"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <sstream>
#include <vector>

using namespace std;
namespace fs = std::filesystem;


// NOTE maybe add some sort of random wall generation
Map::Map(){
    this->startCell={-1,-1};
    this->endCell={-1,-1};
    this->size_x=0;
    this->size_y=0;
}
/**
 * @brief Constructs a new Map object.
 *
 * @param size_x The width of the map.
 * @param size_y The height of the map.
 */
Map::Map(int size_x, int size_y)
    : size_x(size_x),
      size_y(size_y),
      grid(size_y, Row(size_x, nullptr)) {
    startCell = getRandomCell();


    do {
        endCell = getRandomCell();
    } while (startCell == endCell);
}

/**
 * @brief Copy constructor for the Map class.
 *
 * @param other The Map object to be copied.
 */
Map::Map(const Map &other) = default;

Map& Map::operator=(const Map& other) {
    if (this != &other) { // Self-assignment check
        this->size_x = other.size_x;
        this->size_y = other.size_y;

        // Assuming grid is a vector of vector of shared_ptr<Movable>
        // Deep copy of the grid
        this->grid = Grid(other.size_y, Row(other.size_x));
        for (int y = 0; y < other.size_y; ++y) {
            for (int x = 0; x < other.size_x; ++x) {
                if (other.grid[y][x] != nullptr) {
                    // This assumes Movable has a clone function or similar
                    // If Movable objects don't have polymorphic cloning,
                    // you might need a different approach
                    this->grid[y][x] = std::make_shared<Movable>(*other.grid[y][x]);
                } else {
                    this->grid[y][x] = nullptr;
                }
            }
        }

        this->startCell = other.startCell;
        this->endCell = other.endCell;

        // Make sure to also copy any other necessary members not listed here
    }
    return *this;
}





/**
 * @brief Returns the map grid.
 *
 * @return A constant reference to the map grid.
 */
const Grid &Map::getMap() const { return grid; }

/**
 * @bried Setter for the name of the map
 * @param name
 */
void Map::setName(string name){this->name=name;}

/**
 * @brief Getter for the name of the map
 * @return string
 */
string Map::getName() const{return this->name;}

/**
 * @brief Setter for the size of the X-coordinate of the map
 * @param size_x
 */
void Map::setSizeX(int size_x) { this->size_x = size_x; }

/**
 * @brief Getter for the size of the X-coordinate of the map
 * @return int
 */
int Map::getSizeX() const { return size_x; }

/**
 * @brief Setter for the size of the Y-coordinate of the map
 * @param size_y
 */
void Map::setSizeY(int size_y) { this->size_y = size_y; }

/**
 * @brief Getter for the size of the Y-coordinate of the map
 * @return int
 */
int Map::getSizeY() const { return size_y; }

/**
 * @brief Setter for the grid of the map
 * @param grid
 */
void Map::setGrid(const Grid& grid) { this->grid = grid; }

/**
 * @brief Setter for the start cell of the map
 * @param startCell
 */
void Map::setStartCell(const Position& startCell) { this->startCell = startCell; }

/**
 * @brief Setter for the end cell of the map
 * @param endCell
 */
void Map::setEndCell(const Position& endCell) { this->endCell = endCell; }

/**
 * @brief Getter for the grid of the map
 * @return Grid
 */
const Grid Map::getGrid() const { return grid; }

/**
 * @brief Getter for the start cell of the map
 * @return Position
 */
Position Map::getStartCell() const { return startCell; }

/**
 * @brief Getter for the end cell of the map
 * @return Position
 */
Position Map::getEndCell() const { return endCell; }


/**
 * @brief Validates the map by checking if there is a path from the start cell
 * to the end cell.
 *
 * @return true if there is a path from the start cell to the end cell, false
 * otherwise.
 */
bool Map::validateMap() const {
    if (!findPath(startCell, endCell).empty()) {
        cout << "Map is valid" << endl;
        return true;
    } else {
        cout << "Map is invalid" << endl;
        return false;
    }
}

/**
 * @brief Finds a path from a start position to an end position.
 *
 * @param start The start position.
 * @param end The end position.
 * @return A vector of positions representing the path from the start position
 * to the end position.
 */
vector<Position> Map::findPath(Position start, Position end) const {
    if (!start.checkValidity(size_x, size_y) ||
        !end.checkValidity(size_x, size_y)) {
        return {};
    }

    vector<Position> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    queue<Position> queue;
    map<Position, Position> cameFrom;
    vector<Position> path;

    queue.push(start);
    cameFrom[start] = start;

    while (!queue.empty()) {
        Position current = queue.front();
        queue.pop();

        if (current == end) {
            // reconstruct the path
            for (Position pos = end; pos != start; pos = cameFrom[pos]) {
                path.push_back(pos);
            }
            path.push_back(start);
            std::reverse(path.begin(), path.end());
            return path;
        }

        for (auto &dir : directions) {
            Position newpos = {current.x + dir.x, current.y + dir.y};

            if (newpos.checkValidity(size_x, size_y) && cameFrom.count(newpos) == 0) {
                auto cell = grid[newpos.y][newpos.x];
                auto entry_exit = std::dynamic_pointer_cast<Door>(cell); // Attempt to cast cell to Door

                if (!cell || entry_exit) { // Check if the cell is nullptr or if the cast to Door is successful
                    queue.push(newpos);
                    cameFrom[newpos] = current;
                }
            }
        }
    }

    // No path found
    return path;
}


/**
 * @brief Removes a movable object from the map at the specified position.
 * @param Position The position from which to remove the object.
 * @return True if the object was successfully removed, false otherwise.
 */
bool Map::remove(const Position &pos) {
    if (!checkEmpty(pos)) {
        grid[pos.y][pos.x] = nullptr;
        notify();
        return true;
    }
    return false;
}

/**
 * @brief Generates a random Position within the map boundaries.
 *
 * @return A random Position object.
 */
Position Map::getRandomCell() const {
    random_device rd;
    mt19937 eng(rd());
    uniform_int_distribution<> randomX(0, size_x - 1);
    uniform_int_distribution<> randomY(0, size_y - 1);
    return Position{randomX(eng), randomY(eng)};
}

/**
 * Moves an object from the starting position to the ending position on the map.
 * Validates the move before performing it.
 *
 * @param pos_start The starting position of the object.
 * @param pos_end The ending position of the object.
 * @return True if the move is successful, false otherwise.
 */
bool Map::move(const Position &pos_start, const Position &pos_end) {
    // NOTE this needs to happen after the move is deemed valid, aka check if
    // distance not to big
    // TODO add some sort of logging in the future
    // TODO add path tracing on move

    if (!pos_start.checkValidity(size_x, size_y) ||
        !pos_end.checkValidity(size_x, size_y)) {
        return false;
    }

    if (checkEmpty(pos_start)) {
        return false;
    }

    if (checkEmpty(pos_end)) {
        grid[pos_end.y][pos_end.x] = std::move(grid[pos_start.y][pos_start.x]);
        grid[pos_start.y][pos_start.x] = nullptr;// clear the initial Position
        notify();
        return true;
    }
    return false;
}

bool Map::specialMove(const Position &pos_start, const Position &pos_end) {
    // NOTE this needs to happen after the move is deemed valid, aka check if
    // distance not to big
    // TODO add some sort of logging in the future

    if (!pos_start.checkValidity(size_x, size_y) ||
        !pos_end.checkValidity(size_x, size_y)) {
        return false;
    }

    if (checkEmpty(pos_start)) {
        return false;
    }

    if (checkEmpty(pos_end)) {
        grid[pos_end.y][pos_end.x] = std::move(grid[pos_start.y][pos_start.x]);
        grid[pos_start.y][pos_start.x] = nullptr;// clear the initial Position
        return true;
    }
    return false;
}

/**
 * Calculates the distance between two positions on the map.
 *
 * @param pos_start The starting position.
 * @param pos_end The ending position.
 * @return The distance between the two positions.
 */
int Map::getDistance(const Position &pos_start, const Position &pos_end) const {
    return int(findPath(startCell, endCell).size());
}

/**
 * @brief Checks if a given position on the map is empty.
 *
 * @param pos The position to check.
 * @return True if the position is empty, false otherwise.
 */
bool Map::checkEmpty(const Position &pos) const {
    return (grid[pos.y][pos.x] == nullptr || dynamic_pointer_cast<Movable>(grid[pos.y][pos.x])==nullptr); ;
}

#pragma region Map
bool Map::operator<(const Map &rhs) const {
    if (size_x < rhs.size_x) return true;
    if (rhs.size_x < size_x) return false;
    if (size_y < rhs.size_y) return true;
    if (rhs.size_y < size_y) return false;
    if (grid < rhs.grid) return true;
    if (rhs.grid < grid) return false;
    if (startCell < rhs.startCell) return true;
    if (rhs.startCell < startCell) return false;
    return endCell < rhs.endCell;
}
bool Map::operator>(const Map &rhs) const { return rhs < *this; }
bool Map::operator<=(const Map &rhs) const { return !(rhs < *this); }
bool Map::operator>=(const Map &rhs) const { return !(*this < rhs); }
bool Map::operator==(const Map &rhs) const {
    return size_x == rhs.size_x && size_y == rhs.size_y && grid == rhs.grid &&
           startCell == rhs.startCell && endCell == rhs.endCell;
}
bool Map::operator!=(const Map &rhs) const { return !(rhs == *this); }

/**
 * Overloaded insertion operator for output stream to print the Map object.
 * If the cell is empty, it is represented by a dash (-). If the cell contains a
 * wall, it is represented by an X. If the cell contains a player, it is
 * represented by an O.
 * '@' is used to represent the path during testing.
 *
 * @param os The output stream object.
 * @param map The Map object to be printed.
 * @return The modified output stream object.
 */
ostream &operator<<(ostream &os, const Map &map) {
    string map_str;
    map_str += string(map.size_x * 2 - 1, '-') + "\n";
    for (auto &row: map.grid) {
        for (auto &cell: row) {
            if (cell == nullptr) {
                map_str += "- ";
            } else if (Wall* wall = dynamic_cast<Wall*>(cell.get())) {
                map_str += "X ";
            } else if (auto* player = dynamic_cast<Character*>(cell.get())) {
                map_str += "O ";

            }else if (shared_ptr<Door> entry_exit =
                    dynamic_pointer_cast<Door>(cell)) {
                if(entry_exit->getStart()){
                    map_str += "S ";
                }
                else if(entry_exit->getExit()){
                    map_str += "E ";
                }
            }else {
                    map_str += "@ "; // This is done to be able to represent the
                    // path during testing
                }

        }
        map_str += "\n";
    }
    map_str += string(map.size_x * 2 - 1, '-') + "\n";

    os << string(map.size_x * 3 - 1, '-') + "\n"
       << "\n"
       << map_str << "\n"
       << "size_x: " << map.size_x << "\n"
       << "size_y: " << map.size_y << "\n"
       << "startCell: " << map.startCell << "\n"
       << "endCell: " << map.endCell << "\n"
       << string(map.size_x * 3 - 1, '-') + "\n";
    return os;
}

#pragma endregion

/**
 * @brief Checks if the position is valid within the given boundaries.
 *
 * @param max_x The maximum x-coordinate.
 * @param max_y The maximum y-coordinate.
 * @return true if the position is valid, false otherwise.
 */
bool Position::checkValidity(int max_x, int max_y) const {
    return x >= 0 && x < max_x && y >= 0 && y < max_y;
}

#pragma region Position
Position &Position::operator=(const Position &other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
    }
    return *this;
}

/**
 * @brief Constructs a new Position object.
 * @param x
 * @param y
 */
Position::Position(int x, int y) : x(x), y(y) {}

/**
 * @brief Default constructor for the Position class.
 */
Position::Position() = default;


bool Position::operator==(const Position& other) const {
    return x == other.x && y == other.y;
}

bool Position::operator!=(const Position &other) const {
    return !(*this == other);
}

bool Position::operator<(const Position &rhs) const {
    if (x < rhs.x) return true;
    if (rhs.x < x) return false;
    return y < rhs.y;
}
bool Position::operator>(const Position &rhs) const { return rhs < *this; }
bool Position::operator<=(const Position &rhs) const { return !(rhs < *this); }
bool Position::operator>=(const Position &rhs) const { return !(*this < rhs); }
ostream &operator<<(ostream &os, const Position &position) {
    os << "x: " << position.x << " y: " << position.y;
    return os;
}
#pragma endregion


bool Map::map_test() {
    // Test Case 1: Path exists
    cout << "Test Case 1: Path exists" << endl;

    Map map(10, 10);

    Wall wall;
    map.place(wall, Position{1, 1});
    map.place(wall, Position{5, 5});
    Position start{0, 0};
    Position end{2, 2};
    vector<Position> path = map.findPath(start, end);
    assert(path.size() == 5);
    assert(path[0] == start);
    assert(path[1] == Position(1, 0));
    assert(path[2] == Position(2, 0));
    assert(path[3] == Position(2, 1));
    assert(path[4] == end);

    // Test Case 2: No path exists
    cout << "Test Case 2: No path exists" << endl;
    end = Position{9, 9};
    for (int j = 0; j < 10; j++) {
        map.place(wall, Position{j, 5});
    }
    path = map.findPath(start, end);
    assert(path.empty());

    // Test Case 3: Start and end positions are the same
    cout << "Test Case 3: Start and end positions are the same" << endl;
    start = Position{0, 0};
    end = Position{0, 0};
    path = map.findPath(start, end);
    assert(path.size() == 1);
    assert(path[0] == start);

    // Test Case 4: Large grid
    cout << "Test Case 4: Large grid" << endl;
    Map big_map = Map(1000, 1000);
    start = Position{0, 0};
    end = Position{999, 999};
    path = big_map.findPath(start, end);
    assert(path.size() == 1999);// Assuming each step is 1 unit

    // Test Case 5: Invalid start or end position
    cout << "Test Case 5: Invalid start or end position" << endl;
    start = Position{-1, 0};
    end = Position{2, 2};
    path = map.findPath(start, end);
    cout << "path: " << path.size() << endl;
    for (auto a: path) {
        cout << "path: " << a << endl;
    }
    assert(path.empty());

    // Test Case 6: Place random walls
    cout << "Test Case 6: Place random walls" << endl;
    Map map2 = Map(10, 10);
    cout << map2 << endl;

    for (int i = 0; i < 5; i++) {
        if (map2.place(wall, map2.getRandomCell())) {
            cout << "placed" << endl;
        } else {
            cout << "occupied" << endl;
        }
    }

    // Test Case 7: Move object
    cout << "Test Case 7: Move object" << endl;
    map2.place(wall, Position{1, 1});
    cout << map2 << endl;
    cout << map2.validateMap() << endl;
    cout << "________________________________________________________" << endl;

    map2.move(Position{1, 1}, Position{1, 0});
    cout << map2 << endl;
    cout << map2.validateMap() << endl;
    cout << "________________________________________________________" << endl;

    // Test Case 8: Place wall of length 8
    cout << "Test Case 8: Place wall of length 8" << endl;
    for (int j = 0; j < 8; j++) {
        map2.place(wall, Position{j, 5});
    }


    // Test Case 9: Find path
    cout << "Test Case 9: Find path" << endl;
    map2.place(wall, Position{2, 8});
    cout << map2 << endl;

    for (auto a: map2.findPath(Position{0, 8}, Position{0, 2})) {
        cout << "path: " << a << endl;
        Wall path2;
        map2.place(path2, a);
    }
    cout << map2 << endl;

    return true;
}


/**
 * @brief List the available maps to the user and prompt them to choose one.
 * @return
 */
string SavedMapBuilderFromStringRepresentation::chooseMap() {


    string path="../../tests/SavedGrids";
    int user_choice;
    int file_index=0;
    string file_path;

    vector<string> files;

    if(fs::exists(path)){
        int i=0;
        cout<<"Please choose which map you would like to build by entering its number: "<<endl;
        for(const auto& entry: fs::directory_iterator(path)){
            files.push_back(entry.path().string());
            cout<<++i<<") "<<entry.path().filename()<<endl;
        }

        cout<<"\nYour choice:";
        cin>>user_choice;

        while(user_choice<1 || user_choice>i || cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout<<"Invalid choice. Please enter a valid choice: ";
            cin>>user_choice;
        }
    }

    else{
        cout << "Error: Directory does not exist" << endl;
        return "";
    }

    string file_name=files[user_choice - 1].substr(files[user_choice - 1].find_last_of("/\\")+1);
    file_name=file_name.substr(0, file_name.find_last_of("."));

    cout<<"You chose: "<<file_name<<endl<<endl;
    return files[user_choice - 1];
};

/**
 * @brief Parses a row of the map grid.
 * @param row The row to be parsed.
 * @param map The map object to be built.
 * @param y The y-coordinate of the row.
 * @return
 */
Row SavedMapBuilderFromStringRepresentation::parseGrid(const std::string& row, Map& map, int y) {
    stringstream ss(row);
    Row map_row;

    int x=0;
    Position start;
    Position end;


    for(char c; ss >> c; x++) {
        if (toupper(c) == 'X') {
            map_row.push_back(make_shared<Wall>(std::move(Wall())));
        } else if (toupper(c) == '-') {
            map_row.push_back(nullptr);
        } else if (toupper(c) == 'S') {

            //If the map does not already have a start Cell
            if (map.getStartCell().x == -1 && map.getStartCell().y == -1) {
                start = {x, y};
                map.setStartCell(start);


                map_row.push_back(make_shared<Door>(true, false));
            }

            else{
                throw invalid_argument("The map has more than 1 start");
            }

        } else if (toupper(c) == 'E') {

            //If the map does not already have an exit Cell
            if (map.getEndCell().x == -1 && map.getEndCell().y == -1) {
            end = {x, y};
            map.setEndCell(end);

            map_row.push_back(make_shared<Door>(false, true));
            }

            //If the map already has an exit Cell
            else {
                throw invalid_argument("The map has more than 1 exit");
            }

        } else  //If we reach here then the character is invalid
            throw invalid_argument("Invalid character in map file");

    }

    return map_row;
};

/**
 * @brief Gets the size of the y-coordinate of the map from the file.
 * @param file_path The path to the file.
 * @return
 */
int getSizeYFromFile(string file_path){
    ifstream file(file_path);
    string line;
    int size_y=0;

    while(getline(file, line)){
        size_y++;
    }

    return size_y;
}

/**
 * @brief Builds a map object from a saved map in a file.
 * @return
 */
bool SavedMapBuilderFromStringRepresentation::buildGrid() {
    //User choice of map
    string file_path=chooseMap();

    //Name of the map
    string map_name=file_path.substr(file_path.find_last_of("/\\")+1);
    map_name=map_name.substr(0, map_name.find_last_of("."));

    int size_y=getSizeYFromFile(file_path);
    int y=size_y-1;

    Grid grid(size_y, Row(0));
    Row row;

    ifstream file(file_path);
    string line;

    //While th file has not ended
    while(getline(file, line)){
        try {
            //Read the row and make the necessary checks
            row = parseGrid(line, map, y);
        }

        //If the row is invalid
        catch(invalid_argument& e){
            cout<<e.what()<<endl;
            return false;
        }

        grid[y]=row;

        y--;
    }

    //Set the map's grid and name
    map.setGrid(grid);
    map.setName(map_name);


    if(!map.getGrid().empty()){
        map.setSizeX(map.getGrid().size());

        map.setSizeY(map.getGrid()[0].size());

    }

    //If the map is not valid
    if(!map.validateMap()){
        return false;
    }

    //If map is valid
    return true;
}

/**
 * @brief Returns the newly created map object from the saved files.
 * @return
 */
Map SavedMapBuilderFromStringRepresentation::getMap() {
    return map;
}

/**
 * @brief Director that constructs a saved map
 */
bool MapDirector::constructSavedMap(MapBuilder& builder) {
    if(builder.buildGrid()){
        return true;
    }

    else{
        return false;
    }

}


ostream& Map::displayRevMap(ostream& os) const {
    Map reversed_map = *this;

    reverse(reversed_map.grid.begin(), reversed_map.grid.end());

    string map_str;
    map_str += string(reversed_map.size_x * 2 - 1, '-') + "\n";
    for (auto& row : reversed_map.grid) {
        for (auto& cell : row) {
            if (cell == nullptr) {
                map_str += "- ";
            } else if (shared_ptr<Wall> wall = dynamic_pointer_cast<Wall>(cell)) {
                map_str += "X ";
            } else if (shared_ptr<Character> player = dynamic_pointer_cast<Character>(cell)) {
                map_str += "O ";
            } else if (shared_ptr<Door> entry_exit = dynamic_pointer_cast<Door>(cell)) {
                if (entry_exit->getStart()) {
                    map_str += "S ";
                } else if (entry_exit->getExit()) {
                    map_str += "E ";
                }
            } else {
                // This is done to be able to represent the path during testing
                map_str += "@ ";
            }
        }
        map_str += "\n";
    }
    map_str += string(reversed_map.size_x * 2 - 1, '-') + "\n";

    os << string(reversed_map.size_x * 3 - 1, '-') + "\n"
       << "\n"
       << map_str
       << "size_x: " << reversed_map.size_x << "\n"
       << "size_y: " << reversed_map.size_y << "\n"
       << "startCell: " << reversed_map.startCell << "\n"
       << "endCell: " << reversed_map.endCell << "\n"
       << string(reversed_map.size_x * 3 - 1, '-') + "\n";

    return os;
}

/**
 * @brief Test function for the map builder
 * @return
 */
bool Map::mapBuilderTest(){
    SavedMapBuilderFromStringRepresentation builder;

    MapDirector director;

    if(!director.constructSavedMap(builder)){
        return false;
    }
    ostream& ostream1=cout;

    Map map=builder.getMap();
    map.displayRevMap(ostream1);

    map.specialPlace(Wall(),Position(1,1));
    map.specialPlace(Wall(),Position(1,0));

    map.displayRevMap(ostream1);

    map.validateMap();

    map.specialPlace(Wall(),Position(0,1));
    map.displayRevMap(ostream1);

    map.validateMap();

    map.specialMove(Position(0,1),Position(4,1));
    map.displayRevMap(ostream1);

    map.validateMap();



    return true;
}

bool Map::isInBounds(const sf::Vector2i &pos) const {
    if (pos.x >= 0 && pos.x < size_x && pos.y >= 0 && pos.y < size_y) {
        return true;
    }
    return false;
}
