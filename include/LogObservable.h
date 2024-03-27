/**
 * @file LogObservable.h
 * @brief This file contains the declaration of the LogObservable class.
 * @author Tymofiy Kovalenko
 * @date 21-Mar-2024
 */

#ifndef A3_LOGOBSERVABLE_H
#define A3_LOGOBSERVABLE_H

#include "Observable.h"
#include <string>
#include "../include/LogObserver.h"

class LogObserver;

/**
 * @class LogObservable
 * @brief The LogObservable class is responsible for notifying its observers about log events.
 *        It inherits from the Observable class.
 */
class LogObservable : public Observable{
public:
    /**
     * @brief Default constructor for LogObservable.
     */
    LogObservable();

    /**
     * @brief Destructor for LogObservable.
     */
    ~LogObservable() override;

    /**
     * @brief Notifies the observers with a log message and an optional module name.
     * @param message The log message to be notified.
     * @param module The module name associated with the log message (default is "Map").
     */
    void notify(const std::string &message, string module = "Map") const;

    /**
     * @brief Notifies the observers without any message.
     *        This function overrides the notify() function in the base class.
     */
    void notify() const override{Observable::notify();}

    /**
     * @brief Attaches a LogObserver to the LogObservable.
     * @param observer The LogObserver to be attached.
     */
    void attach(LogObserver *observer);

    /**
     * @brief Attaches an Observer to the LogObservable.
     *        This function overrides the attach() function in the base class.
     * @param observer The Observer to be attached.
     */
    void attach(Observer *observer) override{Observable::attach(observer);}

    /**
     * @brief Detaches a LogObserver from the LogObservable.
     * @param observer The LogObserver to be detached.
     */
    void detach(LogObserver *observer);

    /**
     * @brief Detaches an Observer from the LogObservable.
     *        This function overrides the detach() function in the base class.
     * @param observer The Observer to be detached.
     */
    void detach(Observer *observer) override{Observable::detach(observer);}

private:
    std::list<LogObserver*> *logObservers{}; /**< The list of LogObservers attached to the LogObservable. */
};

#endif//A3_LOGOBSERVABLE_H
