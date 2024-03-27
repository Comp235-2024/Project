
//
// Created by Khalil Azaiez on 2024-03-19.
//

#ifndef A2_CHARACTERBUILDER_H
#define A2_CHARACTERBUILDER_H
#include "Character.h"

class CharacterBuilder {
public:
    virtual ~CharacterBuilder() = default;
    virtual void buildAbilityScores() = 0;
    virtual void buildHitPoints(Character& character) = 0;
    virtual Character* getCharacter() = 0;
    void applyLevelBasedHPIncrease(Character& character, int baseHP);
};

#endif//A2_CHARACTERBUILDER_H
