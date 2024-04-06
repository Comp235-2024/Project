/**
 * @file GameScreen.h
 * @brief This file contains the declaration of the GameScreen class, which represents the game screen or main menu of the game.
 * The player can start the game, switch to a different map, or exit the game from this screen.
 * @author Tymofiy Kovalenko
 * @date 22-Mar-2024
 */
#ifndef A3_GAMESCREEN_H
#define A3_GAMESCREEN_H

#include "CONFIG.h"
#include "GameLooptyLoop.h"
#include "MapObserver.h"
#include "Player.h"
#include "State.h"

/**
 * @class GameScreen
 * @brief Represents the game screen state.
 * 
 * The GameScreen class is derived from the State class and represents the state of the game screen.
 * It handles the initialization, input handling, updating, and drawing of the game screen.
 */
class GameScreen : public State {

public:
    /**
     * @brief Constructs a GameScreen object with the given main data.
     * @param data The main data reference.
     */
    explicit GameScreen(MainDataRef& data);

    /**
     * @brief Initializes the game screen.
     * 
     * This function is called when the game screen is first entered.
     * It initializes the necessary resources and variables.
     */
    void Init() override;

    /**
     * @brief Handles the input for the game screen.
     * 
     * This function is called to handle the input events for the game screen.
     * It processes the user input and performs the corresponding actions.
     */
    void HandleInput() override;

    /**
     * @brief Updates the game screen.
     * 
     * This function is called to update the game screen.
     * It updates the game logic based on the elapsed time since the last update.
     * @param deltaTime The time elapsed since the last update.
     */
    void Update(float deltaTime) override;

    /**
     * @brief Draws the game screen.
     * 
     * This function is called to draw the game screen.
     * It renders the game objects and displays them on the screen.
     * @param deltaTime The time elapsed since the last draw.
     */
    void Draw(float deltaTime) override;


private:
    MainDataRef _data; /**< The main data reference. */
    int _mapIndex = 0;
    Clock _clock; /**< Keeps track of time passed. */

    shared_ptr<Map> _currentMap; /**< The current map. */
    RenderTexture _mapTexture; /**< The texture for rendering the map. */
    RenderTexture _characterView; /**< The texture for rendering the character view. */
    RenderTexture _consoleView; /**< The texture for rendering the console view. */
    RenderTexture _sideBarTexture; /**< The texture for rendering the sidebar. */
    Vector2<float> _sideBarPosition;
    Texture _bgTexture; /**< The background texture. */
    RectangleShape _bg; /**< The background shape. */
    Vector2u _windowSize; /**< The window size. */

    //MODIFIED THIS TO BE A PLAYER AND NOT CHARACTER
    shared_ptr<Character> _player; /**< The player character. */
    Campaign _campaign;
    MapObserver _mapObserver; /**< The map observer. */

    int _diceModifier; /**< The dice modifier for the player character. */
    string _diceType = "1d6"; /**< The dice type for the player character. */

    bool _moveEnabled = false; /**< Indicates whether the move button is enabled. */
    bool _attackEnabled = false; /**< Indicates whether the attack button is enabled. */

    /**
     * @struct MapPosition
     * @brief Represents the position and size of a map.
     */
    struct MapPosition {
        Vector2f position; /**< The position of the map. */
        Rect<float> size; /**< The size of the map. */
    };

    /**
     * @struct Buttons
     * @brief Represents the buttons on the game screen.
     */
    struct Buttons {
        RectangleShape menu; /**< The menu button. */
        Text menuText;
        RectangleShape move;
        Text moveText;
        RectangleShape attack;
        Text attackText;
        RectangleShape inventory;
        Text inventoryText;
        RectangleShape rollDice;
        Text rollDiceText;
    };

    shared_ptr<Buttons> buttons = make_shared<Buttons>(); /**< The buttons on the game screen. */

    /**
     * @brief Generates the texture for the map.
     * 
     * This function generates the texture for rendering the map.
     */
    void generateMapTexture();

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
    void calculateTextureSizes();

    /**
     * @brief Finds the player character in the current map.
     * 
     * This function finds the player character in the current map and sets it as the active character.
     */
    void findPlayerCharacter();

    void scanForNearbyObjects();
    static Vector2i positionToVector2i(Position position);
    void generateSideBarTexture();
    void generateButton(RectangleShape &button, Text &buttonText, const string &name, int buttonPos);
};

#endif