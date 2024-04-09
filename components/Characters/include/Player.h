#ifndef A3_PLAYER_H
#define A3_PLAYER_H

#include "../../Items/include/Item.h"
#include "Character.h"
#include "Backpack.h"
#include "WornItems.h"


class Player : public Character{
private:
    Backpack backpack;

    //TODO SOME CONFIGURATION FOR WORNITEMS INSTEAD OF HAVING ITEM IN HAND
    WornItemsContainer wornItems;

    Item* item_in_hand;

public:
    std::string textureName = "knight";

    ~Player() override=default;

    Player();

    explicit Player(int level);

    Player(int level, string TextureName);

    Player getPlayer();

    //TODO STANDARDIZED THIS METHOD (SEE DEFINITION) IT NOW ASSUMES THAT THE ITEM IN HAND IS AT INDEX 3
    Item* getItemInHand();

    void setItemInHand(Item* item);

    Backpack* getBackpack();

    WornItemsContainer* getWornItems();

};


#endif //PLAYER_H
