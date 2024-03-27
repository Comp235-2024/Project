/**
 * @file LogObserver.h
 * @brief This file contains the declaration of the LogObserver class and the EnableModule struct.
 * 
 * The LogObserver class is a concrete implementation of the Observer interface. It is responsible for observing and logging messages.
 * The EnableModule struct is used to enable or disable different modules for logging.
 * 
 * @author Tymofiy Kovalenko
 * @date 21-Mar-2024
 */

#ifndef A3_LOGOBSERVER_H
#define A3_LOGOBSERVER_H

#include "Observer.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

/**
 * @brief Struct representing the enabled modules for logging.
 * 
 * This struct contains boolean flags for each module that can be enabled or disabled for logging.
 * The default state is that all modules are enabled.
 */
struct EnableModule {
    bool map; /**< Flag indicating whether the map module is enabled for logging. */
    bool character; /**< Flag indicating whether the character module is enabled for logging. */
    bool dice; /**< Flag indicating whether the dice module is enabled for logging. */
    bool system; /**< Flag indicating whether the system module is enabled for logging. */

    /**
     * @brief Default constructor.
     * 
     * Initializes all module flags to true (enabled).
     */
    EnableModule() {
        map = true;
        character = true;
        dice = true;
        system = true;
    }

    /**
     * @brief Enables all modules.
     * 
     * Sets all module flags to true (enabled).
     */
    void enableAll() {
        map = true;
        character = true;
        dice = true;
        system = true;
    }

    /**
     * @brief Disables all modules.
     * 
     * Sets all module flags to false (disabled).
     */
    void disableAll() {
        map = false;
        character = false;
        dice = false;
        system = false;
    }
};

class LogObserver : public Observer {

public:
    /**
     * @brief Updates the LogObserver with a new message.
     * @param message The message to be logged.
     */
    void update(const string& message);

    /**
     * @brief Updates the LogObserver.
     * This function is called when there is no specific message to be logged.
     */
    void update() override;

    EnableModule enabledModules; /**< The enabled modules for logging. */

    /**
     * @brief Constructs a LogObserver object with the specified filename.
     * @param filename The name of the log file.
     */
    explicit LogObserver(const string &filename);

private:
    ofstream log; /**< The log file stream. */

    /**
     * @brief Writes a message to the log file.
     * @param message The message to be written.
     */
    void write(const string& message);

};

#endif//A3_LOGOBSERVER_H
