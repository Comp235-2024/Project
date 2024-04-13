#ifndef BACKPACK_H
#define BACKPACK_H

#include "ItemContainer.h"
#include "Item.h"
#include "Movable.h"
#include <memory>

/**
 * @brief Class for Backpack objects which may hold Item objects
 *
 */
class Backpack: public ItemContainer{
private:
    /**
         * @brief Static variable to keep track of the number of backpacks created
         *
         */
    static int nbBackpacks;

    /**
         * @brief Vector containing all the Item objects in the current Backpack object
         *
         */
    vector <shared_ptr<Item> > BackpackStorage;

public:

    std::vector<sf::RectangleShape> inventoryItemRectangles;

    /**
         * @brief Default Constructor for the Backpack object
         *
         */
    Backpack();

    /**
         * @brief Parametrized Constructor for the Backpack object
         *
         * @param capacity
         */
    Backpack(int capacity);

    /**
         * @brief Parametrized Constructor for the Backpack object
         *
         * @param capacity
         * @param size
         */
    Backpack(int capacity,int size);

    /**
         * @brief Parametrized Constructor for the Backpack object
         *
         * @param name
         * @param capacity
         * @param size
         */
    Backpack(string name,int capacity,int size);

    /**
         * @brief Parametrized Constructor for the Backpack object
         *
         * @param name
         * @param capacity
         */
    Backpack(string name,int capacity);

    /**
         * @brief Destroy the Backpack object
         *
         */
    ~Backpack()=default;

    /**
         * @brief Method to get the vector containing all the Item objects in the current Backpack object
         *
         * @return vector<shared_ptr<Item>>
         */
    vector <shared_ptr<Item> > getBackpackStorage() const;

    /**
         * @brief Method to get an Item object from the current Backpack object
         *
         * @param index
         * @return shared_ptr<Item>
         */
    shared_ptr<Item> getItem(int index) const;

    int getItemIndex(shared_ptr<Item> item) const;

    /**
         * @brief Method to add an Item object to the current Backpack object
         *
         * @param item
         */
    void addItem(shared_ptr<Item> item) override;

    /**
         * @brief Method to remove an Item object from the current Backpack object
         *
         * @param item
         */
    void removeItem(shared_ptr<Item> item) override;

    /**
         * @brief Method to check if an Item object is found in the current Backpack object
         *
         * @param item
         * @return true
         * @return false
         */
    bool isFound(shared_ptr<Item> item) const override;

    /**
         * @brief Method to print all the Item objects in the current Backpack object
         *
         */
    void printItems() const override;

    /**
         * @brief Method to print all the content of a Backpack object
         *
         */
    static void printBackpacks();

    /**
         * @brief Method to get the number of Backpack objects created
         *
         * @return int
         */
    static int getNbBackpacks();

    /**
         * @brief Method that prints only the items in the backpack from a specific type
         *
         * @param type
         */
    void  printSortedItemsByType(string type) const;

    /**
         * @brief Method that prints only the items in the backpack with a specific name
         *
         * @param name
         */
    void  printSortedItemsByName(string name) const;


};

#endif // BACKPACK_H