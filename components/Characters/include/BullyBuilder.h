//
// Created by Khalil Azaiez on 2024-03-19.
//

#ifndef A2_BULLYBUILDER_H
#define A2_BULLYBUILDER_H
#include "Character.h"
#include "CharacterBuilder.h"

class BullyBuilder : public CharacterBuilder {
private:
    Character* character;
public:
    BullyBuilder();
    ~BullyBuilder();
    void buildAbilityScores() override;
    void buildHitPoints(Character& character) override;
    Character* getCharacter() override;
};

#endif//A2_BULLYBUILDER_H
