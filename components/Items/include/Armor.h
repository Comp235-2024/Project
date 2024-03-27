
#ifndef ARMOR_H
#define ARMOR_H

#include "Item.h"

class Armor : public Item {
public:
    /**
         * @brief Array containting the possible enchantment types that an Armor object could give
         *
         */
    static  const string enchantment_types[1];

    /**
         * @brief Destroy the Armor object
         *
         */
    ~Armor()=default;

    /**
         * @brief Default Constructor for the Armor object
         *
         */
    Armor();

    /**
         * @brief Parametrized Constructor for the Armor object
         *
         * @param name
         * @param enchantment_type
         * @param enchantment_level
         */
    Armor(string name, string enchantment_type, int enchantment_level);

    /**
         * @brief Copy Constructor for the Armor object
         *
         * @param other
         */
    Armor(const Armor& other);

    /**
         * @brief Assignment Operator for the Armor object
         *
         * @param other
         * @return Armor&
         */
    Armor& operator=(const Armor& other) ;

    /**
         * @brief To string method to print all the attributes of the Armor object
         *
         * @return string
         */
    string toString() override;

    /**
         * @brief Method to create an Armor object with random attributes
         *
         * @param name
         * @return Armor
         */
    static Armor createArmor(string name);

    /**
         * @brief Method to generate a random enchantment type for the Armor object
         *
         * @return string
         */
    static string generateEnchantmentType();

    /**
         * @brief Method to generate a random enchantment level for the Armor object
         *
         * @return int
         */
    static int generateEnchantmentLevel();
};


#endif//PROJECT_ARMOR_H
