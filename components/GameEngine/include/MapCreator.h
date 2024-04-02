#ifndef MAPCREATOR_H
#define MAPCREATOR_H

#include "CONFIG.h"
#include "GameLooptyLoop.h"
#include "MapObserver.h"
#include "Player.h"
#include "State.h"

class MapCreator : public State {
public:

    MapCreator(MainDataRef& data);

    void Init() override;
    void HandleInput() override;
    void Update(float deltaTime) override;
    void Draw(float deltaTime) override;

private:

    struct PlaceableObject {
        sf::Sprite sprite; // Sprite for the object
        int type; // Identifies the object type
        int nbPremitted; // Number of objects of this type that can be placed
    };

    std::vector<PlaceableObject> sidebarObjects; // List of objects in the sidebar
    PlaceableObject* selectedObject = nullptr; // Pointer to the currently selected object

    sf::RectangleShape sidebar; // To represent the sidebar area
    std::vector<sf::RectangleShape> itemContainers;
    std::vector<sf::Sprite> sidebarObjectsSprites; // To store sprites for items to be placed on the sidebar

    sf::RectangleShape mapArea; // The map area
    sf::RectangleShape characterArea; // The character area

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
    void initMapEditingInterface();

    /**
     * @brief Sets up the buttons on the game screen.
     *
     * This function sets up the buttons on the game screen, including their positions and appearance.
     */
    void SetButtons();

    /**
     * @brief Generates a button with the given font, name, position, and size.
     * @param font The font for the button text.
     * @param name The name of the button.
     * @param button The button shape.
     * @param buttonText The button text.
     * @param position The position of the button.
     */
    static void GenerateButton(const Font &font, const string &name, RectangleShape &button, Text &buttonText, Vector2f position);

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

    Position askForSize();
};
#endif MAPCREATOR_H
