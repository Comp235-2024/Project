#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H

#include "Item.h"


/**
 * @brief Base class for all the Item Containers in the game
 *
 */

class ItemContainer{
protected:
    /**
         * @brief The number of objects that the current ItemContainer object is holding
         *
         */
    int size;

    /**
         * @brief The maximum number of objects that the current ItemContainer object can hold
         *
         */
    int capacity;

    /**
         * @brief The name of the current ItemContainer object
         *
         */
    string name;

public:

    /**
         * @brief Construct a new Item Container object
         *
         */
    ItemContainer();

    // copy constructor
    ItemContainer(const ItemContainer& other);

    string textureName = "crate";

    /**
         * @brief Destroy the Item Container object
         *
         * @param capacity
         */
    ~ItemContainer()=default;

    /**
         * @brief Method to add an Item object to the current ItemContainer object
         * @attention Pure Virtual Method to be implemented by the derived classes
         *
         * @param item
         */
    virtual void addItem(Item* item) =0;

    /**
         * @brief Method to remove an Item object from the current ItemContainer object
         * @attention Pure Virtual Method to be implemented by the derived classes
         *
         * @param item
         */
    virtual void removeItem(Item* item) =0;

    /**
         * @brief Method to check if an Item object is found in the current ItemContainer object
         * @attention Pure Virtual Method to be implemented by the derived classes
         *
         * @param item
         * @return true
         * @return false
         */
    virtual bool isFound(Item* item) const =0;

    /**
         * @brief Method to print all the Item objects in the current ItemContainer object
         * @attention Pure Virtual Method to be implemented by the derived classes
         *
         */
    virtual void printItems() const =0;

    /**
         * @brief Method to check if the current ItemContainer object is full
         *
         * @return true
         * @return false
         */
    bool isFull() const;

    /**
         * @brief Method to check if the current ItemContainer object is empty
         *
         * @return true
         * @return false
         */
    bool isEmpty() const;


    /**
         * @brief Get the Size attribute of the object
         *
         * @return int
         */
    int getSize() const;

    /**
         * @brief Get the Capacity attribute of the object
         *
         * @return int
         */
    int getCapacity() const;

    /**
         * @brief Get the Name attribute of the object
         *
         * @return string
         */
    string getName() const;

    /**
         * @brief Set the Name attribute of the object
         *
         * @param name
         */
    void setName(string name);

};

#endif // ITEMCONTAINER_H