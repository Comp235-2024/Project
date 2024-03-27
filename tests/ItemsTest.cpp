#include "../components/Items/include/Item.h"
#include <random>
using namespace std;


int testCinForItemClasses(){
    while (true) {
            cout << "\n\nPlease enter your choice: ";
            int choice_which_class;
            cin >> choice_which_class;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";

            } else if (choice_which_class < 0 || choice_which_class > 7) {
                std::cout << "Invalid input. Number is not in the range 1-7.\n";

            } else {
                return choice_which_class; 
            }
        }
}

int testCinForItemMethods(){
    while (true) {
            cout << "\n\nPlease enter your choice: ";
            int choice_which_class;
            cin >> choice_which_class;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                cout << "Invalid input. Please enter a number.\n";

            } else if (choice_which_class < 0 || choice_which_class > 5) {
                std::cout << "Invalid input. Number is not in the range 1-5.\n";

            } else {
                return choice_which_class; 
            }
        }
}

void printItemsOptions(){
    cout<<"\nPress 1: To Test the Helmet class"<<endl;
    cout<<"Press 2: To Test the Armor class"<<endl;
    cout<<"Press 3: To Test the Shield class"<<endl;
    cout<<"Press 4: To Test the Ring class"<<endl;
    cout<<"Press 5: To Test the Belt class"<<endl;
    cout<<"Press 6: To Test the Boots class"<<endl;
    cout<<"Press 7: To Test the Weapon class"<<endl;
    cout<<"Press 0: To Exit the Program"  <<endl;
}

void printItemsMethods(){
    cout<<"\nPress 1: To Test the Default Constructor"<<endl;
    cout<<"Press 2: To Test the Constructor with Parameters"<<endl;
    cout<<"Press 3: To Test the Copy Constructor"<<endl;
    cout<<"Press 4: To Test the Assignment Operator"<<endl;
    cout<<"Press 5: To Test the createItem Method"<<endl;
    cout<<"Press 0: To Return to the previous menu"  <<endl;

};

void interactiveItemTesting(){
    
    cout<<"-------------------"<<endl;
    cout<<"Testing Item Program"<<endl;
    cout<<"-------------------"<<endl<<endl;
        
    cout<<"\nTesting Item Classes"<<endl; 
    cout<<"-------------------"<<endl<<endl;
    
    printItemsOptions();

    int ChoiceWhichItemClass=testCinForItemClasses();

    while(ChoiceWhichItemClass!=0){
        if(ChoiceWhichItemClass==1){
            cout<<"\nTesting Helmet Class"<<endl;
            cout<<"-------------------"<<endl<<endl;

            printItemsMethods();

            int ChoiceWhichMethodInHelmet=testCinForItemMethods();

            while(ChoiceWhichMethodInHelmet!=0){

                if(ChoiceWhichMethodInHelmet==1){
                    cout<<"\nTesting Default Constructor"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Helmet helmet;
                    cout<<"Helmet Name: "<<helmet.getName()<<endl;
                    cout<<"Helmet Type: "<<helmet.getType()<<endl;
                    cout<<"Helmet Enchantment Type: "<<helmet.getEnchantmentType()<<endl;
                    cout<<"Helmet Enchantment Level: "<<helmet.getEnchantmentLevel()<<endl;
                    cout<<"Helmet ID: "<<helmet.getItemID()<<endl;
                    cout<<"Helmet Placed: "<<to_string(helmet.isPlaced())<<endl;
                    cout<<"Helmet Probability: "<<helmet.generateProbability()<<endl;
                    cout<<"Helmet toString: "<<helmet.toString()<<endl;
                }

                else if(ChoiceWhichMethodInHelmet==2){
                    cout<<"\nTesting Constructor with Parameters"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Helmet helmet("Helmet2", "Enchantment1", 1);
                    cout<<"Helmet Name: "<<helmet.getName()<<endl;
                    cout<<"Helmet Type: "<<helmet.getType()<<endl;
                    cout<<"Helmet Enchantment Type: "<<helmet.getEnchantmentType()<<endl;
                    cout<<"Helmet Enchantment Level: "<<helmet.getEnchantmentLevel()<<endl;
                    cout<<"Helmet ID: "<<helmet.getItemID()<<endl;
                    cout<<"Helmet Placed: "<<to_string(helmet.isPlaced())<<endl;
                    cout<<"Helmet Probability: "<<helmet.generateProbability()<<endl;
                    cout<<"Helmet toString: "<<helmet.toString()<<endl;
                }

                else if(ChoiceWhichMethodInHelmet==3){
                    cout<<"\nTesting Copy Constructor"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Helmet helmet("Helmet3", "Enchantment1", 1);
                    Helmet copyhelmet3(helmet);
                    cout<<"Helmet Name: "<<copyhelmet3.getName()<<endl;
                    cout<<"Helmet Type: "<<copyhelmet3.getType()<<endl;
                    cout<<"Helmet Enchantment Type: "<<copyhelmet3.getEnchantmentType()<<endl;
                    cout<<"Helmet Enchantment Level: "<<copyhelmet3.getEnchantmentLevel()<<endl;
                    cout<<"Helmet ID: "<<copyhelmet3.getItemID()<<endl;
                    cout<<"Helmet Placed: "<<to_string(copyhelmet3.isPlaced())<<endl;
                    cout<<"Helmet Probability: "<<copyhelmet3.generateProbability()<<endl;
                    cout<<"Helmet toString: "<<copyhelmet3.toString()<<endl;
                }

                else if(ChoiceWhichMethodInHelmet==4){
                    cout<<"\nTesting Assignment Operator"<<endl;
                    cout<<"-------------------"<<endl<<endl;
                
                    Helmet helmet("Helmet4", "Enchantment1", 1);                           
                    Helmet helmet4=helmet;                               
                    cout<<"Helmet Name: "<<helmet4.getName()<<endl;
                    cout<<"Helmet Type: "<<helmet4.getType()<<endl;
                    cout<<"Helmet Enchantment Type: "<<helmet4.getEnchantmentType()<<endl;
                    cout<<"Helmet Enchantment Level: "<<helmet4.getEnchantmentLevel()<<endl;
                    cout<<"Helmet ID: "<<helmet4.getItemID()<<endl;
                    cout<<"Helmet Placed: "<<to_string(helmet4.isPlaced())<<endl;
                    cout<<"Helmet Probability: "<<helmet4.generateProbability()<<endl;
                    cout<<"Helmet toString: "<<helmet4.toString()<<endl;
                }

                else if(ChoiceWhichMethodInHelmet==5){
                    cout<<"\nTesting createHelmet Method"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Helmet helmet=Helmet::createHelmet("Helmet5");
                    cout<<"Helmet Name: "<<helmet.getName()<<endl;
                    cout<<"Helmet Type: "<<helmet.getType()<<endl;
                    cout<<"Helmet Enchantment Type: "<<helmet.getEnchantmentType()<<endl;
                    cout<<"Helmet Enchantment Level: "<<helmet.getEnchantmentLevel()<<endl;
                    cout<<"Helmet ID: "<<helmet.getItemID()<<endl;
                    cout<<"Helmet Placed: "<<helmet.isPlaced()<<endl;
                    cout<<"Helmet Probability: "<<helmet.generateProbability()<<endl;
                    cout<<"Helmet toString: "<<helmet.toString()<<endl;
                }
                
                ChoiceWhichMethodInHelmet=testCinForItemMethods();
            }                   
        
        }

        if(ChoiceWhichItemClass==2){
            cout<<"\nTesting Armor Class"<<endl;
            cout<<"-------------------"<<endl<<endl;

            printItemsMethods();

            int ChoiceWhichMethodInArmor=testCinForItemMethods();

            while(ChoiceWhichMethodInArmor!=0){

                if(ChoiceWhichMethodInArmor==1){
                    cout<<"\nTesting Default Constructor"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Armor armor;
                    cout<<"Armor Name: "<<armor.getName()<<endl;
                    cout<<"Armor Type: "<<armor.getType()<<endl;
                    cout<<"Armor Enchantment Type: "<<armor.getEnchantmentType()<<endl;
                    cout<<"Armor Enchantment Level: "<<armor.getEnchantmentLevel()<<endl;
                    cout<<"Armor ID: "<<armor.getItemID()<<endl;
                    cout<<"Armor Placed: "<<to_string(armor.isPlaced())<<endl;
                    cout<<"Armor Probability: "<<armor.generateProbability()<<endl;
                    cout<<"Armor toString: "<<armor.toString()<<endl;
                }

                else if(ChoiceWhichMethodInArmor==2){
                    cout<<"\nTesting Constructor with Parameters"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Armor armor("Armor2", "Enchantment1", 1);
                    cout<<"Armor Name: "<<armor.getName()<<endl;
                    cout<<"Armor Type: "<<armor.getType()<<endl;
                    cout<<"Armor Enchantment Type: "<<armor.getEnchantmentType()<<endl;
                    cout<<"Armor Enchantment Level: "<<armor.getEnchantmentLevel()<<endl;
                    cout<<"Armor ID: "<<armor.getItemID()<<endl;
                    cout<<"Armor Placed: "<<armor.isPlaced()<<endl;
                    cout<<"Armor Probability: "<<armor.generateProbability()<<endl;
                    cout<<"Armor toString: "<<armor.toString()<<endl;
                }

                else if(ChoiceWhichMethodInArmor==3){
                    cout<<"\nTesting Copy Constructor"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Armor armor("Armor3", "Enchantment1", 1);
                    Armor copyarmor3(armor);
                    cout<<"Armor Name: "<<copyarmor3.getName()<<endl;
                    cout<<"Armor Type: "<<copyarmor3.getType()<<endl;
                    cout<<"Armor Enchantment Type: "<<copyarmor3.getEnchantmentType()<<endl;
                    cout<<"Armor Enchantment Level: "<<copyarmor3.getEnchantmentLevel()<<endl;
                    cout<<"Armor ID: "<<copyarmor3.getItemID()<<endl;
                    cout<<"Armor Placed: "<<copyarmor3.isPlaced()<<endl;
                    cout<<"Armor Probability: "<<copyarmor3.generateProbability()<<endl;
                    cout<<"Armor toString: "<<copyarmor3.toString()<<endl;
                }

                else if(ChoiceWhichMethodInArmor==4){
                    cout<<"\nTesting Assignment Operator"<<endl;
                    cout<<"-------------------"<<endl<<endl;
                
                    Armor armor("Armor4", "Enchantment1", 1);                           
                    Armor armor4=armor;                               
                    cout<<"Armor Name: "<<armor4.getName()<<endl;
                    cout<<"Armor Type: "<<armor4.getType()<<endl;
                    cout<<"Armor Enchantment Type: "<<armor4.getEnchantmentType()<<endl;
                    cout<<"Armor Enchantment Level: "<<armor4.getEnchantmentLevel()<<endl;
                    cout<<"Armor ID: "<<armor4.getItemID()<<endl;
                    cout<<"Armor Placed: "<<armor4.isPlaced()<<endl;
                    cout<<"Armor Probability: "<<armor4.generateProbability()<<endl;
                    cout<<"Armor toString: "<<armor4.toString()<<endl;
                }

                else if(ChoiceWhichMethodInArmor==5){
                    cout<<"\nTesting createArmor Method"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Armor armor=Armor::createArmor("Armor5");
                    cout<<"Armor Name: "<<armor.getName()<<endl;
                    cout<<"Armor Type: "<<armor.getType()<<endl;
                    cout<<"Armor Enchantment Type: "<<armor.getEnchantmentType()<<endl;
                    cout<<"Armor Enchantment Level: "<<armor.getEnchantmentLevel()<<endl;
                    cout<<"Armor ID: "<<armor.getItemID()<<endl;
                    cout<<"Armor Placed: "<<armor.isPlaced()<<endl;
                    cout<<"Armor Probability: "<<armor.generateProbability()<<endl;
                    cout<<"Armor toString: "<<armor.toString()<<endl;
                }

                ChoiceWhichMethodInArmor=testCinForItemMethods();

            }

        }

        if(ChoiceWhichItemClass==3){
            cout<<"\nTesting Shield Class"<<endl;
            cout<<"-------------------"<<endl<<endl;

            printItemsMethods();

            int ChoiceWhichMethodInShield=testCinForItemMethods();

            while(ChoiceWhichMethodInShield!=0){

                if(ChoiceWhichMethodInShield==1){
                    cout<<"\nTesting Default Constructor"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Shield shield;
                    cout<<"Shield Name: "<<shield.getName()<<endl;
                    cout<<"Shield Type: "<<shield.getType()<<endl;
                    cout<<"Shield Enchantment Type: "<<shield.getEnchantmentType()<<endl;
                    cout<<"Shield Enchantment Level: "<<shield.getEnchantmentLevel()<<endl;
                    cout<<"Shield ID: "<<shield.getItemID()<<endl;
                    cout<<"Shield Placed: "<<shield.isPlaced()<<endl;
                    cout<<"Shield Probability: "<<shield.generateProbability()<<endl;
                    cout<<"Shield toString: "<<shield.toString()<<endl;
                }

                else if(ChoiceWhichMethodInShield==2){
                    cout<<"\nTesting Constructor with Parameters"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Shield shield("Shield2", "Enchantment1", 1);
                    cout<<"Shield Name: "<<shield.getName()<<endl;
                    cout<<"Shield Type: "<<shield.getType()<<endl;
                    cout<<"Shield Enchantment Type: "<<shield.getEnchantmentType()<<endl;
                    cout<<"Shield Enchantment Level: "<<shield.getEnchantmentLevel()<<endl;
                    cout<<"Shield ID: "<<shield.getItemID()<<endl;
                    cout<<"Shield Placed: "<<shield.isPlaced()<<endl;
                    cout<<"Shield Probability: "<<shield.generateProbability()<<endl;
                    cout<<"Shield toString: "<<shield.toString()<<endl;
                }

                else if(ChoiceWhichMethodInShield==3){
                    cout<<"\nTesting Copy Constructor"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Shield shield("Shield3", "Enchantment1", 1);
                    Shield copyshield3(shield);
                    cout<<"Shield Name: "<<copyshield3.getName()<<endl;
                    cout<<"Shield Type: "<<copyshield3.getType()<<endl;
                    cout<<"Shield Enchantment Type: "<<copyshield3.getEnchantmentType()<<endl;
                    cout<<"Shield Enchantment Level: "<<copyshield3.getEnchantmentLevel()<<endl;
                    cout<<"Shield ID: "<<copyshield3.getItemID()<<endl;
                    cout<<"Shield Placed: "<<copyshield3.isPlaced()<<endl;
                    cout<<"Shield Probability: "<<copyshield3.generateProbability()<<endl;
                    cout<<"Shield toString: "<<copyshield3.toString()<<endl;
                }

                else if(ChoiceWhichMethodInShield==4){
                    cout<<"\nTesting Assignment Operator"<<endl;
                    cout<<"-------------------"<<endl<<endl;
                
                    Shield shield("Shield4", "Enchantment1", 1);                           
                    Shield shield4=shield;                               
                    cout<<"Shield Name: "<<shield4.getName()<<endl;
                    cout<<"Shield Type: "<<shield4.getType()<<endl;
                    cout<<"Shield Enchantment Type: "<<shield4.getEnchantmentType()<<endl;
                    cout<<"Shield Enchantment Level: "<<shield4.getEnchantmentLevel()<<endl;
                    cout<<"Shield ID: "<<shield4.getItemID()<<endl;
                    cout<<"Shield Placed: "<<shield4.isPlaced()<<endl;
                    cout<<"Shield Probability: "<<shield4.generateProbability()<<endl;
                    cout<<"Shield toString: "<<shield4.toString()<<endl;
                }

                else if(ChoiceWhichMethodInShield==5){
                    cout<<"\nTesting createShield Method"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Shield shield=Shield::createShield("Shield5");
                    cout<<"Shield Name: "<<shield.getName()<<endl;
                    cout<<"Shield Type: "<<shield.getType()<<endl;
                    cout<<"Shield Enchantment Type: "<<shield.getEnchantmentType()<<endl;
                    cout<<"Shield Enchantment Level: "<<shield.getEnchantmentLevel()<<endl;
                    cout<<"Shield ID: "<<shield.getItemID()<<endl;
                    cout<<"Shield Placed: "<<shield.isPlaced()<<endl;
                    cout<<"Shield Probability: "<<shield.generateProbability()<<endl;
                    cout<<"Shield toString: "<<shield.toString()<<endl;
                }
 
                ChoiceWhichMethodInShield=testCinForItemMethods();
            }

    }

        if(ChoiceWhichItemClass==4){
        cout<<"\nTesting Ring Class"<<endl;
        cout<<"-------------------"<<endl<<endl;

        printItemsMethods();

        int ChoiceWhichMethodInRing=testCinForItemMethods();

        while(ChoiceWhichMethodInRing!=0){

            if(ChoiceWhichMethodInRing==1){
                cout<<"\nTesting Default Constructor"<<endl;
                cout<<"-------------------"<<endl<<endl;

                Ring ring;
                cout<<"Ring Name: "<<ring.getName()<<endl;
                cout<<"Ring Type: "<<ring.getType()<<endl;
                cout<<"Ring Enchantment Type: "<<ring.getEnchantmentType()<<endl;
                cout<<"Ring Enchantment Level: "<<ring.getEnchantmentLevel()<<endl;
                cout<<"Ring ID: "<<ring.getItemID()<<endl;
                cout<<"Ring Placed: "<<ring.isPlaced()<<endl;
                cout<<"Ring Probability: "<<ring.generateProbability()<<endl;
                cout<<"Ring toString: "<<ring.toString()<<endl;
            }

            else if(ChoiceWhichMethodInRing==2){
                cout<<"\nTesting Constructor with Parameters"<<endl;
                cout<<"-------------------"<<endl<<endl;

                Ring ring("Ring2", "Enchantment1", 1);
                cout<<"Ring Name: "<<ring.getName()<<endl;
                cout<<"Ring Type: "<<ring.getType()<<endl;
                cout<<"Ring Enchantment Type: "<<ring.getEnchantmentType()<<endl;
                cout<<"Ring Enchantment Level: "<<ring.getEnchantmentLevel()<<endl;
                cout<<"Ring ID: "<<ring.getItemID()<<endl;
                cout<<"Ring Placed: "<<ring.isPlaced()<<endl;
                cout<<"Ring Probability: "<<ring.generateProbability()<<endl;
                cout<<"Ring toString: "<<ring.toString()<<endl;
            }

            else if(ChoiceWhichMethodInRing==3){
                cout<<"\nTesting Copy Constructor"<<endl;
                cout<<"-------------------"<<endl<<endl;

                Ring ring("Ring3", "Enchantment1", 1);
                Ring copyring3(ring);
                cout<<"Ring Name: "<<copyring3.getName()<<endl;
                cout<<"Ring Type: "<<copyring3.getType()<<endl;
                cout<<"Ring Enchantment Type: "<<copyring3.getEnchantmentType()<<endl;
                cout<<"Ring Enchantment Level: "<<copyring3.getEnchantmentLevel()<<endl;
                cout<<"Ring ID: "<<copyring3.getItemID()<<endl;
                cout<<"Ring Placed: "<<copyring3.isPlaced()<<endl;
                cout<<"Ring Probability: "<<copyring3.generateProbability()<<endl;
                cout<<"Ring toString: "<<copyring3.toString()<<endl;
            }

            else if(ChoiceWhichMethodInRing==4){
                cout<<"\nTesting Assignment Operator"<<endl;
                cout<<"-------------------"<<endl<<endl;
            
                Ring ring("Ring4", "Enchantment1", 1);                           
                Ring ring4=ring;                               
                cout<<"Ring Name: "<<ring4.getName()<<endl;
                cout<<"Ring Type: "<<ring4.getType()<<endl;
                cout<<"Ring Enchantment Type: "<<ring4.getEnchantmentType()<<endl;
                cout<<"Ring Enchantment Level: "<<ring4.getEnchantmentLevel()<<endl;
                cout<<"Ring ID: "<<ring4.getItemID()<<endl;
                cout<<"Ring Placed: "<<ring4.isPlaced()<<endl;
                cout<<"Ring Probability: "<<ring4.generateProbability()<<endl;
                cout<<"Ring toString: "<<ring4.toString()<<endl;
            }

            else if(ChoiceWhichMethodInRing==5){
                cout<<"\nTesting createRing Method"<<endl;
                cout<<"-------------------"<<endl<<endl;

                Ring ring=Ring::createRing("Ring5");
                cout<<"Ring Name: "<<ring.getName()<<endl;
                cout<<"Ring Type: "<<ring.getType()<<endl;
                cout<<"Ring Enchantment Type: "<<ring.getEnchantmentType()<<endl;
                cout<<"Ring Enchantment Level: "<<ring.getEnchantmentLevel()<<endl;
                cout<<"Ring ID: "<<ring.getItemID()<<endl;
                cout<<"Ring Placed: "<<ring.isPlaced()<<endl;
                cout<<"Ring Probability: "<<ring.generateProbability()<<endl;
                cout<<"Ring toString: "<<ring.toString()<<endl;
            }
            
            ChoiceWhichMethodInRing=testCinForItemMethods();

        }
    }

        if(ChoiceWhichItemClass==5){
            cout<<"\nTesting Belt Class"<<endl;
            cout<<"-------------------"<<endl<<endl;

            printItemsMethods();

            int ChoiceWhichMethodInBelt=testCinForItemMethods();

            while(ChoiceWhichMethodInBelt!=0){

                if(ChoiceWhichMethodInBelt==1){
                    cout<<"\nTesting Default Constructor"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Belt belt;
                    cout<<"Belt Name: "<<belt.getName()<<endl;
                    cout<<"Belt Type: "<<belt.getType()<<endl;
                    cout<<"Belt Enchantment Type: "<<belt.getEnchantmentType()<<endl;
                    cout<<"Belt Enchantment Level: "<<belt.getEnchantmentLevel()<<endl;
                    cout<<"Belt ID: "<<belt.getItemID()<<endl;
                    cout<<"Belt Placed: "<<belt.isPlaced()<<endl;
                    cout<<"Belt Probability: "<<belt.generateProbability()<<endl;
                    cout<<"Belt toString: "<<belt.toString()<<endl;
                }

                else if(ChoiceWhichMethodInBelt==2){
                    cout<<"\nTesting Constructor with Parameters"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Belt belt("Belt2", "Enchantment1", 1);
                    cout<<"Belt Name: "<<belt.getName()<<endl;
                    cout<<"Belt Type: "<<belt.getType()<<endl;
                    cout<<"Belt Enchantment Type: "<<belt.getEnchantmentType()<<endl;
                    cout<<"Belt Enchantment Level: "<<belt.getEnchantmentLevel()<<endl;
                    cout<<"Belt ID: "<<belt.getItemID()<<endl;
                    cout<<"Belt Placed: "<<belt.isPlaced()<<endl;
                    cout<<"Belt Probability: "<<belt.generateProbability()<<endl;
                    cout<<"Belt toString: "<<belt.toString()<<endl;
                }

                else if(ChoiceWhichMethodInBelt==3){
                    cout<<"\nTesting Copy Constructor"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Belt belt("Belt3", "Enchantment1", 1);
                    Belt copybelt3(belt);
                    cout<<"Belt Name: "<<copybelt3.getName()<<endl;
                    cout<<"Belt Type: "<<copybelt3.getType()<<endl;
                    cout<<"Belt Enchantment Type: "<<copybelt3.getEnchantmentType()<<endl;
                    cout<<"Belt Enchantment Level: "<<copybelt3.getEnchantmentLevel()<<endl;
                    cout<<"Belt ID: "<<copybelt3.getItemID()<<endl;
                    cout<<"Belt Placed: "<<copybelt3.isPlaced()<<endl;
                    cout<<"Belt Probability: "<<copybelt3.generateProbability()<<endl;
                    cout<<"Belt toString: "<<copybelt3.toString()<<endl;
                }

                else if(ChoiceWhichMethodInBelt==4){
                    cout<<"\nTesting Assignment Operator"<<endl;
                    cout<<"-------------------"<<endl<<endl;
                
                    Belt belt("Belt4", "Enchantment1", 1);                           
                    Belt belt4=belt;                               
                    cout<<"Belt Name: "<<belt4.getName()<<endl;
                    cout<<"Belt Type: "<<belt4.getType()<<endl;
                    cout<<"Belt Enchantment Type: "<<belt4.getEnchantmentType()<<endl;
                    cout<<"Belt Enchantment Level: "<<belt4.getEnchantmentLevel()<<endl;
                    cout<<"Belt ID: "<<belt4.getItemID()<<endl;
                    cout<<"Belt Placed: "<<belt4.isPlaced()<<endl;
                    cout<<"Belt Probability: "<<belt4.generateProbability()<<endl;
                    cout<<"Belt toString: "<<belt4.toString()<<endl;
                }

                else if(ChoiceWhichMethodInBelt==5){
                    cout<<"\nTesting createBelt Method"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Belt belt=Belt::createBelt("Belt5");
                    cout<<"Belt Name: "<<belt.getName()<<endl;
                    cout<<"Belt Type: "<<belt.getType()<<endl;
                    cout<<"Belt Enchantment Type: "<<belt.getEnchantmentType()<<endl;
                    cout<<"Belt Enchantment Level: "<<belt.getEnchantmentLevel()<<endl;
                    cout<<"Belt ID: "<<belt.getItemID()<<endl;
                    cout<<"Belt Placed: "<<belt.isPlaced()<<endl;
                    cout<<"Belt Probability: "<<belt.generateProbability()<<endl;
                    cout<<"Belt toString: "<<belt.toString()<<endl;
                }

                ChoiceWhichMethodInBelt=testCinForItemMethods();
            }
        }

        if(ChoiceWhichItemClass==6){
            cout<<"\nTesting Boots Class"<<endl;
            cout<<"-------------------"<<endl<<endl;

            printItemsMethods();

            int ChoiceWhichMethodInBoots=testCinForItemMethods();

            while(ChoiceWhichMethodInBoots!=0){

                if(ChoiceWhichMethodInBoots==1){
                    cout<<"\nTesting Default Constructor"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Boots boots;
                    cout<<"Boots Name: "<<boots.getName()<<endl;
                    cout<<"Boots Type: "<<boots.getType()<<endl;
                    cout<<"Boots Enchantment Type: "<<boots.getEnchantmentType()<<endl;
                    cout<<"Boots Enchantment Level: "<<boots.getEnchantmentLevel()<<endl;
                    cout<<"Boots ID: "<<boots.getItemID()<<endl;
                    cout<<"Boots Placed: "<<boots.isPlaced()<<endl;
                    cout<<"Boots Probability: "<<boots.generateProbability()<<endl;
                    cout<<"Boots toString: "<<boots.toString()<<endl;
                }

                else if(ChoiceWhichMethodInBoots==2){
                    cout<<"\nTesting Constructor with Parameters"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Boots boots("Boots2", "Enchantment1", 1);
                    cout<<"Boots Name: "<<boots.getName()<<endl;
                    cout<<"Boots Type: "<<boots.getType()<<endl;
                    cout<<"Boots Enchantment Type: "<<boots.getEnchantmentType()<<endl;
                    cout<<"Boots Enchantment Level: "<<boots.getEnchantmentLevel()<<endl;
                    cout<<"Boots ID: "<<boots.getItemID()<<endl;
                    cout<<"Boots Placed: "<<boots.isPlaced()<<endl;
                    cout<<"Boots Probability: "<<boots.generateProbability()<<endl;
                    cout<<"Boots toString: "<<boots.toString()<<endl;
                }

                else if(ChoiceWhichMethodInBoots==3){
                    cout<<"\nTesting Copy Constructor"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Boots boots("Boots3", "Enchantment1", 1);
                    Boots copyboots3(boots);
                    cout<<"Boots Name: "<<copyboots3.getName()<<endl;
                    cout<<"Boots Type: "<<copyboots3.getType()<<endl;
                    cout<<"Boots Enchantment Type: "<<copyboots3.getEnchantmentType()<<endl;
                    cout<<"Boots Enchantment Level: "<<copyboots3.getEnchantmentLevel()<<endl;
                    cout<<"Boots ID: "<<copyboots3.getItemID()<<endl;
                    cout<<"Boots Placed: "<<copyboots3.isPlaced()<<endl;
                    cout<<"Boots Probability: "<<copyboots3.generateProbability()<<endl;
                    cout<<"Boots toString: "<<copyboots3.toString()<<endl;
                }

                else if(ChoiceWhichMethodInBoots==4){
                    cout<<"\nTesting Assignment Operator"<<endl;
                    cout<<"-------------------"<<endl<<endl;
                
                    Boots boots("Boots4", "Enchantment1", 1);                           
                    Boots boots4=boots;                               
                    cout<<"Boots Name: "<<boots4.getName()<<endl;
                    cout<<"Boots Type: "<<boots4.getType()<<endl;
                    cout<<"Boots Enchantment Type: "<<boots4.getEnchantmentType()<<endl;
                    cout<<"Boots Enchantment Level: "<<boots4.getEnchantmentLevel()<<endl;
                    cout<<"Boots ID: "<<boots4.getItemID()<<endl;
                    cout<<"Boots Placed: "<<boots4.isPlaced()<<endl;
                    cout<<"Boots Probability: "<<boots4.generateProbability()<<endl;
                    cout<<"Boots toString: "<<boots4.toString()<<endl;
                }

                else if(ChoiceWhichMethodInBoots==5){
                    cout<<"\nTesting createBoots Method"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Boots boots=Boots::createBoots("Boots5");
                    cout<<"Boots Name: "<<boots.getName()<<endl;
                    cout<<"Boots Type: "<<boots.getType()<<endl;
                    cout<<"Boots Enchantment Type: "<<boots.getEnchantmentType()<<endl;
                    cout<<"Boots Enchantment Level: "<<boots.getEnchantmentLevel()<<endl;
                    cout<<"Boots ID: "<<boots.getItemID()<<endl;
                    cout<<"Boots Placed: "<<boots.isPlaced()<<endl;
                    cout<<"Boots Probability: "<<boots.generateProbability()<<endl;
                    cout<<"Boots toString: "<<boots.toString()<<endl;
                }

                ChoiceWhichMethodInBoots=testCinForItemMethods();

            }
        }

        if(ChoiceWhichItemClass==7){
            cout<<"\nTesting Weapon Class"<<endl;
            cout<<"-------------------"<<endl<<endl;

            printItemsMethods();

            int ChoiceWhichMethodInWeapon=testCinForItemMethods();

            while(ChoiceWhichMethodInWeapon!=0){

                if(ChoiceWhichMethodInWeapon==1){
                    cout<<"\nTesting Default Constructor"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Weapon weapon;
                    cout<<"Weapon Name: "<<weapon.getName()<<endl;
                    cout<<"Weapon Type: "<<weapon.getType()<<endl;
                    cout<<"Weapon Enchantment Type: "<<weapon.getEnchantmentType()<<endl;
                    cout<<"Weapon Enchantment Level: "<<weapon.getEnchantmentLevel()<<endl;
                    cout<<"Weapon ID: "<<weapon.getItemID()<<endl;
                    cout<<"Weapon Placed: "<<weapon.isPlaced()<<endl;
                    cout<<"Weapon Probability: "<<weapon.generateProbability()<<endl;
                    cout<<"Weapon toString: "<<weapon.toString()<<endl;
                }

                else if(ChoiceWhichMethodInWeapon==2){
                    cout<<"\nTesting Constructor with Parameters"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Weapon weapon("Weapon2", "Enchantment1", 1);
                    cout<<"Weapon Name: "<<weapon.getName()<<endl;
                    cout<<"Weapon Type: "<<weapon.getType()<<endl;
                    cout<<"Weapon Enchantment Type: "<<weapon.getEnchantmentType()<<endl;
                    cout<<"Weapon Enchantment Level: "<<weapon.getEnchantmentLevel()<<endl;
                    cout<<"Weapon ID: "<<weapon.getItemID()<<endl;
                    cout<<"Weapon Placed: "<<to_string(weapon.isPlaced())<<endl;
                    cout<<"Weapon Probability: "<<weapon.generateProbability()<<endl;
                    cout<<"Weapon toString: "<<weapon.toString()<<endl;
                }

                else if(ChoiceWhichMethodInWeapon==3){
                    cout<<"\nTesting Copy Constructor"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Weapon weapon("Weapon3", "Enchantment1", 1);
                    Weapon copyweapon3(weapon);
                    cout<<"Weapon Name: "<<copyweapon3.getName()<<endl;
                    cout<<"Weapon Type: "<<copyweapon3.getType()<<endl;
                    cout<<"Weapon Enchantment Type: "<<copyweapon3.getEnchantmentType()<<endl;
                    cout<<"Weapon Enchantment Level: "<<copyweapon3.getEnchantmentLevel()<<endl;
                    cout<<"Weapon ID: "<<copyweapon3.getItemID()<<endl;
                    cout<<"Weapon Placed: "<<to_string(copyweapon3.isPlaced())<<endl;
                    cout<<"Weapon Probability: "<<copyweapon3.generateProbability()<<endl;
                    cout<<"Weapon toString: "<<copyweapon3.toString()<<endl;
                }

                else if(ChoiceWhichMethodInWeapon==4){
                    cout<<"\nTesting Assignment Operator"<<endl;
                    cout<<"-------------------"<<endl<<endl;
                
                    Weapon weapon("Weapon4", "Enchantment1", 1);                           
                    Weapon weapon4=weapon;                               
                    cout<<"Weapon Name: "<<weapon4.getName()<<endl;
                    cout<<"Weapon Type: "<<weapon4.getType()<<endl;
                    cout<<"Weapon Enchantment Type: "<<weapon4.getEnchantmentType()<<endl;
                    cout<<"Weapon Enchantment Level: "<<weapon4.getEnchantmentLevel()<<endl;
                    cout<<"Weapon ID: "<<weapon4.getItemID()<<endl;
                    cout<<"Weapon Placed: "<<to_string(weapon4.isPlaced())<<endl;
                    cout<<"Weapon Probability: "<<weapon4.generateProbability()<<endl;
                    cout<<"Weapon toString: "<<weapon4.toString()<<endl;
                }

                else if(ChoiceWhichMethodInWeapon==5){
                    cout<<"\nTesting createWeapon Method"<<endl;
                    cout<<"-------------------"<<endl<<endl;

                    Weapon weapon=Weapon::createWeapon("Weapon5");
                    cout<<"Weapon Name: "<<weapon.getName()<<endl;
                    cout<<"Weapon Type: "<<weapon.getType()<<endl;
                    cout<<"Weapon Enchantment Type: "<<weapon.getEnchantmentType()<<endl;
                    cout<<"Weapon Enchantment Level: "<<weapon.getEnchantmentLevel()<<endl;
                    cout<<"Weapon ID: "<<weapon.getItemID()<<endl;
                    cout<<"Weapon Placed: "<<to_string(weapon.isPlaced())<<endl;
                    cout<<"Weapon Probability: "<<weapon.generateProbability()<<endl;
                    cout<<"Weapon toString: "<<weapon.toString()<<endl;
                }

                ChoiceWhichMethodInWeapon=testCinForItemMethods();
            }

        }

        cout<<"\nYour choice of Item Class: ";
        printItemsOptions();
        
        ChoiceWhichItemClass=testCinForItemClasses();

    }
            
    cout<<"Ending Program"<<endl;
};

static void premadeTestCases(){
    Backpack* backpack1 = new Backpack("yes",20);
    TreasureChest* chest1=new TreasureChest("chest1",20);

    cout<<backpack1->getCapacity()<<endl<<endl;
    cout<<backpack1->getSize()<<endl<<endl;

    Helmet helmet1=Helmet::createHelmet("Helmet 1");   
    Boots boot1=Boots::createBoots("Boot 1");
    Armor armor1=Armor::createArmor("Armor 1");
    Shield shield1=Shield::createShield("Shield 1");
    Ring ring1=Ring::createRing("Ring 1");
    Weapon weapon1=Weapon::createWeapon("Weapon 1");

    Helmet helmet2=Helmet::createHelmet("Helmet 2");
    Boots boot2=Boots::createBoots("Boot 2");
    Armor armor2=Armor::createArmor("Armor 2");
    Shield shield2=Shield::createShield("Shield 2");
    Ring ring2=Ring::createRing("Ring 2");
    Weapon weapon2=Weapon::createWeapon("Weapon 2");

    chest1->addItem(&helmet1);
    chest1->addItem(&boot1);
    chest1->addItem(&armor1);
    chest1->addItem(&shield1);
    chest1->addItem(&ring1);
    chest1->addItem(&weapon1);

    cout<<chest1->getSize()<<endl<<endl;

    chest1->addItem(&helmet2);

    chest1->addItem(&helmet1);
    chest1->addItem(&helmet2);
    chest1->addItem(&boot1);
    chest1->addItem(&armor2);

    cout<<chest1->getSize()<<endl<<endl;

    chest1->printSortedItemsByType("Helmet");

    chest1->printItems();

    chest1->removeItem(&helmet1);
    chest1->removeItem(&armor1);

    chest1->printItems();

    backpack1->addItem(&helmet1);
    backpack1->addItem(&helmet2);
    backpack1->addItem(&armor1);

    cout<<backpack1->getSize()<<endl;
    
    backpack1->printItems();

    cout<<"-------------------"<<endl;
}
//int main(){
//    srand(static_cast<unsigned int>(time(nullptr)));
//
//    premadeTestCases();
//
//    return 0;
//}