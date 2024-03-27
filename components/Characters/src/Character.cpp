#include "../include/Character.h"
#include "BullyBuilder.h"
#include "NimbleBuilder.h"
#include "TankBuilder.h"
#include "dice.h"
#include <iostream>

Character::Character(){
health = 100;
location = Position(0,0);
strategy = nullptr;

hitPoints=5;
armorClass=5;
attackBonus=5;
damageBonus=5;
level=5;
for(int i=0;i<6;i++){
    abilityScores[i]=5;
    abilityModifiers[i]=5;}


}
/**
 * @brief Constructs a Character object with the specified level.
 *
 * This constructor initializes a Character object with the given level.
 * It generates ability scores, calculates ability modifiers, hit points,
 * armor class, attack bonus, and damage bonus for the character.
 *
 * @param level The level of the character.
 */
Character::Character(int level) : level(1), hitPoints(10), attackBonus(0), numberOfAttacks(1) {
    generateAbilityScores();
    calculateAbilityModifiers();
    calculateHitPoints();
    calculateArmorClass();
    calculateAttackBonus();
    calculateDamageBonus();
}


/**
 * @brief Generates random ability scores for the character.
 */
void Character::generateAbilityScores() {
    for (int& score : abilityScores) {
        score = (rand() % 16) + 3; // Random scores between 3 and 18
    }
}


int Character::calculateModifier(int abilityScore) {
    return (abilityScore - 10) / 2;
}

/**
 * @brief Calculates the ability modifiers based on the ability scores.
 */
void Character::calculateAbilityModifiers() {
    for (int i = 0; i < 6; i++) {
        abilityModifiers[i] = (abilityScores[i] - 10) / 2;
    }
}

/**
 * @brief Calculates the hit points of the character.
 */
void Character::calculateHitPoints() {
    hitPoints = 1; // Base HP + Constitution modifier
}

/**
 * @brief Calculates the armor class of the character.
 */
void Character::calculateArmorClass() {
    armorClass = 10 + abilityModifiers[1]; // 10 + Dexterity modifier
}

/**
 * @brief Calculates the attack bonus of the character.
 */
void Character::calculateAttackBonus() {
    attackBonus = level + abilityModifiers[0]; // Level + Strength modifier
}

/**
 * @brief Calculates the damage bonus of the character.
 */
void Character::calculateDamageBonus() {
    damageBonus = abilityModifiers[0]; // Strength modifier
}

// Getters
/**
 * Ability Scores Getter
 * @param index
 * @return  ability score-> 0: Strength, 1: Dexterity, 2: Constitution, 3:Intelligence, 4: Wisdom, 5: Charisma
 */
int Character::getAbilityScores(int index) const{
    return abilityScores[index];
}

int Character::getNumberOfAttacks()const{
    return numberOfAttacks;
}

/**
 * Ability Modifiers Getter
 * @param index
 * @return ability modifier based on the index
 */
int Character::getAbilityModifiers(int index) const{
    return abilityModifiers[index];
}

/**
 * hit points Getter
 * @return hitpoints
 */
int Character::getHitPoints() const{
    return hitPoints;
}

/**
 * armor class Getter
 * @return armorClass
 */
int Character::getArmorClass() const{
    return armorClass;
}

/**
 * attack bonus Getter
 * @return attackBonus
 */
int Character::getAttackBonus() const{
    return attackBonus;
}

/**
 * damage bonus Getter
 * @return damageBonus
 */
int Character::getDamageBonus() const{
    return damageBonus;
}

/**
 * level Getter
 * @return level
 */
int Character::getLevel() const{
    return level;
}

Position Character::getLocation() const {
    return this->location;
}

int Character::getHealth() const{
    return this->health;
}

CharacterStrategy* Character::getStrategy() const{
    return this->strategy;
}


// Setters, change and notify observers only if the new attribute is different

void Character::setLocation(Position new_location){
    if(this->location.x != new_location.x || this->location.y != new_location.y) {
        this->location = new_location;
        notify();
    }
}

void Character::setHealth(int health){
    if(this->health != health) {
        this->health = health;
        notify();
    }
}

void Character::setStrategy(CharacterStrategy* new_strategy){
    if(this->strategy != new_strategy) {
        this->strategy = new_strategy;
        notify();
    }
}

/**
 * strength setter in abilityScores array index 0
 * Only changes and calls notify if it's different from the current attribute
 * @param strength
 */
void Character::setStrength(int strength){
    if(this->abilityScores[0] != strength) {
        this->abilityScores[0] = strength;
        notify();
    }
}

/**
 * dexterity setter in abilityScores array index 1
 * Only changes and calls notify if it's different from the current attribute
 * @param dex
 */
void Character::setDexterity(int dex){
    if(this->abilityScores[1] != dex) {
        this->abilityScores[1] = dex;
        notify();
    }
}

/**
 * constitution setter in abilityScores array index 2
 * Only changes and calls notify if it's different from the current attribute
 * @param constitution
 */
void Character::setConstitution(int constitution) {
    if(this->abilityScores[2] != constitution) {
        this->abilityScores[2] = constitution;
        notify();
    }
}

/**
 * intelligence setter in abilityScores array index 3
 * Only changes and calls notify if it's different from the current attribute
 * @param intelligence
 */
void Character::setIntelligence(int intelligence) {
    if(this->abilityScores[3] != intelligence) {
        this->abilityScores[3] = intelligence;
        notify();
    }
}

/**
 * wisdom setter in abilityScores array index 4
 * Only changes and calls notify if it's different from the current attribute
 * @param wis
 */
void Character::setWisdom(int wis) {
    if(this->abilityScores[4] != wis) {
        this->abilityScores[4] = wis;
        notify();
    }
}

/**
 * charisma setter in abilityScores array index 5
 * Only changes and calls notify if it's different from the current attribute
 * @param charisma
 */
void Character::setCharisma(int charisma) {
    if(this->abilityScores[5] != charisma) {
        this->abilityScores[5] = charisma;
        notify();
    }
}

/**
 * abilityModifier setter based on the index, 0-5
 * Only changes and calls notify if it's different from the current attribute
 * @param index
 * @param amount
 */
void Character::setModifier(int index, int amount) {
    if(this->abilityModifiers[index] != amount) {
        this->abilityModifiers[index] = amount;
        notify();
    }
}

/**
 * hitPoints setter
 * Only changes and calls notify if it's different from the current attribute
 * @param hitPoints
 */
void Character::setHitPoints(int hitPoints) {
    if(this->hitPoints != hitPoints) {
        this->hitPoints = hitPoints;
        notify();
    }
}

/**
 * armorClass setter
 * Only changes and calls notify if it's different from the current attribute
 * @param armorClass
 */
void Character::setArmorClass(int armorClass) {
    if(this->armorClass != armorClass) {
        this->armorClass = armorClass;
        notify();
    }
}

/**
 * attackBonus setter
 * Only changes and calls notify if it's different from the current attribute
 * @param attackBonus
 */
void Character::setAttackBonus(int attackBonus) {
    if(this->attackBonus != attackBonus) {
        this->attackBonus = attackBonus;
        notify();
    }
}

/**
 * damageBonus setter
 * Only changes and calls notify if it's different from the current attribute
 * @param damageBonus
 */
void Character::setDamageBonus(int damageBonus) {
    if(this->damageBonus != damageBonus) {
        this->damageBonus = damageBonus;
        notify();
    }
}

/**
 * level setter
 * Only changes and calls notify if it's different from the current attribute
 * @param level
 */
void Character::setLevel(int level) {
    if(this->level != level) {
        this->level = level;
        notify();
    }
}


/**
 * Shows a main menu for testing and updating the character attributes.
 */
void Character::showMainTestMenu() {
    cout << "---------------------------------------------------------------" << endl;
    cout << "|      WELCOME TO THE INTERACTIVE CHARACTER TESTING MENU!     |" << endl;
    cout << "|   Please choose an option(number) from the options below:   |" << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << "|          0. Exit the interactive character testing.         |" << endl;
    cout << "|          1. Change ability scores of the character.         |" << endl;
    cout << "|          2. Change ability modifiers of the character.      |" << endl;
    cout << "|          3. Change hit points of the character.             |" << endl;
    cout << "|          4. Change the armor class of the character.        |" << endl;
    cout << "|          5. Change the attack bonus of the character.       |" << endl;
    cout << "|          6. Change the damage bonus of the character.       |" << endl;
    cout << "|          7. Change the level of the character.              |" << endl;
    cout << "---------------------------------------------------------------" << endl;
    cout << "Your option: " << endl;
}

/**
 * Function to handle the ability scores testing from the user
 */
void Character::interactiveAbilityScoresTest() {
    int input = 0;
    int abilityOption = 0;
    cout << "PLEASE ENTER THE ABILITY YOU WANT TO CHANGE FROM OPTIONS BELOW(NUMBER):" << endl;
    cout << "1: Strength, 2: Dexterity, 3: Constitution" << endl;
    cout << "4: Intelligence, 5: Wisdom, 6: Charisma" << endl;
    cout << "ENTER THE CHOSEN ABILITY: " << endl;
    cin >> abilityOption;
    if(abilityOption < 7 && abilityOption > 0) {
        cout << "PLEASE ENTER THE NEW AMOUNT OF THE ABILITY: " << endl;
        cin >> input;
        if(abilityOption == 1) {
            setStrength(input);
        }
        else if(abilityOption == 2) {
            setDexterity(input);
        }
        else if(abilityOption == 3) {
            setConstitution(input);
        }
        else if(abilityOption == 4) {
            setIntelligence(input);
        }
        else if(abilityOption == 5) {
            setWisdom(input);
        }
        else{
            setCharisma(input);
        }
    }
    else {
        cout << "WRONG CHOICE OF ABILITY! YOU CAN CHOOSE BETWEEN 1-6!" << endl;
    }
}

/**
 * @brief Shows a main menu to the user for testing by getting options
 * and input from the user. If the right format gets entered based on
 * the interactive menu options, it will call the character setters.
 * If the new values are different from the current values of the
 * attributes, they will get changed in the setters and notify the character observer.
 */
void Character::interactiveCharacterTest() {
    string userOption = "0";
    do {
        showMainTestMenu();
        cin >> userOption;
        int input;
        if(userOption == "1") {
            interactiveAbilityScoresTest();
        }
        else if(userOption == "2") {
            int index = 0;
            cout << "PLEASE ENTER THE INDEX OF THE ABILITY MODIFIER(0, 1, 2, 3, 4, or 5): " << endl;
            cin >> index;
            cout << "PLEASE ENTER THE NEW AMOUNT OF THAT ABILITY MODIFIER: " << endl;
            cin >> input;
            setModifier(index, input);
        }
        else if(userOption == "3") {
            cout << "PLEASE ENTER THE NEW HIT POINTS: " << endl;
            cin >> input;
            setHitPoints(input);
        }
        else if(userOption == "4") {
            cout << "PLEASE ENTER THE NEW ARMOR CLASS: " << endl;
            cin >> input;
            setArmorClass(input);
        }
        else if(userOption == "5") {
            cout << "PLEASE ENTER THE NEW ATTACK BONUS: " << endl;
            cin >> input;
            setAttackBonus(input);
        }
        else if(userOption == "6") {
            cout << "PLEASE ENTER THE NEW DAMAGE BONUS: " << endl;
            cin >> input;
            setDamageBonus(input);
        }
        else if(userOption == "7") {
            cout << "PLEASE ENTER THE NEW LEVEL: " << endl;
            cin >> input;
            setLevel(input);
        }
        else {// even if the user enters a wrong option choice it will exit the character testing menu
            userOption = "0";
        }
    }while(userOption != "0");
    cout << "---------------------------------------------------------------" << endl;
    cout << "|      YOU EXITED THE INTERACTIVE CHARACTER TESTING MENU!     |" << endl;
    cout << "---------------------------------------------------------------" << endl;
}

void Character::updateAttacksPerRound() {
    // Reset to 1 attack per round as base
    // Every character starts with 1 attack per round
    numberOfAttacks = 1;

    if (level > 5) {
        // Calculate extra attacks based on level, starting from level 6
        for (int extraLevel = 6; extraLevel <= level; extraLevel += 5) {
            numberOfAttacks += 1;
        }
    }
}

void Character::updateAttackBonuses() {
    // Clear previous bonus attacks
    additionalAttackBonuses.clear();

    // Level 6 or higher gets an additional attack at a lower bonus
    if (level >= 6) {
        additionalAttackBonuses.push_back(level / 6); // +1 attack bonus for levels 6-10, +2 for 11-15, and so on
    }

    // Levels 11, 16, etc., get further additional attacks
    if (level >= 11) {
        additionalAttackBonuses.push_back(level / 11); // +1 attack bonus for levels 11-15, +2 for 16-20, and so on
    }

    if (level >= 16) {
        additionalAttackBonuses.push_back(level / 16); // +1 attack bonus for levels 11-15, +2 for 16-20, and so on
    }
}

void Character::levelUp() {
    Dice dice;
    level += 1;

    // Update hit points
    int conMod = calculateModifier(getAbilityScores(3)); // Assuming 2 is Constitution
    if (level <= 5) {
        hitPoints += level; // Levels 1-5 increase by the level number
    } else {
        // From level 6 onwards, follow the pattern described
        hitPoints += level; // Base increase by level number
        if (level >= 6 && level <= 10) {
            hitPoints += conMod; // Levels 6-10 add constitution modifier
        } else if (level >= 11) {
            // Levels 11+ add cumulative bonuses from the table
            int cumulativeBonus = (level - 1) / 5; // Calculate the number of 5-level tiers below the current level
            hitPoints += (cumulativeBonus * 5) + conMod;
        }
        // Note: This needs adjustment to match your exact hit point calculation rules.
    }

    // Increase attack bonus by one
    attackBonus += 1;

    // Update number of attacks per round if level is a multiple of 5
    if (level % 5 == 0) {
        numberOfAttacks += 1;
    }

    // Call the function to calculate the attack bonus based on the level.
    updateAttackBonuses();

    // Update number of attacks per round
    updateAttacksPerRound();
    }


 void Character::testCharacterCreation() {
    // Instantiate builders
    BullyBuilder bullyBuilder;
    NimbleBuilder nimbleBuilder;
    TankBuilder tankBuilder;

    // Use builders to create and configure characters
    Character* bully = bullyBuilder.getCharacter();
    bullyBuilder.buildAbilityScores();
    bullyBuilder.buildHitPoints(*bully); // Adjusted to pass character by reference

    Character* nimble = nimbleBuilder.getCharacter();
    nimbleBuilder.buildAbilityScores();
    nimbleBuilder.buildHitPoints(*nimble); // Similar adjustments for nimble

    Character* tank = tankBuilder.getCharacter();
    tankBuilder.buildAbilityScores();
    tankBuilder.buildHitPoints(*tank); // Similar adjustments for tank

    // Display stats for each character
    std::cout << "Bully Character Stats:\n";
    Character::displayCharacterStats(*bully); // Adjusted to dereference pointer

    std::cout << "\nNimble Character Stats:\n";
    Character::displayCharacterStats(*nimble); // Adjusted to dereference pointer

    std::cout << "\nTank Character Stats:\n";
    Character::displayCharacterStats(*tank); // Adjusted to dereference pointer

    // Cleanup
    delete bully;
    delete nimble;
    delete tank;
}

 void Character::displayCharacterStats(const Character& character) {
    // Implement based on your Character class's attributes
    // Example:
    std::cout << "Level: " << character.getLevel() << "\n"
              << "Hit Points: " << character.getHitPoints() << "\n"
              // Further stats as needed
              << std::endl;
}

void displayCharacterAttributes(const Character& character) {
    std::cout << "Level: " << character.getLevel() << ", Hit Points: " << character.getHitPoints()
              << ", Armor Class: " << character.getArmorClass() << ", Attack Bonus: " << character.getAttackBonus()
              << ", Damage Bonus: " << character.getDamageBonus() << ", Number of Attacks: " << character.getNumberOfAttacks() << std::endl;
}


 void Character::testLevelUpProcess() {
     BullyBuilder bullyBuilder;
     NimbleBuilder nimbleBuilder;
     TankBuilder tankBuilder;

     Character bully(1), nimble(1), tank(1);

     bully.setStrength(10); bully.setConstitution(10); bully.setDexterity(10);
     nimble.setDexterity(10); nimble.setConstitution(10); nimble.setStrength(10);
     tank.setConstitution(10); tank.setDexterity(10); tank.setStrength(10);

     bullyBuilder.buildAbilityScores();
     bullyBuilder.buildHitPoints(bully);

     nimbleBuilder.buildAbilityScores();
     nimbleBuilder.buildHitPoints(nimble);

     tankBuilder.buildAbilityScores();
     tankBuilder.buildHitPoints(tank);

     // Display initial attributes
     std::cout << "Initial Bully Attributes: ";
     displayCharacterAttributes(bully);

     std::cout << "Initial Nimble Attributes: ";
     displayCharacterAttributes(nimble);

     std::cout << "Initial Tank Attributes: ";
     displayCharacterAttributes(tank);

     // Level up
     bully.levelUp();
     nimble.levelUp();
     tank.levelUp();

     // Display attributes after leveling up
     std::cout << "\nBully Attributes After Leveling Up: ";
     displayCharacterAttributes(bully);

     std::cout << "Nimble Attributes After Leveling Up: ";
     displayCharacterAttributes(nimble);

     std::cout << "Tank Attributes After Leveling Up: ";
     displayCharacterAttributes(tank);

     bully.levelUp();
     nimble.levelUp();
     tank.levelUp();

     // Display attributes after leveling up
     std::cout << "\nBully Attributes After Leveling Up: ";
     displayCharacterAttributes(bully);

     std::cout << "Nimble Attributes After Leveling Up: ";
     displayCharacterAttributes(nimble);

     std::cout << "Tank Attributes After Leveling Up: ";
     displayCharacterAttributes(tank);

     bully.levelUp();
     nimble.levelUp();
     tank.levelUp();

     // Display attributes after leveling up
     std::cout << "\nBully Attributes After Leveling Up: ";
     displayCharacterAttributes(bully);

     std::cout << "Nimble Attributes After Leveling Up: ";
     displayCharacterAttributes(nimble);

     std::cout << "Tank Attributes After Leveling Up: ";
     displayCharacterAttributes(tank);

     bully.levelUp();
     nimble.levelUp();
     tank.levelUp();

     // Display attributes after leveling up
     std::cout << "\nBully Attributes After Leveling Up: ";
     displayCharacterAttributes(bully);

     std::cout << "Nimble Attributes After Leveling Up: ";
     displayCharacterAttributes(nimble);

     std::cout << "Tank Attributes After Leveling Up: ";
     displayCharacterAttributes(tank);

     bully.levelUp();
     nimble.levelUp();
     tank.levelUp();

     // Display attributes after leveling up
     std::cout << "\nBully Attributes After Leveling Up: ";
     displayCharacterAttributes(bully);

     std::cout << "Nimble Attributes After Leveling Up: ";
     displayCharacterAttributes(nimble);

     std::cout << "Tank Attributes After Leveling Up: ";
     displayCharacterAttributes(tank);

     bully.levelUp();
     nimble.levelUp();
     tank.levelUp();

     // Display attributes after leveling up
     std::cout << "\nBully Attributes After Leveling Up: ";
     displayCharacterAttributes(bully);

     std::cout << "Nimble Attributes After Leveling Up: ";
     displayCharacterAttributes(nimble);

     std::cout << "Tank Attributes After Leveling Up: ";
     displayCharacterAttributes(tank);
}



