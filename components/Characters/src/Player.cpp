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

Player::Player(int level, string TextureName):Character(level){
    item_in_hand = nullptr;
    textureName = TextureName;
}

Player Player::getPlayer(){
    return *this;
}

Backpack* Player::getBackpack() {
    return &backpack;
}

void Player::setBackpack(Backpack* backpack) {
    this->backpack = *backpack;
}

WornItemsContainer* Player::getWornItems() {
    return &wornItems;
}

void Player::setWornItems(WornItemsContainer* wornItems) {
    this->wornItems = *wornItems;
}

shared_ptr<Item> Player::getItemInHand() {
    return this->getBackpack()->getBackpackStorage()[2];
}

void Player::setItemInHand(shared_ptr<Item> item) {
    item_in_hand = item;
}


