//
// Created by Khalil Azaiez on 2024-03-19.
//

#include "BullyBuilder.h"
#include "Dice.h"

// BullyBuilder implementation
BullyBuilder::BullyBuilder() { character = new Character(); }
BullyBuilder::~BullyBuilder() { delete character; }
void BullyBuilder::buildAbilityScores() {
    Dice dice;
    // Use the new method for generating ability scores according to the D&D rule
    character->setStrength(dice.roll4d6DropLowest());
    character->setConstitution(dice.roll4d6DropLowest());
    character->setDexterity(dice.roll4d6DropLowest());
    character->setIntelligence(dice.roll4d6DropLowest());
    character->setCharisma(dice.roll4d6DropLowest());
    character->setWisdom(dice.roll4d6DropLowest());}
void BullyBuilder::buildHitPoints(Character& character) {
    int baseHP = 12; // Example: Bully characters start with a higher base HP
    this->applyLevelBasedHPIncrease(character, baseHP);
}

Character* BullyBuilder::getCharacter() { return character; }
