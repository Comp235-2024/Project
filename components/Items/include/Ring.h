#ifndef RING_H
#define RING_H

#include "Item.h"

class Ring : public Item {
public:
    /**
         * @brief Array containing the possible enchantment types that a Ring object could give
         *
         */
    static  const string enchantment_types[5];

    /**
         * @brief Destroy the Ring object
         *
         */
    ~Ring()=default;

    /**
         * @brief Default Constructor for the Ring object
         *
         */
    Ring();

    /**
         * @brief Parametrized Constructor for the Ring object
         *
         * @param name
         * @param enchantment_type
         * @param enchantment_level
         */
    Ring(string name, string enchantment_type, int enchantment_level);

    /**
         * @brief Copy Constructor for the Ring object
         *
         * @param other
         */
    Ring(const Ring& other);

    /**
         * @brief Assignment Operator for the Ring object
         *
         * @param other
         * @return Ring&
         */
    Ring& operator=(const Ring& other) ;

    /**
         * @brief To string method to print all the attributes of the Ring object
         *
         * @return string
         */
    string toString() override;

    /**
         * @brief Method to create a Ring object with random attributes
         *
         * @param name
         * @return Ring
         */
    static Ring createRing(string name);

    /**
         * @brief Method to generate a random enchantment type for the Ring object
         *
         * @return string
         */
    static string generateEnchantmentType();

    /**
         * @brief Method to generate a random enchantment level for the Ring object
         *
         * @return int
         */
    static int generateEnchantmentLevel();
};

#endif // RING_H