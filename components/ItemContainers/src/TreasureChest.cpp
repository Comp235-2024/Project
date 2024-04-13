#include "TreasureChest.h"

#pragma region Initialization of the TreasureChest Class

/**
 * @brief Initializes the number of treasure chests to 0
 *
 */
int TreasureChest::nbTreasureChests = 0;


/**
 * @brief Construct a new Treasure Chest:: Treasure Chest object with null values
 *
 */
TreasureChest::TreasureChest():Movable()
{
    nbTreasureChests++;
    this->size = 0;
    this->capacity = 10;
}


/**
 * @brief Construct a new Treasure Chest:: Treasure Chest object with a given capacity
 *
 * @param capacity
 */
TreasureChest::TreasureChest(int capacity):ItemContainer()
{
    nbTreasureChests++;
    this->size = 0;
    this->capacity = capacity;
}


/**
 * @brief Construct a new Treasure Chest:: Treasure Chest object with a given capacity and size
 *
 * @param capacity
 * @param size
 */
TreasureChest::TreasureChest(int capacity,int size):ItemContainer()
{
    nbTreasureChests++;
    this->size = size;
    this->capacity = capacity;
}


/**
 * @brief Construct a new Treasure Chest:: Treasure Chest object with a given name, capacity and size
 *
 * @param name
 * @param capacity
 * @param size
 */
TreasureChest::TreasureChest(string name,int capacity,int size):ItemContainer()
{
    nbTreasureChests++;
    this->size = size;
    this->capacity = capacity;
    this->name = name;
}


/**
 * @brief Construct a new Treasure Chest:: Treasure Chest object with a given name and capacity
 *
 * @param name
 * @param capacity
 */
TreasureChest::TreasureChest(string name,int capacity):ItemContainer()
{
    nbTreasureChests++;
    this->size = 0;
    this->capacity = capacity;
    this->name = name;
}


/**
 * @brief Returns the number of treasure chests
 *
 * @return int
 */
int TreasureChest::getNbTreasureChests()
{
    return nbTreasureChests;
}

vector<Item*> TreasureChest::getTreasureChestStorage() const{
    return this->TreasureChestStorage;
}

Item* TreasureChest::getItem(int index) const{
    return this->TreasureChestStorage[index];
}

int TreasureChest::getItemIndex(Item* item) const{
    for (int i = 0; i < this->size; i++) {
        if (this->TreasureChestStorage[i]->getItemID() == item->getItemID()) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Adds an item to the treasure chest
 *
 * @param item
 */
void TreasureChest::addItem(Item* item)
{
    if (this->isFull())
    {
        cout <<this->getName()<<" is full\n" << endl;
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
        this->TreasureChestStorage.push_back(item);
//        cout<<item->getName()<<" added to "<<this->getName()<<"\n"<<endl;
    }
}


/**
 * @brief Removes an item from the treasure chest
 *
 * @param item
 */
void TreasureChest::removeItem(Item* item)
{
    if (this->isEmpty())
    {
        cout <<this->getName()<<" is empty \n" << endl;

    }
    else
    {
        for (int i = 0; i < this->size; i++)
        {
            if (this->TreasureChestStorage[i]->ItemID==(item->ItemID))
            {
                item->placed=false;
                cout << item->getName()<<" removed from "<<this->getName()<< "\n" << endl;
                this->size--;

                this->TreasureChestStorage.erase(this->TreasureChestStorage.begin() + i);
                return;
            }
        }
        cout << item->getName()<< " not found in "<<this->getName()<< "\n" << endl;
    }
}


/**
 * @brief Prints the items in the treasure chest
 *
 */
void TreasureChest::printItems() const
{
    if(this->isEmpty())
    {
        cout <<this->getName()<<" is empty, nothing to print." << endl;
    }

    else
    {
        cout<<"Printing items in "<<this->getName()<<":\n\n";
        for (int i = 0; i < this->size; i++)
        {
            cout <<(i+1)<<") "<< this->TreasureChestStorage[i]->toString() <<"\n" << endl;
        }
    }
}

//Add printTreasureChests() to the TreasureChest class

//Add getSortedItemsByType() and getSortedItemsByName() to the TreasureChest class


/**
 * @brief Only Prints the items in the treasure chest from a given type
 *
 * @param type
 */
void TreasureChest::printSortedItemsByType(string type) const
{
    string itemsWithType;

    for (int i = 0; i < this->size; i++)
    {
        string currentItemType = this->TreasureChestStorage[i]->getType();
        for(auto& c: currentItemType) c = tolower(c);
        for(auto& c: type) c = tolower(c);

        if (currentItemType== type)
            itemsWithType+=to_string(i+1)+")"+this->TreasureChestStorage[i]->toString()+"\n\n";

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
 * @brief Only Prints the items in the treasure chest with a given name
 *
 * @param name
 */
void TreasureChest::printSortedItemsByName(string name) const
{
    string itemsWithName;

    for (int i = 0; i < this->size; i++)
    {
        string currentItemName = this->TreasureChestStorage[i]->getName();
        for(auto& c: currentItemName) c = tolower(c);
        for(auto& c: name) c = tolower(c);

        if (currentItemName == name)
        {
            itemsWithName+=to_string(i+1)+")"+this->TreasureChestStorage[i]->toString()+"\n\n";
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
 * @brief Returns whether an item is found in the treasure chest
 *
 * @param item
 * @return true
 * @return false
 */
bool TreasureChest::isFound(Item* item) const
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->TreasureChestStorage[i]->ItemID == item->ItemID)
        {
            return true;
        }
    }
    return false;
}

#pragma endregion