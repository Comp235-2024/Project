#ifndef A3_OBSERVABLE_H
#define A3_OBSERVABLE_H

#include "Observer.h"
#include <list>
using namespace std;

class Observer;

/**
 * @class Observable
 * @brief The Observable class represents an object that can be observed by multiple observers.
 * 
 * The Observable class provides functionality to attach, detach, and notify observers.
 * Observers can register themselves with an Observable object to receive notifications when the object's state changes.
 */
class Observable {
public:
    /**
     * @brief Constructs an Observable object.
     */
    Observable();

    /**
     * @brief Destroys the Observable object.
     */
    virtual ~Observable() = 0;

    /**
     * @brief Attaches an observer to the Observable object.
     * 
     * @param observer A pointer to the observer object to be attached.
     */
    virtual void attach(Observer *observer);

    /**
     * @brief Detaches an observer from the Observable object.
     * 
     * @param observer A pointer to the observer object to be detached.
     */
    virtual void detach(Observer *observer);

    /**
     * @brief Notifies all attached observers about a state change in the Observable object.
     */
    virtual void notify() const;

protected:
    list<Observer*> *observers; /**< A list of pointers to the attached observers. */
};


#endif
