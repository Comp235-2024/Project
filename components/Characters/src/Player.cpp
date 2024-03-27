#include "../include/Player.h"

Player::Player():Character(){
    item_in_hand = nullptr;
}
Backpack Player::getBackpack() {
    return backpack;
}

WornItemsContainer Player::getWornItems() {
    return wornItems;
}

Item* Player::getItemInHand() {
    return this->getBackpack().getBackpackStorage()[2];
}

void Player::setItemInHand(Item* item) {
    item_in_hand = item;
}

