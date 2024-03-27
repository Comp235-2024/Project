#include "Backpack.h"

#pragma region Initialization of the Backpack Class

/**
 * @brief Initializes the number of backpacks to 0
 *
 */
int Backpack::nbBackpacks = 0;


/**
 * @brief Construct a new Backpack:: Backpack object with null values
 *
 */
Backpack::Backpack()
{
    nbBackpacks++;
    this->size = 0;
    this->capacity = 10;
}

/**
 * @brief Construct a new Backpack:: Backpack object with a given capacity
 *
 * @param capacity
 */
Backpack::Backpack(int capacity):ItemContainer()
{
    nbBackpacks++;
    this->size = 0;
    this->capacity = capacity;
}

/**
 * @brief Construct a new Backpack:: Backpack object with a given capacity and size
 *
 * @param capacity
 * @param size
 */
Backpack::Backpack(int capacity,int size):ItemContainer()
{
    nbBackpacks++;
    this->size = size;
    this->capacity = capacity;
}


/**
 * @brief Construct a new Backpack:: Backpack object with a given name, capacity and size
 *
 * @param name
 * @param capacity
 * @param size
 */
Backpack::Backpack(string name,int capacity,int size):ItemContainer()
{
    nbBackpacks++;
    this->size = size;
    this->capacity = capacity;
    this->name = name;
}


/**
 * @brief Construct a new Backpack:: Backpack object with a given name and capacity
 *
 * @param name
 * @param capacity
 */
Backpack::Backpack(string name,int capacity):ItemContainer()
{
    nbBackpacks++;
    this->size = 0;
    this->capacity = capacity;
    this->name = name;
}


/**
 * @brief Returns the number of backpacks
 *
 * @return int
 */
int Backpack::getNbBackpacks()
{
    return nbBackpacks;
}

vector<Item*> Backpack::getBackpackStorage() const{
    return this->BackpackStorage;
}

//TODO
Item* Backpack::getItem(int index) const {
    return this->getBackpackStorage()[index];
}

//TODO
int Backpack::getItemIndex(Item* item) const{
    for (int i = 0; i < this->size; i++) {
        if (this->getBackpackStorage()[i]->getItemID() == item->getItemID()) {
            return i;
        }
    }
    return -1;

}

/**
 * @brief Adds an item to the backpack
 *
 * @param item
 */
void Backpack::addItem(Item* item)
{
    if (this->isFull())
    {
        cout << "Backpack is full\n" << endl;
        return;
    }

    else if(item->placed==true){
        cout<<item->getName()<<" is already placed in a container\n"<<endl;
        return;
    }

    else
    {
        item->placed=true;
        this->size++;
        this->BackpackStorage.push_back(item);
        cout<<item->getName()<<" added to "+this->getName()+"\n"<<endl;
    }
}


/**
 * @brief Removes an item from the backpack
 *
 * @param item
 */
void Backpack::removeItem(Item* item)
{
    if (this->isEmpty())
    {
        cout <<this->getName()<<" is empty \n" << endl;

    }
    else
    {
        for (int i = 0; i < this->size; i++)
        {
            if (this->BackpackStorage[i]->ItemID==(item->ItemID))
            {
                item->placed=false;

                cout << item->getName()<<" removed from "<<this->getName()<<endl << endl;
                this->size--;

                this->BackpackStorage.erase(this->BackpackStorage.begin() + i);
                return;
            }
        }
        cout << item->getName()<< " not found in "<<this->getName() << endl;
    }
}


/**
 * @brief Prints the items in the backpack
 *
 */
void Backpack::printItems() const
{
    if(this->isEmpty())
    {
        cout << "Backpack is empty, nothing to print." << endl;
    }

    else
    {
        cout<<"Printing items in "<<this->getName()<<":\n\n";
        for (int i = 0; i < this->size; i++)
        {
            cout <<(i+1)<<") "<< this->BackpackStorage[i]->toString() <<"\n" << endl;
        }
    }
}

//Add printBackpacks() to the Backpack class


/**
 * @brief Only Prints the items in the backpack from a given type
 *
 * @param type
 */
void Backpack::printSortedItemsByType(string type) const
{
    string itemsWithType;

    for (int i = 0; i < this->size; i++)
    {
        string currentItemType = this->BackpackStorage[i]->getType();
        for(auto& c: currentItemType) c = tolower(c);
        for(auto& c: type) c = tolower(c);

        if (currentItemType== type)
            itemsWithType+=to_string(i+1)+")"+this->BackpackStorage[i]->toString()+"\n\n";

    }

    if(itemsWithType.empty())
    {
        cout << "No items with the type "<<type<<" found in "<<this->getName()<<"\n" << endl;
    }
    else
    {
        cout << "Items with the type "<<type<<" found in "<<this->getName()<<":\n\n";
        cout << itemsWithType << endl;
    }
}


/**
 * @brief Only Prints the items in the backpack with a given name
 *
 * @param name
 */
void Backpack::printSortedItemsByName(string name) const
{
    string itemsWithName;

    for (int i = 0; i < this->size; i++)
    {
        string currentItemName = this->BackpackStorage[i]->getName();
        for(auto& c: currentItemName) c = tolower(c);
        for(auto& c: name) c = tolower(c);

        if (currentItemName == name)
        {
            itemsWithName+=to_string(i+1)+")"+this->BackpackStorage[i]->toString()+"\n\n";
        }
    }

    if(itemsWithName.empty())
    {
        cout << "No items with the name "<<name<<" found in "<<this->getName()<<"\n" << endl;
    }
    else
    {
        cout << "Items with the name "<<name<<" found in "<<this->getName()<<":\n\n";
        cout << itemsWithName << endl;
    }
}


/**
 * @brief Returns whether an item is found in the backpack
 *
 * @param item
 * @return true
 * @return false
 */
bool Backpack::isFound(Item* item) const
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->BackpackStorage[i]->ItemID == item->ItemID)
        {
            return true;
        }
    }
    return false;
}

#pragma endregion