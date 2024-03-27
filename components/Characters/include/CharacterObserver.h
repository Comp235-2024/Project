/**
* @file CharacterObserver.h
* @author Melika Minaei Bidgoli
* @date 11 March 2024
* @brief This file contains the declaration of the CharacterObserver class.
* @details
* 1. Character Observer inherits the Observer class to observe the character
* 2. The design of the CharacterObserver is:
*   It has a pointer to character attribute
*   Upon instantiation, it attaches itself to a Character
*   Upon destruction, it detaches itself from its Character
*   Upon Update, it will draw the Character, by printing all of its attributes.
* 3. The libraries used in this file are iostream for printing,
*   and uses Character and Observer header files.
*/

#ifndef A3_CHARACTEROBSERVER_H
#define A3_CHARACTEROBSERVER_H

#include "Character.h"
#include "Observer.h"
#include <iostream>
using namespace std;

class CharacterObserver : public Observer {
public:
    /**
     * Upon instantiation, attaches itself to a Character
     * and sets its pointer to Character attribute to the passed character
     * @param c character
     */
    CharacterObserver(Character *character);

    /**
     * Upon destruction, detaches itself from its Character
     */
    ~CharacterObserver() override;

    /**
     * redraw Character's info by calling draw()
     */
    void update() override;

    /**
     * Prints all the attributes' values of the character that it is observing
     */
    void draw();

private:

    Character *_character;
};


#endif//A3_CHARACTEROBSERVER_H