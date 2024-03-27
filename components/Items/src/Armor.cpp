#include "Armor.h"

#pragma region Initialization of Armor class

/**
         * @brief Initializes the echantment types that an Armor can give
         *
         */
const string Armor::enchantment_types[] = {"Armor Class"};

/**
         * @brief Construct a new Armor:: Armor object with null values
         *
         */
Armor::Armor() : Item() { type = "Armor"; }

/**
         * @brief Construct a new Armor:: Armor object with a given name, enchantment type and level
         *
         * @param name
         * @param enchantment_type
         * @param enchantment_level
         */
Armor::Armor(string name, string enchantment_type, int enchantment_level) {
    this->name = name;
    this->type = "Armor";
    this->enchantment_type = enchantment_type;
    this->enchantment_level = enchantment_level;
}

/**
         * @brief Construct a new Armor:: Armor object with a given name, enchantment type and level
         *
         * @param other
         */
Armor::Armor(const Armor& other) : Item(other) {}

Armor& Armor::operator=(const Armor& other) {
    Item::operator=(other);
    return *this;
}

/**
         * @brief Returns a string representation of the armor
         *
         * @return string
         */
string Armor::toString() {
    string s = "\nName: " + name + "\nType: " + type +
               "\nEnchantment Type: " + enchantment_type +
               "\nEnchantment Level: " + to_string(enchantment_level);
    return s;
}


/**
         * @brief Returns a random enchantment type for the armor
         *
         * @return string
         */
string Armor::generateEnchantmentType() {
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
         * @brief Returns a random enchantment level for the armor
         *
         * @return int
         */
int Armor::generateEnchantmentLevel() {
    if (generateProbability() <= 0.1)
        return 5;
    else if (generateProbability() > 0.1 && generateProbability() <= 0.5)
        return (rand() % (sizeof(enchantment_types)/sizeof(enchantment_types[0])));

    else
        return 1;
};

/**
         * @brief Creates a new Armor object with a given name and random enchantment type and level
         *
         * @param name
         * @return Armor
         */
Armor Armor::createArmor(string name) {
    string newName = name;
    string enchantment_type = Armor::generateEnchantmentType();
    int enchantment_level = Armor::generateEnchantmentLevel();

    return Armor(newName, enchantment_type, enchantment_level);
}

#pragma endregion