/**
 * @file InputManager.cpp
 * @author Tymofiy Kovalenko
 * @date 17-Mar-2024
 * @brief
 */

#include "InputManager.h"
bool InputManager::IsSpriteClicked(const Sprite& sprite, Mouse::Button button, RenderWindow &window) {
    if (Mouse::isButtonPressed(button)) {

        auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
        auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates
        if(sprite.getGlobalBounds().contains(translated_pos)) // Rectangle-contains-point check
        {
            return true;
        }
    }
    return false;
}
Vector2i InputManager::GetMousePos(RenderWindow &window) {
    return Mouse::getPosition(window);
}
bool InputManager::IsButtonClicked(const RectangleShape &rectangleShape, Mouse::Button button, RenderWindow &window) {
    if (Mouse::isButtonPressed(button)) {
        IntRect buttonRect(
                rectangleShape.getPosition().x - rectangleShape.getSize().x / 2.0f,
                rectangleShape.getPosition().y - rectangleShape.getSize().y / 2.0f,
                rectangleShape.getSize().x,
                rectangleShape.getSize().y);
        if (buttonRect.contains(Mouse::getPosition(window))) {
            return true;
        }
    }
    return false;
}
bool InputManager::IsButtonClicked(const RectangleShape &rectangleShape, Mouse::Button button, RenderWindow &window, const Vector2f &renderTexturePosition) {
    if (Mouse::isButtonPressed(button)) {

        Vector2i mousePos = Mouse::getPosition(window);
        Vector2f mousePosFloat = window.mapPixelToCoords(mousePos);

        mousePosFloat.x -= renderTexturePosition.x;
        mousePosFloat.y -= renderTexturePosition.y;
        FloatRect buttonGlobalBounds = rectangleShape.getGlobalBounds();

        if (buttonGlobalBounds.contains(mousePosFloat)) {
            return true;
        }
    }
    return false;
}
