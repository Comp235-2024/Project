/**
 * @file NonPlayerCharacter.h
 * @author Ricardo Raji Chahine 40234410
 *
 */

#ifndef A3_NONPLAYERCHARACTER_H
#define A3_NONPLAYERCHARACTER_H

#include "Character.h"
#include "Item.h"

class NonPlayerCharacter : public Character{
private:
    Item* item_in_hand;

public:
    virtual ~NonPlayerCharacter() {}

    //TODO: IMPLEMENT DEFAULT CONSTRUCTOR (IT WAS CAUSING A VTABLE ERROR)
    NonPlayerCharacter();

    NonPlayerCharacter(int health, int hit_points, int armor_class, int attack_bonus, int damage_bonus);

    void setItemInHand(Item* item);
    Item* getItemInHand();
};

class Skeleteon : public NonPlayerCharacter{
public:
    Skeleteon();
    Skeleteon(int health, int hit_points, int armor_class, int attack_bonus, int damage_bonus);
};

class Zombie : public NonPlayerCharacter{
public:
    Zombie();
    Zombie(int health, int hit_points, int armor_class, int attack_bonus, int damage_bonus);
};

class Devil : public NonPlayerCharacter{
public:
    Devil();
    Devil(int health, int hit_points, int armor_class, int attack);
};
#endif //A3_NONPLAYERCHARACTER_H
