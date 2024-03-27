#include "Ring.h"

#pragma region Initialization of Ring class

/**
         * @brief Initializes the echantment types that a Ring can give
         *
         */
const string Ring::enchantment_types[] = {"Strength",
                                          "Constitution",
                                          "Armor Class",
                                          "Wisdom",
                                          "Charisma"};

/**
         * @brief Construct a new Ring:: Ring object with type "Ring"
         *
         */
Ring::Ring() : Item() { type = "Ring"; }

/**
         * @brief Construct a new Ring:: Ring object with a given name, enchantment type and level
         *
         * @param name
         * @param enchantment_type
         * @param enchantment_level
         */
Ring::Ring(string name, string enchantment_type, int enchantment_level) {
    this->name = name;
    this->type = "Ring";
    this->enchantment_type = enchantment_type;
    this->enchantment_level = enchantment_level;
}

/**
         * @brief Construct a new Ring:: Ring object with a given name, enchantment type and level
         *
         * @param other
         */
Ring::Ring(const Ring& other) : Item(other) {}


/**
         * @brief Assignment operator
         *
         * @param other
         * @return Ring&
         */
Ring& Ring::operator=(const Ring& other) {
    Item::operator=(other);
    return *this;
}

/**
         * @brief Returns a string representation of the ring
         *
         * @return string
         */
string Ring::toString() {
    string s = "\nName: " + name + "\nType: " + type +
               "\nEnchantment Type: " + enchantment_type +
               "\nEnchantment Level: " + to_string(enchantment_level);
    return s;
}


/**
         * @brief Returns a random enchantment type for the ring
         *
         * @return string
         */
string Ring::generateEnchantmentType() {
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
         * @brief Returns a random enchantment level for the ring
         *
         * @return int
         */
int Ring::generateEnchantmentLevel() {
    if (generateProbability() <= 0.1)
        return 5;
    else if (generateProbability() > 0.1 && generateProbability() <= 0.5)
        return (rand() % (sizeof(enchantment_types)/sizeof(enchantment_types[0])));

    else
        return 1;
};

/**
         * @brief Creates a new Ring object with a given name and random enchantment type and level
         *
         * @param name
         * @return Ring
         */
Ring Ring::createRing(string name) {
    string newName = name;
    string enchantment_type = Ring::generateEnchantmentType();
    int enchantment_level = Ring::generateEnchantmentLevel();

    return Ring(newName, enchantment_type, enchantment_level);
}

#pragma endregion