#include "NonPlayerCharacter.h"

void NonPlayerCharacter::setItemInHand(Item* item) {
    this->item_in_hand = item;
}

Item* NonPlayerCharacter::getItemInHand() {
    return this->item_in_hand;
}
NonPlayerCharacter::NonPlayerCharacter(int health, int hit_points, int armor_class, int attack_bonus, int damage_bonus) {
    this->health = health;
    this->hitPoints = hit_points;
    this->armorClass = armor_class;
    this->attackBonus = attack_bonus;
    this->damageBonus = damage_bonus;
}
Ogre::Ogre(int health, int hit_points, int armor_class, int attack_bonus, int damage_bonus) : NonPlayerCharacter(health, hit_points, armor_class, attack_bonus, damage_bonus) {
    this->textureName = "ogre";
}

Ogre::Ogre() {
    this->health = 100;
    this->hitPoints = 100;
    this->armorClass = 15;
    this->attackBonus = 10;
    this->damageBonus = 10;
    this->textureName = "ogre";
}
