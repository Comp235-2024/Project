#include "../include/Player.h"

Player::Player():Character(){
    item_in_hand = nullptr;

    Texture texture;
    if (!texture.loadFromFile("../../assets/images/frames/knight_m_idle_anim_f0.png")) {;
        throw std::invalid_argument("Player image not found");
    }

}

Player::Player(int level):Character(level){
    item_in_hand = nullptr;
}

Player Player::getPlayer(){
    return *this;
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

