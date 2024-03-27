#include "Shield.h"

#pragma region Initialization of Shield class

/**
         * @brief Initializes the echantment types that a Shield can give
        */
const string Shield::enchantment_types[] = {"Armor Class"};

/**
         * @brief Construct a new Shield:: Shield object with null values
         *
         */
Shield::Shield() : Item() { type = "Shield"; }

/**
         * @brief Construct a new Shield:: Shield object with a given name, enchantment type and level
         *
         * @param name
         * @param enchantment_type
         * @param enchantment_level
         */
Shield::Shield(string name, string enchantment_type, int enchantment_level) {
    this->name = name;
    this->type = "Shield";
    this->enchantment_type = enchantment_type;
    this->enchantment_level = enchantment_level;
}

/**
         * @brief Construct a new Shield:: Shield object with a given name, enchantment type and level
         *
         * @param other
         */
Shield::Shield(const Shield& other) : Item(other) {}

/**
         * @brief Overloads the assignment operator
         *
         * @param other
         * @return Shield&
         */
Shield& Shield::operator=(const Shield& other) {
    Item::operator=(other);
    return *this;
}

/**
         * @brief Returns a string representation of the shield
         *
         * @return string
         */
string Shield::toString() {
    string s = "\nName: " + name + "\nType: " + type +
               "\nEnchantment Type: " + enchantment_type +
               "\nEnchantment Level: " + to_string(enchantment_level);
    return s;
}

/**
         * @brief Returns a random enchantment type for the shield
         *
         * @return string
         */
string Shield::generateEnchantmentType() {
    float probability = generateProbability();
    // If the probability is more than 0.9, return 4 which will be used to
    // select all of the enchantment type
    if (probability <= 0.1) return "All";

    // If the probability is between 0.25 and 0.75, return one random
    // enchantment type

    else if (probability > 0.1 && probability <= 0.6){
        int enchantment_number = sizeof(enchantment_types) /
                                 sizeof(enchantment_types[0]);

        return (enchantment_types[(rand() % enchantment_number)]);
    }
    else
        return "None";
};

/**
         * @brief Returns a random enchantment level for the shield
         *
         * @return int
         */
int Shield::generateEnchantmentLevel() {
    if (generateProbability() <= 0.1)
        return 5;
    else if (generateProbability() > 0.1 && generateProbability() <= 0.5)
        return (rand() % (sizeof(enchantment_types)/sizeof(enchantment_types[0])));

    else
        return 1;
};

/**
         * @brief Creates a new Shield object with a given name and random enchantment type and level
         *
         * @param name
         * @return Shield
         */
Shield Shield::createShield(string name) {
    string newName = name;
    string enchantment_type = Shield::generateEnchantmentType();
    int enchantment_level = Shield::generateEnchantmentLevel();

    return Shield(newName, enchantment_type, enchantment_level);
}

#pragma endregion