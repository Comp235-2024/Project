//
// Created by Khalil Azaiez on 2024-03-10.
//
#include "Campaign.h"
#include "Pillar.h"
#include "fstream"
#include <algorithm>


void Campaign::addMap(const Map& map) {
    maps.push_back(map);
    adjacencies[maps.size() - 1] = std::vector<int>();
}

bool Campaign::removeMap(int index) {
    if (index < 0 || index >= maps.size()) return false;
    maps.erase(maps.begin() + index);
    adjacencies.erase(index);
    // Adjust adjacencies here if necessary
    return true;
}

bool Campaign::addPath(int fromIndex, int toIndex) {
    if (fromIndex < 0 || fromIndex >= maps.size() || toIndex < 0 || toIndex >= maps.size()) return false;
    adjacencies[fromIndex].push_back(toIndex);
    return true;
}

bool Campaign::removePath(int fromIndex, int toIndex) {
    if (fromIndex < 0 || fromIndex >= maps.size() || toIndex < 0 || toIndex >= maps.size()) return false;
    auto& adjList = adjacencies[fromIndex];
    auto it = std::find(adjList.begin(), adjList.end(), toIndex);
    if (it != adjList.end()) {
        adjList.erase(it);
        return true;
    }
    return false;
}

bool Campaign::editMap(int index, const Map& newMap) {
    if (index < 0 || index >= maps.size()) return false;
    maps[index] = newMap;
    return true;
}

size_t Campaign::getNumberOfMaps() const {
    return maps.size();
}

void Campaign::printCampaignDetails() const {
    std::cout << "Campaign contains " << maps.size() << " maps.\n";
    // Further details can be added as needed
}
void Campaign::saveToJson(const std::string& filename) const {
    json j;
    for (const auto& map : maps) {
        // Example: Save minimal map info; adapt based on your Map class details
        j["maps"].push_back({{"size_x", map.getSizeX()}, {"size_y", map.getSizeY()}});
        // Add more map details as necessary
    }
    // Save adjacencies if needed

    std::ofstream outFile(filename);
    if (!outFile) {
        std::cerr << "Error opening file for writing: " << filename << std::endl;
        return;
    }
    outFile << j.dump(4); // Pretty print with 4 spaces indentation
}

bool Campaign::loadFromJson(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Error opening file for reading: " << filename << std::endl;
        return false;
    }
    json j;
    inFile >> j;
    maps.clear();
    for (const auto& mapJson : j["maps"]) {
        Map map(mapJson["size_x"].get<int>(), mapJson["size_y"].get<int>());
        // Load map details and reconstruct each map
        maps.push_back(map);
    }
    // Load and reconstruct adjacencies if saved

    return true;
}
std::unique_ptr<std::vector<Map>> Campaign::getCampaign() const {
    return std::make_unique<std::vector<Map>>(maps);
}


void Campaign::defaultLevel1(){

    Map map(20, 20);

//    mike = Character(5);
//    map.place(mike, Position{0, 0});
//    mike.textureName = "imp";
    map.setStartCell(Position{0, 0});

    TreasureChest chest{"chest1", 20};
    map.place(chest, Position{5, 7});

    TreasureChest chest2{"chest2", 20};
    map.place(chest2, Position{5, 5});

    TreasureChest chest3{"chest3", 20};
    map.place(chest3, Position{7, 5});

    Wall wall;

    for (int i = 1; i < 10; ++i) {
        map.place(wall, Position{1, i});
        map.place(wall, Position{2, i});
    }

    for (int i = 11; i < 19; ++i) {
        map.place(wall, Position{1, i});
        map.place(wall, Position{2, i});
    }

    for (int i = 3; i < 11; ++i) {
        map.place(wall, Position{i, 17});
        map.place(wall, Position{i, 18});
    }
    for (int i = 3; i < 20; ++i) {
        map.place(wall, Position{i, 12});
        map.place(wall, Position{i, 11});
    }
    map.place(wall, Position{19, 10});
    map.place(wall, Position{13, 19});
    for (int i = 13; i < 19; ++i) {
        map.place(wall, Position{i, 17});
        map.place(wall, Position{i, 18});
    }

    for (int i = 3; i < 19; ++i) {
        map.place(wall, Position{i, 9});
        map.place(wall, Position{i, 8});
    }

    Door door;
    map.place(door, Position{14, 19});
    //map.place(door, Position{0, 5});

//    shared_ptr<Door> door2 = make_shared<Door>();
//    map.place(door2, Position{0, 11});

    for (int i = 3; i < 10; ++i) {
        map.place(wall, Position{i, 1});
        map.place(wall, Position{i, 2});
    }


    for (int i = 0; i < 4; ++i) {
        map.place(wall, Position{12, i});
        map.place(wall, Position{13, i});
    }
    map.place(wall, Position{14, 3});
    map.place(wall, Position{15, 3});
    map.place(wall, Position{14, 4});
    map.place(wall, Position{15, 4});


//    // TODO KEYS
//    shared_ptr<Door> key1 = make_shared<Door>();
//    map.place(key1, Position{14, 2});
//
//    shared_ptr<Door> key2 = make_shared<Door>();
//    map.place(key2, Position{19, 6});
//    //


    map.place(wall, Position{16, 5});
    map.place(wall, Position{17, 5});
    map.place(wall, Position{16, 6});
    map.place(wall, Position{17, 6});
    map.place(wall, Position{18, 5});
    map.place(wall, Position{18, 6});


    this->addMap(map);

}
void Campaign::defaultLevel2(){
    Map map(20, 20);

    // hard enemy
//    Character enemy1{2};
//    map.place(enemy1, Position{7, 8});
//
//    // easy enemy
//    Character enemy2{2};
//        map.place(enemy2, Position{13, 4});

    // easy enemy
    Character enemy2{2};
    map.place(enemy2, Position{13, 4});

   // map.place(mike, Position{9, 0});
    //mike.textureName = "imp";

    map.setStartCell(Position{0, 9});


    Wall wall;

    for (int i = 4; i < 20; ++i) {
        map.place(wall, Position{i, 17});
        map.place(wall, Position{i, 18});
        map.place(wall, Position{i, 19});
    }
    for (int i = 10; i < 20; ++i) {
        for(int j = 11; j < 17; j++)
            map.place(wall, Position{i, j});
    }

    map.place(wall, Position{2, 17});
    map.place(wall, Position{3, 17});
    map.place(wall, Position{2, 18});

    Door door1;
    map.place(door1, Position{3, 18});

    for (int i = 0; i < 8; ++i) {
        map.place(wall, Position{i, 14});
    }

    for (int i = 0; i < 5; ++i) {
        map.place(wall, Position{i, 12});
    }
    for (int i = 1; i < 5; ++i) {
        map.place(wall, Position{i, 10});
    }
    map.place(wall, Position{4, 11});

    for (int i = 10; i < 13; ++i) {
        map.place(wall, Position{6, i});
    }
    map.place(wall, Position{7, 10});
    for (int i = 9; i < 14; ++i) {
        map.place(wall, Position{8, i});
    }
    for (int i = 0; i < 8; ++i) {
        map.place(wall, Position{8, i});
    }
    map.place(wall, Position{7, 7});
    for (int i = 4; i < 7; ++i) {
        map.place(wall, Position{6, i});
    }
    for (int i = 4; i < 9; ++i) {
        map.place(wall, Position{1, i});
    }
    for (int i = 1; i < 7; ++i) {
        map.place(wall, Position{i, 4});
    }

    for (int i = 0; i < 4; ++i) {
        map.place(wall, Position{10, i});
    }
    for (int i = 5; i < 11; ++i) {
        map.place(wall, Position{10, i});
    }
    for (int i = 5; i < 7; ++i) {
        map.place(wall, Position{11, i});
    }
    map.place(wall, Position{19, 1});
    map.place(wall, Position{18, 8});


    for (int i = 11; i < 18; ++i) {
        map.place(wall, Position{i, 0});
    }
    for (int i = 13; i < 15; ++i) {
        map.place(wall, Position{i, 2});
    }
    for (int i = 11; i < 15; ++i) {
        map.place(wall, Position{i, 3});
    }
    for (int i = 13; i < 20; ++i) {
        map.place(wall, Position{i, 5});
    }
    for (int i = 12; i < 19; ++i) {
        map.place(wall, Position{i, 7});
    }
    for (int i = 12; i < 19; ++i) {
        map.place(wall, Position{i, 9});
    }

    //    shared_ptr<Door> door2 = make_shared<Door>();
    //    map.place(door2, Position{9, 13});
    //
    //    //TODO KEY
    //    shared_ptr<Door> key2 = make_shared<Door>();
    //    map.place(key2, Position{7, 6});
    //
    //    shared_ptr<Door> key1 = make_shared<Door>();
    //    map.place(key1, Position{3, 11});
    //    //

    TreasureChest chest1 {"chest1", 20};
    map.place(chest1, Position{17, 8});
    TreasureChest chest2 {"chest2", 20};
    map.place(chest2, Position{11, 2});
    TreasureChest chest3 {"chest3", 20};
    map.place(chest3, Position{12, 2});
    this->addMap(map);

}

void Campaign::defaultLevel3() {


    Map map(20, 20);
    map.setStartCell(Position{3, 3});

    Wall wall;

    for (int i = 0; i < 20; ++i) {
        map.place(wall, Position{0, i});
    }
    for (int i = 0; i < 20; ++i) {
        map.place(wall, Position{i, 0});
    }
    for (int i = 0; i < 20; ++i) {
        map.place(wall, Position{19, i});
    }
    for (int i = 0; i < 20; ++i) {
        map.place(wall, Position{i, 19});
    }

    Pillar pillar;
    for (int i = 14; i < 16; ++i) {
        map.place(pillar, Position{4, i});
        map.place(pillar, Position{5, i});
    }
    for (int i = 14; i < 16; ++i) {
        map.place(pillar, Position{i, 4});
        map.place(pillar, Position{i, 5});
    }
    for (int i = 4; i < 6; ++i) {
        map.place(pillar, Position{i, 4});
        map.place(pillar, Position{i, 5});
    }
    for (int i = 14; i < 16; ++i) {
        map.place(pillar, Position{14, i});
        map.place(pillar, Position{15, i});
    }

//    Character mike{5};
//
//    map.place(mike, Position{12, 12});
//    mike.textureName = "imp";
//    // boss
//    Character boss{2};
//    map.place(boss, Position{9, 9});

    this->addMap(map);

}


Campaign::Campaign() {
    maps = std::vector<Map>();
    ind = 1;
    defaultLevel1();
    defaultLevel2();
    defaultLevel3();
    loadMap = true;
}

void Campaign::loadNextMap() {
    if(loadMap) {
        ind++;
        //removeMap(0);
        if (ind == 2) {
            defaultLevel2();
        } else if (ind == 3) {
            defaultLevel3();
        } else {
            exit(0);
        }
        loadMap = false;
    }

}

shared_ptr<Map> Campaign::getMap(int index) const {
    if (index < this->maps.size()) {
        return make_shared<Map>(this->maps[index]);
    } else {
        this->notify("Map index out of bounds.", "Map");
        throw runtime_error("Map index out of bounds.");
    }
}
