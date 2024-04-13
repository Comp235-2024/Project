#ifndef WORNITEMS_H
#define WORNITEMS_H

#include "ItemContainer.h"
#include "Item.h"
#include "Movable.h"

/**
 * @brief Class for WornItemsContainer objects which may hold Item objects
 *
 */
class WornItemsContainer: public ItemContainer{
private:
    /**
         * @brief Static variable to keep track of the number of WornItemsContainer objects created
         *
         */
    static int nbWornItemsContainer;

    /**
         * @brief Vector containing all the Item objects in the current WornItemsContainer object
         *
         */
    vector <shared_ptr<Item> > WornItemsContainerStorage;

public:
    std::vector<sf::RectangleShape> wornItemsRectangles;

    /**
         * @brief Default Constructor for the WornItemsContainer object
         *
         */
    WornItemsContainer();

    /**
         * @brief Parametrized Constructor for the WornItemsContainer object
         *
         * @param capacity
         */
    WornItemsContainer(int capacity);

    /**
         * @brief Parametrized Constructor for the WornItemsContainer object
         *
         * @param capacity
         * @param size
         */
    WornItemsContainer(int capacity,int size);

    /**
         * @brief Parametrized Constructor for the WornItemsContainer object
         *
         * @param name
         * @param capacity
         * @param size
         */
    WornItemsContainer(string name,int capacity,int size);

    /**
         * @brief Parametrized Constructor for the WornItemsContainer object
         *
         * @param name
         * @param capacity
         */
    WornItemsContainer(string name,int capacity);


    /**
         * @brief Destroy the WornItemsContainer object
         *
         */
    ~WornItemsContainer()=default;

    /**
         * @brief Method to get the vector containing all the Item objects in the current WornItemsContainer object
         * @return
         */
    vector<shared_ptr<Item>> getWornItemsContainerStorage() const;

    /**
         * @brief Method to get an Item object from the current WornItemsContainer object
         * @param index
         * @return
         */
    shared_ptr<Item> getItem(int index) const;

    /**
         * @brief Method to get the index of an Item object in the current WornItemsContainer object
         * @param item
         * @return
         */
    int getItemIndex(shared_ptr<Item> item) const;

    /**
         * @brief Method to add an Item object to the current WornItemsContainer object
         *
         * @param item
         */
    void addItem(shared_ptr<Item> item) override;

    /**
         * @brief Method to remove an Item object from the current WornItemsContainer object
         *
         * @param item
         */
    void removeItem(shared_ptr<Item> item) override;

    /**
         * @brief Method to check if an Item object is found in the current WornItemsContainer object
         *
         * @param item
         * @return true
         * @return false
         */
    bool isFound(shared_ptr<Item> item) const override;

    /**
         * @brief Method to print all the Item objects in the current WornItemsContainer object
         *
         */
    void printItems() const override;

    /**
         * @brief Method to print all the content of a WornItemsContainer object
         *
         */
    static void printWornItemsContainer();

    /**
         * @brief Method to get the number of WornItemsContainer objects created
         *
         * @return int
         */
    static int getNbWornItemsContainer();

    /**
         * @brief Method that prints only the items in the WornItemsContainer from a specific type
         *
         * @param type
         */
    void  printSortedItemsByType(string type) const;

    /**
         * @brief Method that prints only the items in the WornItemsContainer with a specific name
         *
         * @param name
         */
    void  printSortedItemsByName(string name) const;
};

#endif // "WORNITEMS_H"