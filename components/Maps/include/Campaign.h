/**
* @file character.h
* @date 25 february 2024, 11 March 2024
* @brief this file contains the declaration of the Campaign class and related structures aliases
* @detail
* 1. The Campaign class is responsible for managing a campaign, including adding and removing maps, 
creating connections between maps, editing maps, and saving/loading the campaign to/from a JSON file.
*/
#ifndef A3_CAMPAIGN_H
#define A3_CAMPAIGN_H

#include "../../Log/include/LogObservable.h"
#include "Map.h"                                                     // Include the "Map.h" header
#include "../../../cmake-build-debug/_deps/json-src/include/nlohmann/json.hpp"// Include the "nlohmann/json.hpp" header
#include <iostream>
#include <unordered_map>
#include <vector>

using json = nlohmann::json;


/**
 * @class Campaign
 * @brief Represents a campaign consisting of multiple maps and their connections.
 * 
 * The Campaign class provides functionality to manage a campaign, including adding and removing maps,
 * creating connections between maps, editing maps, and saving/loading the campaign to/from a JSON file.
 */
class Campaign : public LogObservable{
private:
    std::vector<Map> maps; // Container for storing maps
    std::unordered_map<int, std::vector<int>> adjacencies; // Map index to list of adjacent map indices

public:

    /**
     * @brief Default constructor for Campaign class. Generates a default campaign.
     */
    Campaign();

    std::unique_ptr<std::vector<Map>> getCampaign() const;


    /**
     * @brief Adds a map to the campaign.
     * @param map The map to be added.
     */
    void addMap(const Map& map);


    shared_ptr<Map> getMap(int index) const;

    /**
     * @brief Removes a map from the campaign.
     * @param index The index of the map to be removed.
     * @return True if the map was successfully removed, false otherwise.
     */
    bool removeMap(int index);

    /**
     * @brief Adds a path/connection between two maps in the campaign.
     * @param fromIndex The index of the map from which the path starts.
     * @param toIndex The index of the map to which the path leads.
     * @return True if the path was successfully added, false otherwise.
     */
    bool addPath(int fromIndex, int toIndex);

    /**
     * @brief Removes a path/connection between two maps in the campaign.
     * @param fromIndex The index of the map from which the path starts.
     * @param toIndex The index of the map to which the path leads.
     * @return True if the path was successfully removed, false otherwise.
     */
    bool removePath(int fromIndex, int toIndex);

    /**
     * @brief Edits a map in the campaign.
     * @param index The index of the map to be edited.
     * @param newMap The new map data.
     * @return True if the map was successfully edited, false otherwise.
     */
    bool editMap(int index, const Map& newMap);

    /**
     * @brief Returns the number of maps in the campaign.
     * @return The number of maps.
     */
    size_t getNumberOfMaps() const;

    /**
     * @brief Prints the details of the campaign.
     */
    void printCampaignDetails() const;

    /**
     * @brief Saves the campaign to a JSON file.
     * @param filename The name of the file to save to.
     */
    void saveToJson(const std::string& filename) const;

    /**
     * @brief Loads the campaign from a JSON file.
     * @param filename The name of the file to load from.
     * @return True if the campaign was successfully loaded, false otherwise.
     */
    bool loadFromJson(const std::string& filename);
};
#endif//A3_CAMPAIGN_H

