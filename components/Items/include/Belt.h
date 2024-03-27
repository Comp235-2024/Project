#ifndef BELT_H
#define BELT_H

#include "Item.h"

class Belt : public Item {
public:
    /**
         * @brief Array containing the possible enchantment types that a Belt object could give
        */
    static  const string enchantment_types[2];

    /**
         * @brief Destroy the Belt object
         *
         */
    ~Belt()=default;

    /**
         * @brief Default Constructor for the Belt object
         *
         */
    Belt();

    /**
         * @brief Parametrized Constructor for the Belt object
         *
         * @param name
         * @param enchantment_type
         * @param enchantment_level
         */
    Belt(string name, string enchantment_type, int enchantment_level);

    /**
         * @brief Copy Constructor for the Belt object
        */
    Belt(const Belt& other);

    /**
         * @brief Assignment Operator for the Belt object
        */
    Belt& operator=(const Belt& other) ;

    /**
         * @brief To string method to print all the attributes of the Belt object
        */
    string toString() override;

    /**
         * @brief Method to create a Belt object with random attributes
        */
    static Belt createBelt(string name);

    /**
         * @brief Method to generate a random enchantment type for the Belt object
        */
    static string generateEnchantmentType();

    /**
         * @brief Method to generate a random enchantment level for the Belt object
        */
    static int generateEnchantmentLevel();
};

#endif // BELT_H