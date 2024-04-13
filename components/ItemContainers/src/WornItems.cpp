#include "WornItems.h"

#pragma region Initialization of the WornItemsContainer Class

/**
 * @brief Initializes the number of worn items containers to 0
 *
 */
int WornItemsContainer::nbWornItemsContainer = 0;


/**
 * @brief Construct a new Worn Items Container:: Worn Items Container object with null values
 *
 */
WornItemsContainer::WornItemsContainer()
{
    nbWornItemsContainer++;
    this->size = 0;
    this->capacity = 10;
}


/**
 * @brief Construct a new Worn Items Container:: Worn Items Container object with a given capacity
 *
 * @param capacity
 */
WornItemsContainer::WornItemsContainer(int capacity):ItemContainer()
{
    nbWornItemsContainer++;
    this->size = 0;
    this->capacity = capacity;
}


/**
 * @brief Construct a new Worn Items Container:: Worn Items Container object with a given capacity and size
 *
 * @param capacity
 * @param size
 */
WornItemsContainer::WornItemsContainer(int capacity,int size):ItemContainer()
{
    nbWornItemsContainer++;
    this->size = size;
    this->capacity = capacity;
}


/**
 * @brief Construct a new Worn Items Container:: Worn Items Container object with a given name, capacity and size
 *
 * @param name
 * @param capacity
 * @param size
 */
WornItemsContainer::WornItemsContainer(string name,int capacity,int size):ItemContainer()
{
    nbWornItemsContainer++;
    this->size = size;
    this->capacity = capacity;
    this->name = name;
}


/**
 * @brief Construct a new Worn Items Container:: Worn Items Container object with a given name and capacity
 *
 * @param name
 * @param capacity
 */
WornItemsContainer::WornItemsContainer(string name,int capacity):ItemContainer()
{
    nbWornItemsContainer++;
    this->size = 0;
    this->capacity = capacity;
    this->name = name;
}


/**
 * @brief Returns the number of worn items containers
 *
 * @return int
 */
int WornItemsContainer::getNbWornItemsContainer()
{
    return nbWornItemsContainer;
}

vector<shared_ptr<Item> > WornItemsContainer::getWornItemsContainerStorage() const {
    return this->WornItemsContainerStorage;
}

shared_ptr<Item>  WornItemsContainer::getItem(int index) const{
    return this->WornItemsContainerStorage[index];
}

int WornItemsContainer::getItemIndex(shared_ptr<Item> item) const{
    for (int i = 0; i < this->size; i++) {
        if (this->WornItemsContainerStorage[i]->getItemID() == item->getItemID()) {
            return i;
        }
    }
    return -1;
}

/**
 * @brief Adds an item to the worn items container
 *
 * @param item
 */
void WornItemsContainer::addItem(shared_ptr<Item> item)
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
        this->WornItemsContainerStorage.push_back(item);
        cout<<item->getName()<<" added to "<<this->getName()<<" \n"<<endl;
    }
}


/**
 * @brief Removes an item from the worn items container
 *
 * @param item
 */
void WornItemsContainer::removeItem(shared_ptr<Item> item)
{
    if (this->isEmpty())
    {
        cout <<this->getName() << " is empty \n" << endl;

    }
    else
    {
        for (int i = 0; i < this->size; i++)
        {
            if (this->WornItemsContainerStorage[i]->ItemID==(item->ItemID))
            {
                item->placed=false;
                cout << item->getName()<<" removed from "<<this->getName()<< "\n" << endl;
                this->size--;

                this->WornItemsContainerStorage.erase(this->WornItemsContainerStorage.begin() + i);
                return;
            }
        }
        cout << item->getName()<< " not found in "<<this->getName()<<"\n" << endl;
    }
}


/**
 * @brief Prints the items in the worn items container
 *
 */
void WornItemsContainer::printItems() const
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
            cout <<(i+1)<<") "<< this->WornItemsContainerStorage[i]->toString() <<"\n" << endl;
        }
    }
}

//Add printWornItemsContainers() to the WornItemsContainer class

//Add getSortedItemsByType() and getSortedItemsByName() to the WornItemsContainer class


/**
 * @brief Only Prints the items in the worn items container from a given type
 *
 * @param type
 */
void WornItemsContainer::printSortedItemsByType(string type) const
{
    string itemsWithType;

    for (int i = 0; i < this->size; i++)
    {
        string currentItemType = this->WornItemsContainerStorage[i]->getType();
        for(auto& c: currentItemType) c = tolower(c);
        for(auto& c: type) c = tolower(c);

        if (currentItemType== type)
            itemsWithType+=to_string(i+1)+")"+this->WornItemsContainerStorage[i]->toString()+"\n\n";

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
 * @brief Only Prints the items in the worn items container with a given name
 *
 * @param name
 */
void WornItemsContainer::printSortedItemsByName(string name) const
{
    string itemsWithName;

    for (int i = 0; i < this->size; i++)
    {
        string currentItemName = this->WornItemsContainerStorage[i]->getName();
        for(auto& c: currentItemName) c = tolower(c);
        for(auto& c: name) c = tolower(c);

        if (currentItemName == name)
        {
            itemsWithName+=to_string(i+1)+")"+this->WornItemsContainerStorage[i]->toString()+"\n\n";
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
 * @brief Returns whether an item is found in the worn items container
 *
 * @param item
 * @return true
 * @return false
 */
bool WornItemsContainer::isFound(shared_ptr<Item> item) const
{
    for (int i = 0; i < this->size; i++)
    {
        if (this->WornItemsContainerStorage[i]->ItemID == item->ItemID)
        {
            return true;
        }
    }
    return false;
}

#pragma endregion