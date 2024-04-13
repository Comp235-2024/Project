#ifndef TREASURECHEST_H
#define TREASURECHEST_H


#include "ItemContainer.h"
#include "Item.h"
#include "Movable.h"

/**
 * @brief Class for TreasureChest objects which may hold Item objects
 *
 */
class TreasureChest: public ItemContainer, public Movable{
private:

    /**
         * @brief Static variable to keep track of the number of TreasureChest objects created
         *
         */
    static int nbTreasureChests;

    /**
         * @brief Vector containing all the Item objects in the current TreasureChest object
         *
         */
    vector <shared_ptr<Item>> TreasureChestStorage;

public:

    std::vector<sf::RectangleShape> chestItemRectangles;

    /**
         * @brief Default Constructor for the TreasureChest object
         *
         */
    TreasureChest();

    /**
         * @brief Parametrized Constructor for the TreasureChest object
         *
         * @param capacity
         */
    TreasureChest(int capacity);

    /**
         * @brief Parametrized Constructor for the TreasureChest object
         *
         * @param capacity
         * @param size
         */
    TreasureChest(int capacity,int size);

    /**
         * @brief Parametrized Constructor for the TreasureChest object
         *
         * @param name
         * @param capacity
         * @param size
         */
    TreasureChest(string name,int capacity,int size);

    /**
         * @brief Parametrized Constructor for the TreasureChest object
         *
         * @param name
         * @param capacity
         */
    TreasureChest(string name,int capacity);

    /**
         * @brief Destroy the TreasureChest object
         *
         */
    ~TreasureChest()=default;

    vector<shared_ptr<Item>> getTreasureChestStorage() const;

    shared_ptr<Item> getItem(int index) const;

    int getItemIndex(shared_ptr<Item> item) const;

    /**
         * @brief Method to get the number of TreasureChest objects created
         *
         * @return int
         */
    void addItem(shared_ptr<Item> item) override;

    /**
         * @brief Method to remove an Item object from the current TreasureChest object
         *
         * @param item
         */
    void removeItem(shared_ptr<Item> item) override;

    /**
         * @brief Method to check if an Item object is found in the current TreasureChest object
         *
         * @param item
         * @return true
         * @return false
         */
    bool isFound(shared_ptr<Item> item) const override;

    /**
         * @brief Method to print all the Item objects in the current TreasureChest object
         *
         */
    void printItems() const override;

    /**
         * @brief Method to print all the content of a TreasureChest object
         *
         */
    static int getNbTreasureChests();


    /**
         * @brief Method that prints only the items in the TreasureChest from a specific type
         *
         * @param type
         */
    void  printSortedItemsByType(string type) const;

    /**
         * @brief Method that prints only the items in the TreasureChest with a specific name
         *
         * @param name
         */
    void  printSortedItemsByName(string name) const;
};

#endif // TREASURECHEST_H