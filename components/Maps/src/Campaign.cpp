//
// Created by Khalil Azaiez on 2024-03-10.
//
#include "Campaign.h"
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


Campaign::Campaign() {
    // Placeholder for now
    maps = std::vector<Map>();

    Character mike{5};
    mike.textureName = "imp";

    Map map(20, 20);
    map.place(mike, Position{9, 9});

    TreasureChest chest{"chest1", 20};
    map.place(chest, Position{5, 5});

    Wall wall;

    for (int i = 0; i < 12; ++i) {
        map.place(wall, Position{1, i});
    }

    for (int i = 0; i < 12; ++i) {
        map.place(wall, Position{15, i});
        map.place(wall, Position{i, 12});
    }



    this->addMap(map);

}

shared_ptr<Map> Campaign::getMap(int index) const {
    if (index < this->maps.size()) {
        return make_shared<Map>(this->maps[index]);
    } else {
        this->notify("Map index out of bounds.", "Map");
        throw runtime_error("Map index out of bounds.");
    }
}
