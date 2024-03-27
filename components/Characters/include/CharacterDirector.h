//
// Created by Khalil Azaiez on 2024-03-19.
//

#ifndef A2_CHARACTERDIRECTOR_H
#define A2_CHARACTERDIRECTOR_H

#include "CharacterBuilder.h"
class CharacterDirector {
private:
    CharacterBuilder* builder;
public:
    void setBuilder(CharacterBuilder* b);
    Character* constructCharacter(Character& character, const std::string& fighterStyle);
};

#endif//A2_CHARACTERDIRECTOR_H
