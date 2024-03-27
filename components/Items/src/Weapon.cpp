#include "Weapon.h"

#pragma region Initialization of Weapon class

/**
         * @brief Initializes the echantment types that a Weapon can give
         *
         */
const string Weapon::enchantment_types[] = {"Attack Bonus", "Damage Bonus"};


/**
         * @brief Construct a new Weapon:: Weapon object with type "Weapon"
         *
         */
Weapon ::Weapon() : Item() { type = "Weapon"; }


/**
         * @brief Construct a new Weapon:: Weapon object with a given name, enchantment type and level
         *
         * @param name
         * @param enchantment_type
         * @param enchantment_level
         */
Weapon::Weapon(string name, string enchantment_type, int enchantment_level) {
    this->name = name;
    this->type = "Weapon";
    this->enchantment_type = enchantment_type;
    this->enchantment_level = enchantment_level;
}


/**
         * @brief Construct a new Weapon:: Weapon object with a given name, enchantment type and level
         *
         * @param other
         */
Weapon::Weapon(const Weapon& other) : Item(other) {}


/**
         * @brief Overloads the assignment operator
         *
         * @param other
         * @return Weapon&
         */
Weapon& Weapon::operator=(const Weapon& other) {
    Item::operator=(other);
    return *this;
}


/**
         * @brief Returns a string representation of the weapon
         *
         * @return string
         */
string Weapon::toString() {
    string s = "\nName: " + name + "\nType: " + type +
               "\nEnchantment Type: " + enchantment_type +
               "\nEnchantment Level: " + to_string(enchantment_level);
    return s;
}


/**
         * @brief Returns a random enchantment type for the weapon
         *
         * @return string
         */
string Weapon::generateEnchantmentType() {
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
         * @brief Returns a random enchantment level for the weapon
         *
         * @return int
         */
int Weapon::generateEnchantmentLevel() {
    if (generateProbability() <= 0.1)
        return 5;
    else if (generateProbability() > 0.1 && generateProbability() <= 0.5)
        return (rand() % (sizeof(enchantment_types)/sizeof(enchantment_types[0])));

    else
        return 1;
};


/**
         * @brief Creates a new Weapon object with a given name and random enchantment type and level
         *
         * @param name
         * @return Weapon
         */
Weapon Weapon::createWeapon(string name) {
    string newName = name;
    string enchantment_type = Weapon::generateEnchantmentType();
    int enchantment_level = Weapon::generateEnchantmentLevel();

    return Weapon(newName, enchantment_type, enchantment_level);
}

#pragma endregion