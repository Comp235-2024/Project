/**
 * @file StateMachine.cpp
 * @author Tymofiy Kovalenko
 * @date 17-Mar-2024
 * @brief
 */

#include "StateMachine.h"

void StateMachine::AddState(StateRef newState, bool isReplacing, LogObserver *log) {
    _isAdding = true;
    _isReplacing = isReplacing;

    _newState = std::move(newState);
    _newState->attach(log);
    this->notify("Log attached to new state", "System");
    this->notify("New state added", "System");
}

void StateMachine::RemoveState() {
    _isRemoving = true;
}


void StateMachine::ProcessStateChanges() {
    if (_isRemoving && !_states.empty()) {
        _states.pop();
        if (!_states.empty()) {
            _states.top()->Resume();
        }
        _isRemoving = false;
    } else if (_isAdding) {
        if (!_states.empty()) {
            if (_isReplacing) {
                _states.pop();
                _isReplacing = false;
                this->notify("State replaced", "System");
            } else {
                _states.top()->Pause();
                this->notify("State paused", "System");
            }
        }
        this->notify("State activated", "System");
        _states.push(std::move (_newState));

        _states.top()->Init();
        _isAdding = false;
    }

}

StateRef &StateMachine::GetActiveState() {
    return _states.top();
}
