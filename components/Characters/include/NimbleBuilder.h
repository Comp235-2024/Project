//
// Created by Khalil Azaiez on 2024-03-19.
//

#ifndef A2_NIMBLEBUILDER_H
#define A2_NIMBLEBUILDER_H
#include "Character.h"
#include "CharacterBuilder.h"

class NimbleBuilder : public CharacterBuilder, public Movable{
private:
    Character* character;
public:
    NimbleBuilder();
    ~NimbleBuilder();
    void buildAbilityScores() override;
    void buildHitPoints(Character& character) override;
    Character* getCharacter() override;
};

#endif//A2_NIMBLEBUILDER_H
