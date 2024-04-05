#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include "CONFIG.h"
#include "GameLooptyLoop.h"
#include "MapObserver.h"
#include "Player.h"
#include "State.h"
#include "Movable.h"
#include "TreasureChest.h"
#include "GameLooptyLoop.h"
#include "NonPlayerCharacter.h"
#include "../../Maps/include/Lever.h"

#include <cmath>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class MapCreator : public State {
public:


    MapCreator(MainDataRef& data);

    /**
     * @brief Initializes the map creator by asking the user for the map size&name then, load all the Textures.
     */
    void Init() override;

    /**
     * @brief Handles the inputs (clicks) of the user on the window and updates the game logic.
     * @brief Either select an item from the sidebar
     * @brief Or place an item on the map
     * @brief Or clear the map
     * @brief Or save the map
     */
    void HandleInput() override;

    void Update(float deltaTime) override;

    /**
     * @brief Clear the window and then Draw all the components.
     * @param deltaTime
     */
    void Draw(float deltaTime) override;


    struct SidebarItem :public Movable{
        sf::Sprite sprite;
        std::string name;
        int permittedCount;
        sf::Text countText;
        sf::RectangleShape countBackground;

        SidebarItem(const std::string &name, int permittedCount);
    };

private:
    static int nbSavedMaps; /**< The number of maps in the campaign. */

    string mapName; /**< The name of the map. */

    bool isHolding = false; // Flag to indicate if an object is being held

    MapObserver mapObserver; /**< The map observer. */

    std::vector<SidebarItem> sidebarObjects; // List of objects in the sidebar

    shared_ptr<Movable> selectedObject = nullptr; // Pointer to the currently selected object

    std::vector<std::string> itemNames = {"Wall", "Player", "Chest", "Door","Ogre","Lever"};
    sf::Text itemPermittedCount; // To display the number of this object type that can be placed
    sf::RectangleShape sidebar; // To represent the sidebar area
    std::vector<sf::RectangleShape> itemContainers;
    std::vector<sf::Sprite> sidebarObjectsSprites; // To store sprites for items to be placed on the sidebar

    sf::RectangleShape mapArea; // The map area

    sf::RectangleShape buttonContainer; // The container for the buttons
    sf::RectangleShape clearButton; // The clear button
    sf::RectangleShape saveButton; // The save button
    sf::Text clearButtonText; // The text for the clear button
    sf::Text saveButtonText; // The text for the save button

    MainDataRef _data; /**< The main data reference. */

    shared_ptr<Map> _currentMap; /**< The current map. */
    RenderTexture _mapTexture; /**< The texture for rendering the map. */
    RenderTexture _characterView; /**< The texture for rendering the character view. */
    Sprite _bg; /**< The background sprite. */
    Vector2<unsigned int> _windowSize; /**< The window size. */

    struct Buttons {
        RectangleShape menu; /**< The menu button. */
    };

    shared_ptr<Buttons> buttons = make_shared<Buttons>(); /**< The buttons on the game screen. */

    /**
     * @brief Generates the texture for the map.
     *
     * This function generates the texture for rendering the map.
     */

    /**
     * @brief Calculates the sizes of the textures based on the window size.
     *
     * This function calculates the sizes of the map texture, character view texture, and console view texture
     * based on the window size.
     */
    void calculateTextureSizes(int x, int y);

    void loadTextures();

    void saveMapToFile();

    void initSideBar();

    void drawSideBar();

    Position askForSize();

    void initButtons();

    void drawButtons();

    void clearMap();

    void drawMap();



    void Run();

    void selectObjectFromSidebar(const Vector2f &mousePos);

    void placeObjectOnMap(const Vector2f &mousePos);
    void processClickActions(const Vector2f &mousePos);
    void handleCloseEvent();
    void handleMouseButtonPressedEvent(const Event &event);

};
#endif MAPCREATOR_H
