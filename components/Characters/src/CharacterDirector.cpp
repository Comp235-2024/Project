//
// Created by Khalil Azaiez on 2024-03-19.
//
#include "CharacterDirector.h"
#include "Character.h"

void CharacterDirector::setBuilder(CharacterBuilder* b) { builder = b; }
Character* CharacterDirector::constructCharacter(Character& character, const std::string& fighterStyle) {
    // Example construction logic; adjust as needed
    builder->buildAbilityScores();
    builder->buildHitPoints(character);
    // Adjust as needed
    return builder->getCharacter();
}