#include "Helmet.h"

#pragma region Initialization of Helmet class

/**
         * @brief Initializes the echantment types that a Helmet can give
         *
         */
const string Helmet::enchantment_types[] = {"Intelligence",
                                            "Wisdom",
                                            "Armor Class"};

/**
         * @brief Construct a new Helmet:: Helmet object
         *
         */
Helmet::Helmet() : Item() {
    type = "Helmet"; }


/**
         * @brief Construct a new Helmet:: Helmet object with a given name, enchantment type and level
         *
         * @param name
         * @param enchantment_type
         * @param enchantment_level
         */
Helmet::Helmet(string name, string enchantment_type, int enchantment_level) :Item(){
    this->name = name;
    this->type = "Helmet";
    this->enchantment_type = enchantment_type;
    this->enchantment_level = enchantment_level;
}

/**
         * @brief Construct a new Helmet:: Helmet object with a given name, enchantment type and level
         *
         * @param name
         * @param enchantment_type
         * @param enchantment_level
         */
Helmet::Helmet(const Helmet& other) : Item(other) {}

/**
         * @brief Overloads the assignment operator
         *
         * @param other
         * @return Helmet&
         */
Helmet& Helmet::operator=(const Helmet& other) {
    Item::operator=(other);
    return *this;
}

/**
         * @brief Returns a string representation of the helmet
         *
         * @return string
         */
string Helmet::toString() {
    string s = "\nName: " + name + "\nType: " + type +
               "\nEnchantment Type: " + enchantment_type +
               "\nEnchantment Level: " + to_string(enchantment_level);
    return s;
}

// Add applyenchantment() to the Helmet class

/**
         * @brief Generates a random enchantment type for the helmet
         *
         * @return string
         */
string Helmet::generateEnchantmentType() {
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
         * @brief Generates a random enchantment level for the helmet
         *
         * @return int
         */
int Helmet::generateEnchantmentLevel() {
    float probability = generateProbability();
    if (probability <= 0.1)
        return 5;
    else if (probability > 0.1 &&
             probability <= 0.5)
        return (rand() % (sizeof(enchantment_types)/sizeof(enchantment_types[0])))+2;

    else
        return 1;
};

/**
         * @brief Creates a new Helmet object with a given name and random enchantment type and level
         *
         * @param name
         * @return Helmet
         */
Helmet Helmet::createHelmet(string name) {
    string newName = name;
    string enchantment_type = Helmet::generateEnchantmentType();
    int enchantment_level = Helmet::generateEnchantmentLevel();

    return Helmet(newName, enchantment_type, enchantment_level);
};

#pragma endregion