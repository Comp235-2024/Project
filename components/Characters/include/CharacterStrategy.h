//
// Created by ricka on 2024-03-17.
//

#ifndef A3_CHARACTERSTRATEGY_H
#define A3_CHARACTERSTRATEGY_H

#include "../../Items/include/Item.h"
#include "../../Maps/include/Map.h"
#include "../../Maps/include/MapObserver.h"
#include "Character.h"
#include "NonPlayerCharacter.h"
#include "Player.h"
#include "SFML/Graphics.hpp"
#include <string>

using namespace sf;


/**
 * @class CharacterStrategy
 * @brief Abstract class and base class for character strategies.
 */
class CharacterStrategy:public Character{
public:
    /**
     * @brief used by the npcs to know the location of the player
     */
    Player* player;
    NonPlayerCharacter* npc;
    Item* item;
    shared_ptr<Map> map;

    //TODO IMPLEMENT DEEP DESTRUCTOR
    ~CharacterStrategy()  override = default;
    virtual bool play()=0;

    /**
     * @brief method that checks if the character is in range to attack/interact with
     * @return
     */
    //TODO: IMPLEMENT INRANGE DEPENDING ON THE TYPE OF THE WEAPON EX: SWORD, BOW, ETC
    virtual bool inRange();
};

/**
 * @class HumanPlayerStrategy
 * @brief Represents what the human user will be able to do in their round.

 */
class HumanPlayerStrategy : public CharacterStrategy{
public:
    explicit HumanPlayerStrategy(Player*);

    //TODO IMPLEMENT DEEP DESTRUCTOR
    ~HumanPlayerStrategy() override=default;

    //TODO IMPLEMENT PLAY FUNCTION WITH EXISTING WINDOW
    static bool play(sf::RenderWindow&) ;
    bool play() override;

    /**
     * @brief method that moves the player given the passed pressed key event
     * @return
     */
    bool move(sf::Event) ;

    /**
     * @brief method that moved the player given the passed string representation of an event
     * @return
     */
    bool move(string);

    /**
     * @brief method that attacks the npc
     * @return
     */
    bool attack(NonPlayerCharacter*);

    /**
     * @brief method that lets the user interact with their backpack and worn items
     * @return
     */
    bool freeAction(int);

    void setWindowSize(int, int,float&,float&);

};

class NonPlayerAggressorStrategy : public CharacterStrategy{
public:
    //TODO IMPLEMENT CONSTRUCTOR
    explicit NonPlayerAggressorStrategy(Player*, NonPlayerCharacter*, Map*);

    //TODO IMPLEMENT DESTRUCTOR
    ~NonPlayerAggressorStrategy() override=default;

    /**
     * @brief method that plays the npc's turn depending on its strategy
     * @return if successful
     */
    bool play() override;

    /**
     * @brief method that moves the npc closer to the player by finding the shortest path
     * @return
     */
    bool move();

    /**
     * @brief method that attacks the player if in range
     * @return
     */
    bool attack();
    
};

class NonPlayerFriendlyStrategy : public CharacterStrategy{
private:
    /**
     * @brief state of the npc whether still friendly or whether it has switched to aggressor
     */
    string state;
    
public:
    //TODO IMPLEMENT CONSTRUCTOR
    explicit NonPlayerFriendlyStrategy(Player*, NonPlayerCharacter*, Map*);

    //TODO IMPLEMENT DESTRUCTOR
    ~NonPlayerFriendlyStrategy() override;

    /**
     * @brief method that plays the npc's turn depending on its strategy
     * @return
     */
    bool play() override;

    /**
     * @brief method that moves the npc closer to the player by finding the shortest path
     * @return
     */
    bool move();

    /**
     * @brief method that attacks the player if in range
     * @return
     */
    bool attack();

    /**
     * @brief method that returns the state of the npc
     * @return
     */
    string getState();

    /**
     * @brief method that switches the npc to aggressor
     */
    void switchToAggressor();
};


#endif//A3_CHARACTERSTRATEGY_H
