//
// Created by Khalil Azaiez on 2024-03-20.
//

#ifndef A2_CHARACTERBUILDER_CPP_H
#define A2_CHARACTERBUILDER_CPP_H
#include "CharacterBuilder.h"
#include "Dice.h"

#endif//A2_CHARACTERBUILDER_CPP_H
void CharacterBuilder::applyLevelBasedHPIncrease(Character& character, int baseHP) {
    Dice dice;
    int conMod = character.calculateModifier(character.getAbilityScores(2)); // Assuming 2 is Constitution

    // Initial HP setup
    int hitPoints = baseHP + conMod;

    // Increment HP for each level beyond the first
    for (int level = 2; level <= character.getLevel(); ++level) {
        hitPoints += dice.roll("1d10") + conMod;
    }

    character.setHitPoints(hitPoints);
}

