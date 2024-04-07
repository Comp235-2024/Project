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
#include <memory>
#include <vector>

using namespace sf;
using namespace std;

/**
 * @brief Manages the turn order and turn-based interactions in the game.
 */
class TurnManager : public LogObservable {
private:
    vector<shared_ptr<Character>> characterList;     ///< List of all characters in turn order.
    int currentIndex = 0;                            ///< Index of the current character's turn.
    shared_ptr<Character> currentPlayer;             ///< Pointer to the current player character.
    bool turnChanged = true;                         ///< Indicates if the turn has changed.
    float messageTimer = 0;                          ///< Timer for displaying messages.
    const float MESSAGE_DURATION = 30.0f;            ///< Duration to display messages.

public:
    TurnManager();
    ~TurnManager() override;

    /**
     * @brief Adds a character to the turn order.
     * @param character Shared pointer to the character being added.
     * @param isPlayer Indicates if the character is the player.
     */
    void addCharacter(const shared_ptr<Character> &character, const bool &isPlayer = false);

    /**
     * @brief Draws the turn indicator on screen.
     * @param _data Reference to the main game data.
     * @param deltaTime Time since the last update.
     */
    void drawWhoseTurn(const MainDataRef &_data, float deltaTime);

    /**
     * @brief Advances to the next character's turn.
     */
    void nextTurn();

    /**
     * @brief Checks if it is the player's turn.
     * @return True if it is the player's turn, false otherwise.
     */
    bool isPlayerTurn();

    /**
     * @brief Checks if it is an NPC's turn.
     * @return True if it is an NPC's turn, false otherwise.
     */
    bool isNPCTurn();

    /**
     * @brief Retrieves the current player.
     * @return Shared pointer to the current player character.
     */
    shared_ptr<Character> getCurrentPlayer();

    /**
     * @brief Resets the turn order to the first character.
     */
    void resetTurns();

    /**
     * @brief Gets the number of players in the turn order.
     * @return Number of players.
     */
    int getNumPlayers();

    /**
     * @brief Removes a player from the turn order.
     * @param player Shared pointer to the player being removed.
     */
    void removePlayer(const shared_ptr<Character> &player);

    /**
     * @brief Clears all characters from the turn order.
     */
    void clear();

    /**
     * @brief Retrieves all players in the turn order.
     * @return Vector of shared pointers to all characters.
     */
    vector<shared_ptr<Character>> getPlayers();
};

#endif // PROJECT_TURNMANAGER_H

