/**
 * @file TurnManager.cpp
 * @author Tymofiy Kovalenko
 * @date 06-Apr-2024
 * @brief
 */

#include "TurnManager.h"
#include <algorithm>

TurnManager::TurnManager() = default;

TurnManager::~TurnManager() = default;

void TurnManager::addCharacter(const shared_ptr<Character> &character, const bool &isPlayer) {
    characterList.push_back(character);
    if (isPlayer) {
        currentPlayer = character;
        this->notify("Player added to the game", "System");
    } else {
        this->notify("NPC added to the game", "System");
    }
    std::sort(characterList.begin(), characterList.end(), [](const shared_ptr<Character> &a, const shared_ptr<Character> &b) {
        return a->getInitiative() > b->getInitiative();
    });
}

void TurnManager::drawWhoseTurn(const MainDataRef &_data, float deltaTime) {
    if (!turnChanged){
        return;
    } else if (messageTimer < MESSAGE_DURATION){
        messageTimer += deltaTime;
    } else {
        turnChanged = false;
    }

    RectangleShape turnBox(Vector2f(250, 50));
    turnBox.setFillColor(Color(210, 180, 140, 200)); // Semi-transparent
    turnBox.setOutlineThickness(2);
    turnBox.setOutlineColor(Color(50, 50, 50));
    sf::Vector2u windowSize = _data->window.getSize();
    turnBox.setPosition((windowSize.x - turnBox.getSize().x) / 2.f, (windowSize.y - turnBox.getSize().y) / 2.f);

    Text turnText;
    turnText.setFont(_data->assets.GetFont("My Font"));
    turnText.setString(isPlayerTurn() ? "Player's Turn" : "NPC's Turn");
    turnText.setCharacterSize(24);
    turnText.setFillColor(Color::Black);
    sf::FloatRect textRect = turnText.getLocalBounds();
    turnText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    turnText.setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));

    _data->window.draw(turnBox);
    _data->window.draw(turnText);
}

void TurnManager::nextTurn() {
    currentIndex = (currentIndex + 1) % characterList.size();
    turnChanged = true; // Indicate that turn has changed for drawing
    messageTimer = 0; // Reset message display timer
    this->notify("Next turn", "System");
}

bool TurnManager::isPlayerTurn() {
    return characterList[currentIndex] == currentPlayer;
}

bool TurnManager::isNPCTurn() {
    return !isPlayerTurn();
}

shared_ptr<Character> TurnManager::getCurrentPlayer() {
    return characterList[currentIndex];
}

void TurnManager::resetTurns() {
    currentIndex = 0;
    this->notify("Turns reset", "System");
}

int TurnManager::getNumPlayers() {
    return characterList.size();
}

void TurnManager::removePlayer(const shared_ptr<Character> &player) {
    auto it = std::remove(characterList.begin(), characterList.end(), player);
    characterList.erase(it, characterList.end());
    this->notify("Player removed", "System");
}

void TurnManager::clear() {
    characterList.clear();
    currentIndex = 0;
    this->notify("All players removed", "System");
}

vector<shared_ptr<Character>> TurnManager::getPlayers() {
    return characterList;
}

