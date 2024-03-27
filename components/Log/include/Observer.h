/**
 * @file Observer.h
 * @author Tymofiy Kovalenko
 * @date 08-Mar-2024
 * @brief
 */


#ifndef A3_OBSERVER_H
#define A3_OBSERVER_H

#include "Observable.h"

class Observable;

/**
 * @class Observer
 * @brief The Observer class is an abstract base class that defines the interface for observers.
 * 
 * Observers are used in the Observer design pattern to receive updates from a subject when its state changes.
 * Any class that wants to be an observer should inherit from this class and implement the update() method.
 */
class Observer {
public:
    /**
     * @brief Destructor for the Observer class.
     */
    virtual ~Observer();

    /**
     * @brief This method is called by the subject to notify the observer of a state change.
     * 
     * The observer should implement this method to perform any necessary actions when it receives an update.
     */
    virtual void update() = 0;

protected:
    /**
     * @brief Default constructor for the Observer class.
     */
    Observer();
};


#endif//A3_OBSERVER_H
