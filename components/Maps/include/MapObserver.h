/**
 * @file Map.h
 * @author Tymofiy Kovalenko
 * @date 24 February 2024
 * @brief This file is the MapObserver class declaration.
 * @details /**
 * @file Map.h
 * @author Tymofiy Kovalenko
 * @date 24 February 2024
 * @brief This file contains the declaration of the Map class and related structures and aliases.
 * @details
 * 1. The Observer receives updates from the Observable and displays the map using SFML. It also receives
 * updates from driver to ensure the map is displayed correctly.
 * 
 * 2. The librarie used in this file is SFML/Graphics.hpp. It helps to display the map using with a Gui.
 */

#ifndef A3_MAPOBSERVER_H
#define A3_MAPOBSERVER_H

#include "../../Functionalities/include/Dice.h"
#include "CONFIG.h"
#include "GameLooptyLoop.h"
#include "LogObserver.h"
#include "Map.h"
#include "Observer.h"
#include "NonPlayerCharacter.h"
#include "Player.h"
#include "Lever.h"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Graphics.hpp>
#include <memory>
#include <unordered_map>
using namespace sf;

/**
 * @class MapObserver
 * @brief A class that observes and displays a map.
 * 
 * The MapObserver class is responsible for observing and displaying a map using SFML.
 * It inherits from the Observer class.
 */
class MapObserver : public Observer, public LogObservable{

public:
    /**
     * @brief Constructs a MapObserver object.
     * @param map A pointer to the map object.
     * @param window A pointer to the SFML render window.
     */
    MapObserver(shared_ptr<Map> map, sf::RenderTexture *window, MainDataRef data);

    MapObserver() = default;


    MapObserver(shared_ptr<Map> sharedPtr, RenderTexture *pTexture);
    /**
     * @brief Destroys the MapObserver object.
     */
    ~MapObserver() override;

    /**
     * @brief Updates the map observer.
     * 
     * This function is called when the observed map changes and updates the observer's display.
     */
    void update() override;

    /**
     * @brief Updates only the map display.
     * @param _window A pointer to the SFML render window.
     */
    void updateMapOnly(RenderTexture *_window);

    /**
     * @brief Gets the SFML render window.
     * @return A pointer to the SFML render window.
     */
    RenderTexture *getWindow();

    /**
     * @brief Gets the width of the render window.
     * @return The width of the render window.
     */
    int getWindowSizeX() const;

    /**
     * @brief Gets the height of the render window.
     * @return The height of the render window.
     */
    int getWindowSizeY() const;

    /**
     * @brief Gets the size multiplier for the map display.
     * @return The size multiplier.
     */
    float getSizeMult() const;

    void assignTextureToCell(int x, int y, const Texture& tex);

    const Texture& getTextureForCell(int x, int y) const;


    void drawCircleAroundPos(Vector2i position, int i, const Color color, RenderTexture *_window);

    float SIZE_MULT = 30; /**< The size multiplier for the map display. */

private:

    MainDataRef _data;

    struct pair_hash {
        template<class T1, class T2>
        size_t operator () (const pair<T1, T2> &pair) const {
            auto hash1 = hash<T1>{}(pair.first);
            auto hash2 = hash<T2>{}(pair.second);
            return hash1 ^ hash2;
        }
    };
    
    unordered_map<pair<int, int>, Texture, pair_hash> textureMap;
    shared_ptr<Map> grid; /**< A pointer to the map object. */
    sf::RenderTexture* window; /**< A pointer to the SFML render window. */
    int window_size_x{}; /**< The width of the render window. */
    int window_size_y{}; /**< The height of the render window. */


    /**
     * @brief Draws the map observer's display.
     */
    void draw();

    /**
     * @brief Draws the grid lines on the map display.
     * @param window A pointer to the SFML render window.
     * @param line The horizontal grid line shape.
     * @param line_v The vertical grid line shape.
     */
    void drawGridLines(RenderTexture *window, RectangleShape &line, RectangleShape &line_v) const;

    /**
     * @brief Draws a red X at the specified position on the map display.
     * @param window A pointer to the SFML render window.
     * @param posX The x-coordinate of the position.
     * @param posY The y-coordinate of the position.
     */
    void drawRedX(sf::RenderWindow *window, float posX, float posY) const;

    /**
     * @brief Draws the map on the map display.
     * @param _window A pointer to the SFML render window.
     */
    void drawMap(RenderTexture *_window);

    /**
     * @brief Draws an image at the specified position on the map display.
     * @param pWindow A pointer to the SFML render window.
     * @param pathToImage The path to the image file.
     * @param x The x-coordinate of the position.
     * @param y The y-coordinate of the position.
     */
    void drawImage(RenderTexture *pWindow, const char *pathToImage, float x, float y);
    void drawFloor(RenderTexture *pWindow, float x, float y);

    void generateFloorTextureHashMap();
    void drawBorderAroundCell(const Vector2i &position, const Color &color, RenderTexture *_window, int _thickness) const;
};

#endif //A3_MAPOBSERVER_H
