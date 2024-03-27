//
// Created by Khalil Azaiez on 2024-03-19.
//
#include "TankBuilder.h"
#include "Dice.h"
#include "Character.h"


TankBuilder::TankBuilder() { character = new Character(); }
TankBuilder::~TankBuilder() { delete character; }

void TankBuilder::buildAbilityScores() {
    Dice dice;
    // Tank: Constitution, Dexterity, Strength, Intelligence, Charisma, Wisdom
    character->setConstitution(dice.roll4d6DropLowest());
    character->setDexterity(dice.roll4d6DropLowest());
    character->setStrength(dice.roll4d6DropLowest());
    character->setIntelligence(dice.roll4d6DropLowest());
    character->setCharisma(dice.roll4d6DropLowest());
    character->setWisdom(dice.roll4d6DropLowest());}
void TankBuilder::buildHitPoints(Character& character) {
    int baseHP = 15; // Tanks have the highest base HP
    this->applyLevelBasedHPIncrease(character, baseHP);
}


Character* TankBuilder::getCharacter() { return character; }