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

    shared_ptr<Item> item_in_hand;

public:
    std::string textureName = "knight";

    ~Player() override=default;

    Player();

    explicit Player(int level);

    Player(int level, string TextureName);

    Player getPlayer();

    //TODO STANDARDIZED THIS METHOD (SEE DEFINITION) IT NOW ASSUMES THAT THE ITEM IN HAND IS AT INDEX 3
    shared_ptr<Item> getItemInHand();

    void setItemInHand(shared_ptr<Item> item);

    Backpack* getBackpack();

    void setBackpack(Backpack* backpack);

    WornItemsContainer* getWornItems();

    void setWornItems(WornItemsContainer* wornItems);

};


#endif //PLAYER_H
