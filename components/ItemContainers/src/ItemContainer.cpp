/**
* @file Item.cpp
* @author Ricardo Raji Chahine
* @brief
* @version 0.1
* @date 2024-02-23
*
* @copyright Copyright (c) 2024
*
*/

#include "../include/ItemContainer.h"

using namespace std;

#pragma region Initialization of the ItemContainer Class

/**
* @brief Construct a new Item Container:: Item Container object with null values
*
*/
ItemContainer::ItemContainer()
{
   this->size = 0;
   this->capacity = 5;
}

ItemContainer::ItemContainer(const ItemContainer &other) {
   this->size = other.size;
   this->capacity = other.capacity;
   this->name = other.name;
}

/**
* @brief Returns whether the container is empty or not
*
* @return true
* @return false
*/
bool ItemContainer::isEmpty() const
{
   return (this->size)==0;
}


/**
* @brief Returns whether the container is full or not
*
* @return true
* @return false
*/
bool ItemContainer::isFull() const
{
   return this->size==this->capacity;
}


/**
* @brief Returns the size of the container
*
* @return int
*/
int ItemContainer::getSize() const
{
   return this->size;
}


/**
* @brief Returns the capacity of the container
*
* @return int
*/
int ItemContainer::getCapacity() const
{
   return this->capacity;
}


/**
* @brief Returns the name of the container
*
* @return string
*/
string ItemContainer::getName() const
{
   return this->name;
}


/**
* @brief Sets the name of the container
*
* @param name
*/
void ItemContainer::setName(string name)
{
   this->name = name;
}


#pragma endregion