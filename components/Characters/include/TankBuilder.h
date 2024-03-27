//
// Created by Khalil Azaiez on 2024-03-19.
//

#ifndef A2_TANKBUILDER_H
#define A2_TANKBUILDER_H

#include "Character.h"
#include "CharacterBuilder.h"

class TankBuilder : public CharacterBuilder, public Movable {
private:
    Character* character;
public:
    TankBuilder();
    ~TankBuilder();
    void buildAbilityScores() override;
    void buildHitPoints(Character& character) override;
    Character* getCharacter() override;
};
#endif//A2_TANKBUILDER_H
