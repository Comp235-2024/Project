#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"

class Weapon : public Item {
private:
    //TODO CONFIGURE THE RANGE OF EACH ITEM;
    Position range;

public:
    /**
         * @brief Array containing the possible enchantment types that a Weapon object could give
         *
         */
    static const string enchantment_types[2];

    /**
         * @brief Destroy the Weapon object
         *
         */
    ~Weapon()=default;

    /**
         * @brief Default Constructor for the Weapon object
         *
         */
    Weapon();

    /**
         * @brief Parametrized Constructor for the Weapon object
         *
         * @param name
         * @param enchantment_type
         * @param enchantment_level
         */
    Weapon(string name, string enchantment_type, int enchantment_level);

    /**
         * @brief Copy Constructor for the Weapon object
         *
         * @param other
         */
    Weapon(const Weapon& other);

    /**
         * @brief Assignment Operator for the Weapon object
         *
         * @param other
         * @return Weapon&
         */
    Weapon& operator=(const Weapon& other) ;

    /**
         * @brief To string method to print all the attributes of the Weapon object
         *
         * @return string
         */
    string toString() override;

    //TODO IMPLEMENT
    Position getRange() const;

    /**
         * @brief Method to create a Weapon object with random attributes
         *
         * @param name
         * @return Weapon
         */
    static Weapon createWeapon(string name);

    /**
         * @brief Method to generate a random enchantment type for the Weapon object
         *
         * @return string
         */
    static string generateEnchantmentType();

    /**
         * @brief Method to generate a random enchantment level for the Weapon object
         *
         * @return int
         */
    static int generateEnchantmentLevel();
};

#endif