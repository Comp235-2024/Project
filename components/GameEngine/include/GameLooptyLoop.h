/**
 * @file GameLooptyLoop.h
 * @brief Header file for the GameLooptyLoop class.
 * 
 * This file defines the GameLooptyLoop class, which represents the main game loop of the application.
 * The GameLooptyLoop class is responsible for managing the game state, handling user input, and updating the game logic.
 * It also contains a MainData struct that holds various game-related data, such as the state machine, window, asset manager, input manager, log observer, and campaign.
 */

#ifndef A2_GAMELOOPTYLOOP_H
#define A2_GAMELOOPTYLOOP_H

#include "AssetManager.h"
#include "Campaign.h"
#include "Dice.h"
#include "InputManager.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include "State.h"
#include "StateMachine.h"
#include <memory>
#include <string>
#include <SFML/Audio.hpp>
#include <SFML/Audio/Music.hpp>
struct MainData{
    StateMachine stateMachine;
    RenderWindow window;
    AssetManager assets;
    InputManager inputs;
    LogObserver* log;
    unique_ptr<Campaign> campaign;
    Music music;
    Dice dice;
    Player player;
};

typedef shared_ptr<MainData> MainDataRef;

class GameLooptyLoop {
public:
    /**
     * @brief Constructs a GameLooptyLoop object with the specified width, height, and title.
     * 
     * @param width The width of the game window.
     * @param height The height of the game window.
     * @param title The title of the game window.
     */
    GameLooptyLoop(int width, int height, const string& title);

private:
    const float deltaTime = 1.0f / 60.0f;
    Clock _clock;
    MainDataRef _data = make_shared<MainData>();
    /**
     * @brief Runs the game loop.
     * 
     * This function is responsible for running the main game loop, which includes updating the game logic, handling user input,
     * and rendering the game state.
     */
    void Run();
};

#endif//A2_GAMELOOPTYLOOP_H
