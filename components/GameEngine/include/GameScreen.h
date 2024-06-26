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
#include "TurnManager.h"
#include "Campaign.h"

/**
 * @class GameScreen
 * @brief Represents the game screen state.
 * 
 * The GameScreen class is derived from the State class and represents the state of the game screen.
 * It handles the initialization, input handling, updating, and drawing of the game screen.
 */
class GameScreen : public State {

struct enable_flags {
    bool turn_manager = false;
    bool draw_whose_turn = false;
    bool attack = true;
    bool move = true;
    bool inventory = true;
    bool roll_dice = true;
    bool interact = true;
    bool objective = false;
};

enum class GameState {
    StartScreen,
    Idle,
    Moving,
    Attacking,
    Interacting,
    RollingDice,
    Inventory,
    Stats,
    Exiting,

};

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

    /**
     * @brief Changes the state of the game screen.
     *
     * This function is called to change the state of the game screen.
     */
    void ChangeState(GameState newState);



private:
    MainDataRef _data; /**< The main data reference. */
    int _mapIndex = 0;
    Clock _clock; /**< Keeps track of time passed. */

    shared_ptr<Map> _currentMap; /**< The current map. */
    RenderTexture _mapTexture; /**< The texture for rendering the map. */
    RenderTexture _characterView; /**< The texture for rendering the character view. */
    RenderTexture _consoleTexture; /**< The texture for rendering the console view. */
    Vector2f _consolePosition; /**< The position of the console view. */
    RenderTexture _sideBarTexture; /**< The texture for rendering the sidebar. */
    Vector2<float> _sideBarPosition;
    Texture _bgTexture; /**< The background texture. */
    RectangleShape _bg; /**< The background shape. */
    Vector2u _windowSize; /**< The window size. */

    shared_ptr<Player> _player; /**< The player character. */
    vector<shared_ptr<NonPlayerCharacter>> _npcs; /**< The non-player characters. */
    Campaign _campaign;
    MapObserver _mapObserver; /**< The map observer. */

    const Color buttonColorFill{Color(210, 180, 140)};
    const Color buttonColorText{Color(50, 50, 50)};
    const Color buttonInactiveColor{Color(150, 150, 150)};
    const Color buttonEndTurnColor{Color(120, 150, 86)};
    const Color buttonExitGameColor{Color(170, 100, 100)};

    Color _sideBarButtonColor = buttonColorFill;

    GameState _gameState = GameState::StartScreen; /**< The current game state. */

    unique_ptr<enable_flags> _enableFlags = make_unique<enable_flags>();

    shared_ptr<TurnManager> _turnManager; /**< The turn manager. */

    int _diceModifier; /**< The dice modifier for the player character. */
    string _diceType = "1d20"; /**< The dice type for the player character. */

    std::array<std::pair<Keyboard::Key, Vector2i>, 4> movementBindings = {
            {{Keyboard::Up,    {0, -1}},
             {Keyboard::Down,  {0, 1}},
             {Keyboard::Left,  {-1, 0}},
             {Keyboard::Right, {1, 0}}}
    };

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
        RectangleShape move;
        Text moveText;
        RectangleShape attack;
        Text attackText;
        RectangleShape inventory;
        Text inventoryText;
        RectangleShape rollDice;
        Text rollDiceText;
        RectangleShape exit;
        Text exitText;
        RectangleShape endTurn;
        Text endTurnText;
        RectangleShape stats;
        Text statsText;
        RectangleShape start;
        Text startText;
        RectangleShape inventoryExit;
        Text inventoryExitText;
        RectangleShape chestExit;
        Text chestExitText;
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
     * @brief Finds the NPC characters in the current map.
     * 
     * This function finds the NPC characters in the current map and stores them in the _npcs vector.
     */
    void findNPCs();

    /**
     * @brief Scans for nearby objects in the current map.
     * 
     * This function scans for nearby objects in the current map and performs actions based on the objects found.
     */
     void scanForNearbyObjects();

     /**
      * @brief Checks if the position are within 1 cell of each other (Diagonals included)
      * @brief Does not do type checking
      * @param pos1
      * @param pos2
      * @return
      */
     bool isAdjacent(const Vector2i& pos1, const Vector2i& pos2);


    /**
     * @brief Converts a position to a Vector2i.
     * @param position The position to convert.
     * @return The converted Vector2i.
     */
    static Vector2i positionToVector2i(Position position);

    /**
     * @brief Generates the texture for the sidebar.
     * 
     * This function generates the texture for rendering the sidebar.
     */
    void generateSideBarTexture();

    /**
     * @brief Generates a button with the given name and position.
     * @param button The button shape.
     * @param buttonText The button text.
     * @param name The name of the button.
     * @param buttonPos The position of the button.
     */
    void generateButton(RectangleShape &button, Text &buttonText, const string &name, int buttonPos, bool active, Color buttonColor);

    /**
     * @brief Generates the texture for the console view.
     * 
     * This function generates the texture for rendering the console view.
     */
    void generateConsoleTexture();
    void movePlayer(Vector2i dir);
    void handleKeyboardArrows();
    void handleMouseButtonMap();
    void onMoveOrAttack();
    void HandlePlayerActions();
    void HandleNpcActions();
    void handleStart();
    void drawStartScreen();

    /**
     * @brief Calls the appropriate functions to let the user interact with their inventory
     */
    void handleInventory();

    /**
     * @brief Processes the player's inventory click and selects the respective item
     */
    void processInventoryBackpackClick();

    /**
     * @brief Processes the player's worn items click and selects the respective item
     */
    void processInventoryWornItemsClick();

    /**
     * @brief Processes the player's chest click and selects the respective item from the fixed worn Items sequence
     *
     * @param itemType
     * @return
     */
    int getSlotIndexForItem(const std::string& itemType);

    /**
     * @brief given the previously selected item, it equips it to the player
     */
    void equipSelectedItem();

    /**
     * @brief checks whether the user is spamming clicks
     * @return
     */
    bool isClickAllowed();

    /**
     * @brief checks if the selected Item exists
     */
    void checkItemSelection();

    /**
     * @brief Either selects or deselects the item
     * @param itemAtSlot
     */
    void toggleItemSelection(std::shared_ptr<Item>& itemAtSlot);


    shared_ptr<Item> selectedItem;

    std::vector<sf::RectangleShape> chestItemRectangles;

    /**
     * @brief Draws the Inventory interface
     */
    void drawInventoryScreen();

    /**
     * @brief Draws the Inventory items
     * @param wornItemsSection
     * @param backpackItemsSection
     */
    void drawInventoryItems(RectangleShape* wornItemsSection, RectangleShape* backpackItemsSection);
    //Since the inventory screen is a bit more complex, we need to keep track of the current state
    //Due to the continuous loop, we need to notify that the state is inventory only once
    int inventoryFlag =0;

    /**
     * @brief Checks whether the player exited the inventory screen
     */
    void handleInventoryExitButton();
    RectangleShape backpackScreenSection;
    RectangleShape wornItemsScreenSection;

    /**
     * @brief Draws a specific chest's interface
     */
    void drawChestScreen();
    Position chestPositionFlag;
    void drawChestItems(RectangleShape* chestItemsSection, RectangleShape* backpackItemsSection);
    void handleChest();
    void handleChestExitButton();
    int chestFlag =0;
    RectangleShape chestScreenSection;


    void adjustTextSize(sf::Text &text, float maxWidth, float maxHeight);
    void drawMapStuff();
    void drawHealthBars();
    void handleAttack(shared_ptr<Player> player, shared_ptr<NonPlayerCharacter> npc);
    void handleAttack(shared_ptr<NonPlayerCharacter> npc, shared_ptr<Player> player);
    void make_npc_into_chest(Vector2i vector2);
};

#endif // GAME_SCREEN_H
