/**
 * @file TurnManager.h
 * @author Tymofiy Kovalenko
 * @date 06-Apr-2024
 * @brief
 */

#ifndef PROJECT_TURNMANAGER_H
#define PROJECT_TURNMANAGER_H

#include "GameLooptyLoop.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include <algorithm>
#include <memory>
#include <vector>

using namespace std;
using namespace sf;

class TurnManager : public LogObservable {
private:
    vector<shared_ptr<Character>> characterList;
    int currentIndex = 0;
    shared_ptr<Character> currentPlayer;

public:
    TurnManager() = default;
    ~TurnManager() = default;

    void addCharacter(const shared_ptr<Character> &character, const bool &isPlayer = false) {
        if (isPlayer){
            currentPlayer = character;
            this->notify("Player added to the game", "System");
        } else {
            this->notify("NPC added to the game", "System");
        }
        characterList.push_back(character);
        std::sort(characterList.begin(), characterList.end(), [](const shared_ptr<Character> &a, const shared_ptr<Character> &b) {
            return a->getInitiative() > b->getInitiative();
        });
    }

    void drawWhoseTurn(const MainDataRef& _data) {
        RectangleShape turnBox(Vector2f(200, 50));
        turnBox.setFillColor(Color::Transparent);
        turnBox.setOutlineThickness(2);
        turnBox.setOutlineColor(Color::Black);
        sf::Vector2u windowSize = _data->window.getSize();
        turnBox.setPosition((windowSize.x - turnBox.getSize().x) / 2.f, (windowSize.y - turnBox.getSize().y) / 2.f);

        Text turnText;
        turnText.setFont(_data->assets.GetFont("My Font"));

        if (isPlayerTurn()) {
            turnText.setString("Player's Turn");
            this->notify("Player's Turn", "System");
        } else if (isNPCTurn()) {
            turnText.setString("NPC's Turn");
            this->notify("NPC's Turn", "System");
        } else {
            return;
        }

        turnText.setCharacterSize(24);
        turnText.setFillColor(Color::Black);

        sf::FloatRect textRect = turnText.getLocalBounds();
        turnText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
        turnText.setPosition(sf::Vector2f(windowSize.x / 2.0f, windowSize.y / 2.0f));

        _data->window.draw(turnBox);
        _data->window.draw(turnText);

    }


    void nextTurn() {
        currentIndex = (currentIndex + 1) % characterList.size();
        this->notify("Next turn", "System");
    }

    bool isPlayerTurn() {
        return characterList[currentIndex] == currentPlayer;
    }

    bool isNPCTurn() {
        return !isPlayerTurn();
    }

    shared_ptr<Character> getCurrentPlayer() {
        return characterList[currentIndex];
    }


    void resetTurns() {
        currentIndex = 0;
        this->notify("Turns reset", "System");
    }

    int getNumPlayers() {
        return characterList.size();
    }

    void removePlayer(const shared_ptr<Character> &player) {
        characterList.erase(remove(characterList.begin(), characterList.end(), player), characterList.end());
        this->notify("Player removed", "System");
    }

    void clear() {
        characterList.clear();
        this->notify("All players removed", "System");
    }

    vector<shared_ptr<Character>> getPlayers() {
        return characterList;
    }
};


#endif//PROJECT_TURNMANAGER_H
