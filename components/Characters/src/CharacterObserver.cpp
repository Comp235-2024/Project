/**
* @file CharacterObserver.cpp
*
* @author Melika Minaei Bidgoli
*
* @brief CharacterObserver class displays the character’s view when Character
* triggers the re-display of the character view each time a value is
* changed in the character's setters, using the observer pattern mechanism, by notifying
* CharacterObserver's update and draw.
*
* @version 0.1
*
* @date 2024-03-11
*
* @copyright Copyright (c) 2024
*/

#include "../include/CharacterObserver.h"

/**
 * Upon instantiation, attaches itself to a Character
 * and sets its pointer to Character attribute to the passed character
 * @param c character
 */
CharacterObserver::CharacterObserver(Character* c) {
    _character = c;
    _character->attach(this);
}

/**
 * Upon destruction, detaches itself from its Character
 */
CharacterObserver::~CharacterObserver() {
    _character->detach(this);
}

/**
 * redraw Character's info by calling draw()
 */
void CharacterObserver::update() {
    draw();
}

/**
 * Prints all the attributes' values of the character that it is observing
 */
void CharacterObserver::draw() {
    cout << endl << "---------------CHARACTER OBSERVER:-------------" <<endl;
    // Displaying the generated ability scores
    cout << "ABILITY SCORES: " << endl;
    cout << "Strength: " << _character->getAbilityScores(0) << ", "
         << "Dexterity: " << _character->getAbilityScores(1) << ", "
         << "Constitution: " << _character ->getAbilityScores(2) << endl;
    cout << "Intelligence :" << _character->getAbilityScores(3) << ", "
         << "Wisdom: " << _character->getAbilityScores(4) << ", "
         << "Charisma: " << _character->getAbilityScores(5) << endl;
    // Displaying the calculated ability modifiers
    cout << "ABILITY MODIFIERS: ";
    for (int i = 0; i < 6; i++) {
        cout << _character->getAbilityModifiers(i);
        if(i!=5) { // for putting comma after any elements but the last one
            cout << ", ";
        }
        else {
            cout << endl;
        }
    }
    // Displaying the calculated hit points
    cout << "HIT POINTS: " << _character->getHitPoints() << endl;
    // Displaying the calculated armor class
    cout << "ARMOR CLASS: " << _character->getArmorClass() << endl;
    // Displaying the calculated attack bonus
    cout << "ATTACK BONUS: " << _character->getAttackBonus() << endl;
    // Displaying the calculated damage bonus
    cout << "DAMAGE BONUS: " << _character->getDamageBonus() << endl;
    // Displaying the level
    cout << "LEVEL: " << _character->getLevel() << endl;
    cout << "------------END OF CHARACTER OBSERVER----------" << endl << endl;
}