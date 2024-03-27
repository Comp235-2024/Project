#include "Boots.h"

#pragma region Initialization of Boots class
/**
         * @brief Initializes the echantment types that a Boots can give
         *
         */
const string Boots::enchantment_types[] = {"Dexterity", "Armor Class"};

/**
         * @brief Construct a new Boots:: Boots object with type "Boots"
         *
         */
Boots::Boots() : Item() { type = "Boots"; }

/**
         * @brief Construct a new Boots:: Boots object with a given name, enchantment type and level
         *
         * @param name
         * @param enchantment_type
         * @param enchantment_level
         */
Boots::Boots(string name, string enchantment_type, int enchantment_level) {
    this->name = name;
    this->type = "Boots";
    this->enchantment_type = enchantment_type;
    this->enchantment_level = enchantment_level;
}


/**
         * @brief Construct a new Boots:: Boots object with a given name, enchantment type and level
         *
         * @param other
         */
Boots::Boots(const Boots& other) : Item(other) {}


/**
         * @brief Overloads the assignment operator
         *
         * @param other
         * @return Boots&
         */
Boots& Boots::operator=(const Boots& other) {
    Item::operator=(other);
    return *this;
}


/**
         * @brief Returns a string representation of the boots
         *
         * @return string
         */
string Boots::toString() {
    string s = "\nName: " + name + "\nType: " + type +
               "\nEnchantment Type: " + enchantment_type +
               "\nEnchantment Level: " + to_string(enchantment_level);
    return s;
}


/**
         * @brief Returns a random enchantment type for the boots
         *
         * @return string
         */
string Boots::generateEnchantmentType() {
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
         * @brief Returns a random enchantment level for the boots
         *
         * @return int
         */
int Boots::generateEnchantmentLevel() {
    if (generateProbability() <= 0.1)
        return 5;
    else if (generateProbability() > 0.1 && generateProbability() <= 0.5)
        return (rand() % (sizeof(enchantment_types)/sizeof(enchantment_types[0])));

    else
        return 1;
};


/**
         * @brief Creates a new Boots object with a given name and random enchantment type and level
         *
         * @param name
         * @return Boots
         */
Boots Boots::createBoots(string name) {
    string newName = name;
    string enchantment_type = Boots::generateEnchantmentType();
    int enchantment_level = Boots::generateEnchantmentLevel();

    return Boots(newName, enchantment_type, enchantment_level);
}

#pragma endregion