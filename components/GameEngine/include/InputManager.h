/**
 * @file InputManager.h
 * @brief This file contains the declaration of the InputManager class.
 * @author Tymofiy Kovalenko
 * @date 17-Mar-2024
 */

#ifndef A2_INPUTMANAGER_H
#define A2_INPUTMANAGER_H

#include "SFML/Graphics.hpp"
using namespace sf;
using namespace std;

/**
 * @class InputManager
 * @brief The InputManager class provides utility functions for handling user input.
 */
class InputManager {
public:
    /**
     * @brief Default constructor for InputManager.
     */
    InputManager() = default;

    /**
     * @brief Default destructor for InputManager.
     */
    ~InputManager() = default;

    /**
     * @brief Checks if a sprite is clicked by the specified mouse button.
     * @param sprite The sprite to check.
     * @param button The mouse button to check.
     * @param window The render window to check.
     * @return True if the sprite is clicked, false otherwise.
     */
    static bool IsSpriteClicked(const Sprite& sprite, Mouse::Button button, RenderWindow& window);

    /**
     * @brief Checks if a button (represented by a rectangle shape) is clicked by the specified mouse button.
     * @param rectangleShape The rectangle shape representing the button.
     * @param button The mouse button to check.
     * @param window The render window to check.
     * @return True if the button is clicked, false otherwise.
     */
    static bool IsButtonClicked(const RectangleShape& rectangleShape, Mouse::Button button, RenderWindow& window);

    /**
     * @brief Gets the current mouse position relative to the specified render window.
     * @param window The render window to get the mouse position from.
     * @return The current mouse position as a Vector2i object.
     */
    static Vector2i GetMousePos(RenderWindow& window);
};

#endif // A2_INPUTMANAGER_H
