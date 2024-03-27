#include "Belt.h"

#pragma region Initialization of Belt class

/**
         * @brief Initializes the echantment types that a Belt can give
         *
         */
const string Belt::enchantment_types[] = {"Strength", "Constitution"};

/**
         * @brief Construct a new Belt:: Belt object with type "Belt"
         *
         */
Belt::Belt() : Item() { type = "Belt"; }

/**
         * @brief Construct a new Belt:: Belt object with a given name, enchantment type and level
         *
         * @param name
         * @param enchantment_type
         * @param enchantment_level
         */
Belt::Belt(string name, string enchantment_type, int enchantment_level) {
    this->name = name;
    this->type = "Belt";
    this->enchantment_type = enchantment_type;
    this->enchantment_level = enchantment_level;
}


/**
         * @brief Construct a new Belt:: Belt object with a given name, enchantment type and level
         *
         * @param other
         */
Belt::Belt(const Belt& other) : Item(other) {}


/**
         * @brief Overloads the assignment operator
         *
         * @param other
         * @return Belt&
         */
Belt& Belt::operator=(const Belt& other) {
    Item::operator=(other);
    return *this;
}


/**
         * @brief Returns a string representation of the belt
         *
         * @return string
         */
string Belt::toString() {
    string s = "\nName: " + name + "\nType: " + type +
               "\nEnchantment Type: " + enchantment_type +
               "\nEnchantment Level: " + to_string(enchantment_level);
    return s;
}


/**
         * @brief Returns a random enchantment type for the belt
         *
         * @return string
         */
string Belt::generateEnchantmentType() {
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
         * @brief Returns a random enchantment level for the belt
         *
         * @return int
         */
int Belt::generateEnchantmentLevel() {
    if (generateProbability() <= 0.1)
        return 5;
    else if (generateProbability() > 0.1 && generateProbability() <= 0.5)
        return (rand() % (sizeof(enchantment_types)/sizeof(enchantment_types[0])));

    else
        return 1;
};

/**
         * @brief Creates a new Belt object with a given name and random enchantment type and level
         *
         * @param name
         * @return Belt
         */
Belt Belt::createBelt(string name) {
    string newName = name;
    string enchantment_type = Belt::generateEnchantmentType();
    int enchantment_level = Belt::generateEnchantmentLevel();

    return Belt(newName, enchantment_type, enchantment_level);
}

#pragma endregion