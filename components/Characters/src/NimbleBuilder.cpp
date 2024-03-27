//
// Created by Khalil Azaiez on 2024-03-19.
//
#include "NimbleBuilder.h"
#include "Dice.h"

NimbleBuilder::NimbleBuilder() { character = new Character(); }
NimbleBuilder::~NimbleBuilder() { delete character; }

void NimbleBuilder::buildAbilityScores() {
    Dice dice;
    // Nimble: Dexterity, Constitution, Strength, Intelligence, Charisma, Wisdom
    character->setDexterity(dice.roll4d6DropLowest());
    character->setConstitution(dice.roll4d6DropLowest());
    character->setStrength(dice.roll4d6DropLowest());
    character->setIntelligence(dice.roll4d6DropLowest());
    character->setCharisma(dice.roll4d6DropLowest());
    character->setWisdom(dice.roll4d6DropLowest());}
void NimbleBuilder::buildHitPoints(Character& character) {
    int baseHP = 8; // Nimble might have lower base HP due to their reliance on evasion
    this->applyLevelBasedHPIncrease(character, baseHP);
}
Character* NimbleBuilder::getCharacter() { return character; }
