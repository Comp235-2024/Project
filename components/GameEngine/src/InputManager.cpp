/**
 * @file InputManager.cpp
 * @author Tymofiy Kovalenko
 * @date 17-Mar-2024
 * @brief
 */

#include "InputManager.h"
bool InputManager::IsSpriteClicked(const Sprite& sprite, Mouse::Button button, RenderWindow &window) {
    if (Mouse::isButtonPressed(button)) {
        IntRect buttonRect(
                sprite.getPosition().x,
                sprite.getPosition().y,
                sprite.getGlobalBounds().width,
                sprite.getGlobalBounds().height);
        if (buttonRect.contains(Mouse::getPosition(window))) {
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
