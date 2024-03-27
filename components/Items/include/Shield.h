#ifndef SHIELD_H
#define SHIELD_H

#include "Item.h"

class Shield : public Item {
public:
    /**
         * @brief Array containing the possible enchantment types that a Shield object could give
         *
         */
    static  const string enchantment_types[1];

    /**
         * @brief Destroy the Shield object
         *
         */
    ~Shield()=default;

    /**
         * @brief Default Constructor for the Shield object
         *
         */
    Shield();

    /**
         * @brief Parametrized Constructor for the Shield object
         *
         * @param name
         * @param enchantment_type
         * @param enchantment_level
         */
    Shield(string name, string enchantment_type, int enchantment_level);

    /**
         * @brief Copy Constructor for the Shield object
         *
         * @param other
         */
    Shield(const Shield& other);

    /**
         * @brief Assignment Operator for the Shield object
         *
         * @param other
         * @return Shield&
         */
    Shield& operator=(const Shield& other) ;

    /**
         * @brief To string method to print all the attributes of the Shield object
         *
         * @return string
         */
    string toString() override;

    /**
         * @brief Method to create a Shield object with random attributes
         *
         * @param name
         * @return Shield
         */
    static Shield createShield(string name);

    /**
         * @brief Method to generate a random enchantment type for the Shield object
         *
         * @return string
         */
    static string generateEnchantmentType();

    /**
         * @brief Method to generate a random enchantment level for the Shield object
         *
         * @return int
         */
    static int generateEnchantmentLevel();

};

#endif //SHIELD_H