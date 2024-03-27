/**
 * @file State.h
 * @author Tymofiy Kovalenko
 * @date 17-Mar-2024
 * @brief
 */

#ifndef A2_STATE_H
#define A2_STATE_H


#include "../../Log/include/LogObservable.h"

/**
 * @brief The State class is an abstract base class for implementing different states in a game.
 * 
 * The State class provides a common interface for initializing, handling input, updating, and drawing game states.
 * It also includes optional methods for pausing and resuming a state.
 * 
 * To create a new state, derive from this class and implement the necessary methods.
 */
class State : public LogObservable{
public:
    /**
     * @brief Initializes the state.
     * 
     * This method is called once when the state is first entered.
     */
    virtual void Init() = 0;

    /**
     * @brief Handles user input for the state.
     * 
     * This method is called every frame to handle user input specific to the state.
     */
    virtual void HandleInput() = 0;

    /**
     * @brief Updates the state.
     * 
     * This method is called every frame to update the state's logic and data.
     * 
     * @param deltaTime The time elapsed since the last frame.
     */
    virtual void Update(float deltaTime) = 0;

    /**
     * @brief Draws the state.
     * 
     * This method is called every frame to draw the state's graphics.
     * 
     * @param deltaTime The time elapsed since the last frame.
     */
    virtual void Draw( float deltaTime ) = 0;

    /**
     * @brief Pauses the state.
     * 
     * This method is called when the state is paused.
     * It can be overridden to implement custom behavior when the state is paused.
     */
    virtual void Pause() {};

    /**
     * @brief Resumes the state.
     * 
     * This method is called when the state is resumed after being paused.
     * It can be overridden to implement custom behavior when the state is resumed.
     */
    virtual void Resume() {};
};


#endif//A2_STATE_H
