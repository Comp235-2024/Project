#ifndef BOOTS_H
#define BOOTS_H

#include "Item.h"

class Boots : public Item {
public:
    /**
         * @brief Array containing the possible enchantment types that a Boots object could give
         *
         */
    static const string enchantment_types[2];

    /**
         * @brief Destroy the Boots object
         *
         */
    ~Boots()=default;

    /**
         * @brief Default Constructor for the Boots object
         *
         */
    Boots();

    /**
         * @brief Parametrized Constructor for the Boots object
         *
         * @param name
         * @param enchantment_type
         * @param enchantment_level
         */
    Boots(string name, string enchantment_type, int enchantment_level);

    /**
         * @brief Copy Constructor for the Boots object
         *
         * @param other
         */
    Boots(const Boots& other);

    /**
         * @brief Assignment Operator for the Boots object
         *
         * @param other
         * @return Boots&
         */
    Boots& operator=(const Boots& other) ;

    /**
         * @brief To string method to print all the attributes of the Boots object
         *
         * @return string
         */
    string toString() override;

    /**
         * @brief Method to create a Boots object with random attributes
         *
         * @param name
         * @return Boots
         */
    static Boots createBoots(string name);

    /**
         * @brief Method to generate a random enchantment type for the Boots object
         *
         * @return string
         */
    static string generateEnchantmentType();

    /**
         * @brief Method to generate a random enchantment level for the Boots object
         *
         * @return int
         */
    static int generateEnchantmentLevel();
};

#endif