

/**
 * @file OptionsScreen.h
 * @author Melika Minaei Bidgoli
 * @brief Contains the declaration of the OptionsScreen class.
 */

#ifndef PROJECT_OPTIONSSCREEN_H
#define PROJECT_OPTIONSSCREEN_H

#include "CONFIG.h"
#include "GameLooptyLoop.h"
#include "MapObserver.h"
#include "State.h"

/**
 * @class OptionsScreen
 * @brief Represents the options screen state of the game.
 * 
 * The OptionsScreen class is derived from the State class and represents the state of the game when the options screen is active.
 * It provides methods to initialize, handle input, update, and draw the options screen.
 */
class OptionsScreen: public State {
public:
    /**
     * @brief Constructs an OptionsScreen object.
     * @param data The shared pointer to the MainData object.
     */
    explicit OptionsScreen(MainDataRef data);

    /**
     * @brief Initializes the options screen state.
     */
    void Init() override;

    /**
     * @brief Handles the input for the options screen state.
     */
    void HandleInput() override;

    /**
     * @brief Updates the options screen state.
     * @param deltaTime The time elapsed since the last update.
     */
    void Update(float deltaTime) override;

    /**
     * @brief Draws the options screen state.
     * @param deltaTime The time elapsed since the last draw.
     */
    void Draw(float deltaTime) override;

private:
    MainDataRef _data; ///< The shared pointer to the MainData object.

    Clock _clock; ///< Keeps track of time passed.

    Texture _bgTexture; ///< The background texture.
    Sprite _bg; ///< The background sprite.

    /**
     * @struct Buttons
     * @brief Represents the buttons on the options screen.
     */
    struct Buttons {
        Sprite mute; ///< The mute button sprite.
        Sprite back; ///< The back button sprite.
        Sprite music1; ///< The music1 button sprite.
        Sprite music2; ///< The music2 button sprite.
        Sprite music3; ///< The music3 button sprite.
        Sprite music4; ///< The music4 button sprite.
        RectangleShape music; ///< The music rectangle shape.
        Text musicText; ///< The music text.
    };

    shared_ptr<Buttons> buttons = make_shared<Buttons>(); ///< The shared pointer to the Buttons struct.

    /**
     * @brief Handles the music on the options screen.
     */
    void handleMusic();

    /**
     * @brief Sets up the buttons on the options screen.
     */
    void SetButtons();

    /**
     * @brief Changes the music on the options screen.
     * @param fileName The name of the music file.
     */
    void changeMusic(string fileName);

    /**
     * @brief Generates a button sprite.
     * @param button The button sprite to generate.
     * @param position The position of the button sprite.
     * @param texture The texture of the button sprite.
     */
    static void GenerateButton(Sprite& button, Vector2f position, Texture& texture);

    /**
     * @brief Generates a button with text.
     * @param font The font of the button text.
     * @param name The name of the button.
     * @param button The button rectangle shape.
     * @param buttonText The button text.
     * @param position The position of the button.
     */
    static void GenerateButton(const Font &font, const string &name, RectangleShape &button, Text &buttonText, Vector2f position);
};

#endif//PROJECT_OPTIONSSCREEN_H
