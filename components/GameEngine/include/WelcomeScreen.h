/**
 * @file WelcomeScreen.h
 * @author Tymofiy Kovalenko
 * @date 17-Mar-2024
 * @brief
 */

#ifndef A2_WELCOMESCREEN_H
#define A2_WELCOMESCREEN_H

#include "CONFIG.h"
#include "GameLooptyLoop.h"
#include "SFML/Graphics.hpp"
#include "State.h"
#include "sstream"
#include <iostream>


/**
 * @class WelcomeScreen
 * @brief Represents the welcome screen state of the game.
 * 
 * The WelcomeScreen class is derived from the State class and is responsible for managing the welcome screen state of the game.
 * It handles initialization, input handling, updating, and drawing of the welcome screen.
 */
class WelcomeScreen : public State{
public:
    /**
     * @brief Constructs a WelcomeScreen object.
     * @param data The reference to the main data object.
     */
    explicit WelcomeScreen(MainDataRef data);

    /**
     * @brief Initializes the welcome screen state.
     */
    void Init() override;

    /**
     * @brief Handles the input for the welcome screen state.
     */
    void HandleInput() override;

    /**
     * @brief Updates the welcome screen state.
     * @param deltaTime The time passed since the last update.
     */
    void Update(float deltaTime) override;

    /**
     * @brief Draws the welcome screen state.
     * @param deltaTime The time passed since the last draw.
     */
    void Draw(float deltaTime) override;

private:
    MainDataRef _data; ///< The reference to the main data object.

    Clock _clock; ///< Keeps track of time passed.

    Texture _bgTexture; ///< The background texture.
    Sprite _bg; ///< The background sprite.
    Text text; ///< The text object.

};

#endif
