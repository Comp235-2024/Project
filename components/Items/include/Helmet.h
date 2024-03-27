
#ifndef HELMET_H
#define HELMET_H

#include "Item.h"

class Helmet : public Item {
public:
    /**
         * @brief Array containing the possible enchantment types that a Helmet object could give
         *
         */
    static  const string enchantment_types[3];

    /**
         * @brief Destroy the Helmet object
         *
         */
    ~Helmet()=default;

    /**
         * @brief Default Constructor for the Helmet object
         *
         */
    Helmet();

    /**
         * @brief Parametrized Constructor for the Helmet object
         *
         * @param name
         * @param enchantment_type
         * @param enchantment_level
         */
    Helmet(string name, string enchantment_type, int enchantment_level);

    /**
         * @brief Copy Constructor for the Helmet object
         *
         * @param other
         */
    Helmet(const Helmet& other);

    /**
         * @brief Assignment Operator for the Helmet object
         *
         * @param other
         * @return Helmet&
         */
    Helmet& operator=(const Helmet& other) ;

    /**
         * @brief To string method to print all the attributes of the Helmet object
         *
         * @return string
         */
    string toString() override;

    /**
         * @brief Method to create a Helmet object with random attributes
         *
         * @param name
         * @return Helmet
         */
    static Helmet createHelmet(string name);

    /**
         * @brief Method to generate a random enchantment type for the Helmet object
         *
         * @return string
         */
    static string generateEnchantmentType();

    /**
         * @brief Method to generate a random enchantment level for the Helmet object
         *
         * @return int
         */
    static int generateEnchantmentLevel() ;
};

#endif//HELMET_H
