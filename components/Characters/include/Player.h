#ifndef A3_PLAYER_H
#define A3_PLAYER_H

#include "../../Items/include/Item.h"
#include "Character.h"
#include "../../ItemContainers/include/Backpack.h"
#include "../../ItemContainers/include/WornItems.h"

class Player : public Character{
private:
    Backpack backpack;

    //TODO SOME CONFIGURATION FOR WORNITEMS INSTEAD OF HAVING ITEM IN HAND
    WornItemsContainer wornItems;

    Item* item_in_hand;

public:
    ~Player() override=default;

    Player();



    //TODO STANDARDIZED THIS METHOD (SEE DEFINITION) IT NOW ASSUMES THAT THE ITEM IN HAND IS AT INDEX 3
    Item* getItemInHand();

    void setItemInHand(Item* item);

    Backpack getBackpack();

    WornItemsContainer getWornItems();

};


#endif //PLAYER_H
