/**
 * @file StateMachine.h
 * @author Tymofiy Kovalenko
 * @date 17-Mar-2024
 * @brief
 */

#ifndef A2_STATEMACHINE_H
#define A2_STATEMACHINE_H

#include "Log/include/LogObservable.h"
#include "State.h"
#include <memory>
#include <stack>

using namespace std;

typedef unique_ptr<State> StateRef;

/**
 * @class StateMachine
 * @brief Represents a state machine that manages different states.
 * 
 * The StateMachine class is responsible for managing different states and transitioning between them.
 * It inherits from the LogObservable class.
 */
class StateMachine : public LogObservable{
public:
    /**
     * @brief Default constructor for the StateMachine class.
     */
    StateMachine()= default;

    /**
     * @brief Default destructor for the StateMachine class.
     */
    ~StateMachine() override= default;

    /**
     * @brief Adds a new state to the state machine.
     * @param newState The new state to be added.
     * @param isReplacing Flag indicating whether the current state should be replaced.
     * @param log Pointer to a LogObserver object for logging purposes.
     */
    void AddState(StateRef newState, bool isReplacing = true, LogObserver *log = nullptr);

    /**
     * @brief Removes the current state from the state machine.
     */
    void RemoveState();

    /**
     * @brief Processes any pending state changes in the state machine.
     */
    void ProcessStateChanges();

    /**
     * @brief Retrieves the active state of the state machine.
     * @return A reference to the active state.
     */
    StateRef &GetActiveState();

private:
    stack<StateRef> _states; /**< Stack of states managed by the state machine. */
    StateRef _newState; /**< The new state to be added. */

    bool _isRemoving{}; /**< Flag indicating whether a state is being removed. */
    bool _isAdding{}; /**< Flag indicating whether a state is being added. */
    bool _isReplacing{}; /**< Flag indicating whether the current state is being replaced. */
};


#endif//A2_STATEMACHINE_H
