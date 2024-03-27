#include "Item.h"

#pragma region Item Class and the different types of items

#pragma region Initialization of Item class

/**
         * @brief Initializes the number of items to 0
         *
         */
int Item::ItemCount = 0;

/**
         * @brief Construct a new Item:: Item object with null values
         * @attention This conctructor increments the ItemCount and assigns the ItemID
         *
         */
Item::Item() {
    this->placed=false;
    ItemCount++;
    ItemID = ItemCount;
}

/**
         * @brief Construct a new Item:: Item object with a given name, type, enchantment type and level
         *
         * @param name
         * @param type
         * @param enchantment_type
         * @param enchantment_level
         */
Item& Item::operator=(const Item& other)
{
    this->name = other.name;
    this->type = other.type;
    this->enchantment_type = other.enchantment_type;
    this->enchantment_level = other.enchantment_level;
    return *this;
}

/**
         * @brief Returns a string representation of the item
         *
         * @return string
         */
string Item::toString() {

    string s = "\nName: " + name + "\nType: " + type +
               "\nEnchantment Type: " + enchantment_type +
               "\nEnchantment Level: " + to_string(enchantment_level)+"\n";
    return s;
}

/**
         * @brief Returns the name of the item
         *
         * @return string
         */
string Item::getName() const{ return this->name; }

/**
         * @brief Returns the type of the item
         *
         * @return string
         */
string Item::getType() const{ return this->type; }

/**
         * @brief Sets the name of the item
         *
         * @param name
         */
void Item::setName(string name) { this->name = name; }


/**
         * @brief Sets the type of the item
         *
         * @param type
         */
void Item::setEnchantmentType(string enchantment_type) {
    this->enchantment_type = enchantment_type;
}

/**
         * @brief Sets the enchantment level of the item
         *
         * @param enchantment_level
         */
void Item::setEnchantmentLevel(int enchantment_level) {
    this->enchantment_level = enchantment_level;
}

/**
         * @brief Returns the enchantment level of the item
         *
         * @return int
         */
int Item::getEnchantmentLevel() const{ return this->enchantment_level; }

/**
         * @brief Returns the enchantment type of the item
         *
         * @return string
         */
string Item::getEnchantmentType() const { return this->enchantment_type; }

/**
         * @brief Generates a random float number between 0 and 1
         *
         * @return float
         */
float Item::generateProbability() {

    return (static_cast<float>(rand()) / static_cast<float>(RAND_MAX));
}

/**
         * @brief Returns whether the item is placed in a container or not
         *
         * @return true
         * @return false
         */
bool Item::isPlaced() const { return this->placed; }

/**
         * @brief Returns the ID of the item
         *
         * @return int
         */
int Item::getItemID() const { return this->ItemID; }

int Item::getItemCount() { return ItemCount; }

// Add applyenchantment() to the Item class

#pragma endregion

#pragma endregion

