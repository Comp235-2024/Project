/**
* @file Item.h
* @author Ricardo Raji Chahine
* @date Winter 2024
*/

#ifndef ITEMS_H
#define ITEMS_H

#include <iostream>
#include <string>
#include "Movable.h"
#include "Position.h"
#include <vector>

using namespace std;

/**
* @brief Base Class for all items in the game
* @details
*
*/
class Item: public Movable{
    friend class ItemContainer;
    friend class Backpack;
    friend class WornItemsContainer;
    friend class TreasureChest;

private:
    /**
        * @brief Static variable to keep track of the number of items created
       */
    static int ItemCount;

protected:
    /**
        * @brief attribute that each Item has to keep track of its ID
       */
    int ItemID;

    /**
        * @brief attribute that each Item has to keep track of its name
       */
    string name;

    /**
        * @brief attribute that each Item has to keep track of its type
       */
    string type;

    /**
        * @brief attribute that each Item has to keep track of its enchantment type
       */
    string enchantment_type;

    /**
        * @brief attribute that each Item has to keep track of its enchantment level
       */
    int enchantment_level;

    /**
        * @brief attribute that each Item has to keep track of whether it is placed somewhere (Itemcontainer, map...) or not
       */
    bool placed;



public:
    /**
        * @brief Destroy the Item object
        *
        */
    ~Item() override =default ;

    /**
        * @brief Construct a new Item object with null values
        *
        */
    Item();


    Item& operator=(const Item& other) ;

    /**
        * @brief Get the Name atrribute of the Item object
        *
        * @return string
        */
    string getName() const;

    /**
        * @brief Set the Name atrribute of the Item object
        *
        * @param name
        */
    void setName(string name);

    /**
        * @brief Get the Type atrribute of the Item object
        *
        * @return string
        */
    string getType() const;

    /**
        * @brief Get the Enchantment Level atrribute of the Item object
        *
        * @return int
        */
    int getEnchantmentLevel() const;

    /**
        * @brief Get the Enchantment Type atrribute of the Item object
        *
        * @return string
        */
    string getEnchantmentType() const;

    /**
        * @brief Set the Enchantment Type atrribute of the Item object
        *
        * @param enchantment_type
        */
    void setEnchantmentType(string enchantment_type);

    /**
        * @brief Set the Enchantment Level atrribute of the Item object
        *
        * @param enchantment_level
        */
    void setEnchantmentLevel(int enchantment_level);

    /**
        * @brief Generate a random uniformely distributed probability between 0 and 1
        *
        * @return float
        */
    static float generateProbability();

    /**
        * @brief Whether the item is placed somewhere or not
        *
        * @return true
        * @return false
        */
    bool isPlaced() const;

    /**
        * @brief Get the Item ID atrribute of the Item object
        *
        * @return int
        */
    int getItemID() const;

    static int getItemCount();

    /**
        * @brief To string method to print all the attributes of the Item object
        *
        * @return string
        */
    virtual string toString()=0;

    /**
        * @brief This function is used to test the functionality of the item class.
        *
        */
    static void item_test();


};

#endif //A3_ITEMS_H
