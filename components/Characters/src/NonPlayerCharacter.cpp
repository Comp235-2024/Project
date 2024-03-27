#include "NonPlayerCharacter.h"

void NonPlayerCharacter::setItemInHand(Item* item) {
    this->item_in_hand = item;
}

Item* NonPlayerCharacter::getItemInHand() {
    return this->item_in_hand;
}

