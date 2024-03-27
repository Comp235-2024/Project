/**
* @file character.h
* @date 25 february 2024, 11 March 2024
* @brief this file contains the declaration of the character class and related structures aliases
* @detail
* 1. The character is the main player of the game. Each character has a bunch of characteristics(attributes) and they can perform some actions as well(methods).
*     If the character's attributes gets updated, it will notify its CharacterObserver.
* 2. The design of the character class in two files: First is the .h file to define the attributes and .cpp to do the implementation of the methods which is the most basic design for each class. 
* 3. The libraries used are cstdlib for randomization of the ability score and iostream library for basic use of classes and functions.
*     Character is movable because it can move and observable because it is observed by the CharacterObserver.
*/

#ifndef A3_CHARACTER_H
#define A3_CHARACTER_H

#include "../../Items/include/Movable.h"
#include "../../Maps/include/Position.h"
#include "../../Log/include/LogObservable.h"
#include "Observable.h"
#include "SFML/Graphics.hpp"
#include <cstdlib>// For rand() and srand()
#include <ctime>  // For time()
#include <iostream>


class CharacterStrategy;
/**
 * @class Character
 * @brief Represents a character in a game.
 *
 * The Character class stores information about a character's ability scores,
 * hit points, armor class, attack bonus, damage bonus, and level. It also
 * provides methods to generate ability scores and calculate ability modifiers,
 * hit points, armor class, attack bonus, and damage bonus.
 */
class Character : public Movable,  public Observable{
public:
    /**
     * @brief Constructs a Character object with the specified level.
     *
     * @param level The level of the character.
     */
    // Constructor
    explicit Character(int level);
    Character();

    /**
     * @brief Shows a main menu to the user for testing by getting options
     * and input from the user. If the right format gets entered based on
     * the interactive menu options, it will call the character setters.
     * If the new values are different from the current values of the
     * attributes, they will get changed in the setters and notify the character observer.
     */
    void interactiveCharacterTest();

    /**
     * Shows a main menu for testing and updating the character attributes.
     */
    void showMainTestMenu();

    /**
     * Function to handle the ability scores testing from the user
     */
    void interactiveAbilityScoresTest();

    sf::Vector2f position;

    // Getters

    /**
     * Strategy Getter
     * @return strategy
     */

    CharacterStrategy* getStrategy() const;


    /**
     * health Getter
     * @return health
     */

    int getHealth() const;
    
    /**
     * Ability Scores Getter
     * @param index
     * @return  ability score-> 0: Strength, 1: Dexterity, 2: Constitution, 3:Intelligence, 4: Wisdom, 5: Charisma
     */
    int getAbilityScores(int index) const;
    void updateAttackBonuses();

    int getNumberOfAttacks() const;


    /**
     * Ability Modifiers Getter
     * @param index
     * @return ability modifier based on the index
     */
    int getAbilityModifiers(int index) const;

    /**
     * hit points Getter
     * @return hitpoints
     */
    int getHitPoints() const;

    /**
     * armor class Getter
     * @return armorClass
     */
    int getArmorClass() const;

    /**
     * attack bonus Getter
     * @return attackBonus
     */
    int getAttackBonus() const;

    /**
     * damage bonus Getter
     * @return damageBonus
     */
    int getDamageBonus() const;

    /**
     * level Getter
     * @return level
     */
    int getLevel() const;

    Position getLocation() const;


    // Setters

    /**
     * @brief Sets the strategy of the character.
     * @param strategy The strategy to set.
     */

    void setStrategy(CharacterStrategy* strategy);

    /**
     * health setter
     * Only changes and calls notify if it's different from the current attribute
     * @param health
     */
    void setHealth(int health);
    /**
     * strength setter in abilityScores array index 0
     * Only changes and calls notify if it's different from the current attribute
     * @param strength
     */
    void setStrength(int strength);

    /**
     * dexterity setter in abilityScores array index 1
     * Only changes and calls notify if it's different from the current attribute
     * @param dex
     */
    void setDexterity(int dex);

    /**
     * constitution setter in abilityScores array index 2
     * Only changes and calls notify if it's different from the current attribute
     * @param constitution
     */
    void setConstitution(int constitution);

    /**
     * intelligence setter in abilityScores array index 3
     * Only changes and calls notify if it's different from the current attribute
     * @param intelligence
     */
    void setIntelligence(int intelligence);

    /**
     * wisdom setter in abilityScores array index 4
     * Only changes and calls notify if it's different from the current attribute
     * @param wis
     */
    void setWisdom(int wis);

    /**
     * charisma setter in abilityScores array index 5
     * Only changes and calls notify if it's different from the current attribute
     * @param charisma
     */
    void setCharisma(int charisma);

    /**
     * abilityModifier setter based on the index, 0-5
     * Only changes and calls notify if it's different from the current attribute
     * @param index
     * @param amount
     */
    void setModifier(int index, int amount);

    /**
     * hitPoints setter
     * Only changes and calls notify if it's different from the current attribute
     * @param hitPoints
     */
    void setHitPoints(int hitPoints);

    /**
     * armorClass setter
     * Only changes and calls notify if it's different from the current attribute
     * @param armorClass
     */
    void setArmorClass(int armorClass);

    /**
     * attackBonus setter
     * Only changes and calls notify if it's different from the current attribute
     * @param attackBonus
     */
    void setAttackBonus(int attackBonus);

    /**
     * damageBonus setter
     * Only changes and calls notify if it's different from the current attribute
     * @param damageBonus
     */
    void setDamageBonus(int damageBonus);

    /**
     * level setter
     * Only changes and calls notify if it's different from the current attribute
     * @param level
     */
    void setLevel(int level);

    void setLocation(Position);


    int calculateModifier(int abilityScore);
    void levelUp();
    void updateAttacksPerRound();
    static void testCharacterCreation();
    static void displayCharacterStats(const Character& character);
    static void testLevelUpProcess();


private:

    CharacterStrategy* strategy;

    Position location;

    //TODO implement health logic
    int health;

    int abilityScores[6]; // 0: Strength, 1: Dexterity, 2: Constitution, 3:
                         // Intelligence, 4: Wisdom, 5: Charisma
    int abilityModifiers[6]{};
    int hitPoints;
    int armorClass{};
    int attackBonus;
    int damageBonus{};
    int numberOfAttacks; // Number of attacks per round
    int level;
    std::vector<int> additionalAttackBonuses;  // Holds additional attack bonuses.

    /**
     * @brief Generates random ability scores for the character.
     */
    void generateAbilityScores();

    /**
     * @brief Calculates the ability modifiers based on the ability scores.
     */
    void calculateAbilityModifiers();

    /**
     * @brief Calculates the hit points of the character.
     */
    void calculateHitPoints();

    /**
     * @brief Calculates the armor class of the character.
     */
    void calculateArmorClass();

    /**
     * @brief Calculates the attack bonus of the character.
     */
    void calculateAttackBonus();

    /**
     * @brief Calculates the damage bonus of the character.
     */
    void calculateDamageBonus();


};

#endif