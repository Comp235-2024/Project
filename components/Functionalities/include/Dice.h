/**
 * @file Dice.h
 * @author Melika Minaei Bidgoli
 * @date 2024-02-25
 *
 * 1) the dice rules: x and y should be included in the given rex with the
 * format: xdy[+z] but +z is optional. Also, the kinds of dices should be d4,
 * d6, d8, d10, d12, d20, or d100. If any of these rules are not respected the
 * program will show the error and exit the program.
 *
 * 2) Description of design: The program will roll the given rex string by first
 * parsing the rex by looking for the positions of "d", and possibly "+". It
 * will store the integer type of each x, y, and z in Dice attributes: number,
 * kind, addedValue. Afterwards, it will generate x random numbers in the range
 * of the dy of the dice and add the z if exists at the end and return it.
 *
 * 3) the libraries used in the code:
 * iostream: for printing output
 * string: for substring
 * cstdlib: generates a random number srand()
 * ctime: for using time, use the result of time(0) as the seed for generating
 * random number
 *
 */

#ifndef A3_DICE_H
#define A3_DICE_H

#include "../../Log/include/LogObservable.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

/**
 * @brief Class for the Dice in the game
 * @details
 */
class Dice : public LogObservable
//class Dice
{

private:
    /**
     * @brief int variable to keep track of the number of dice
     */
    int number;

    /**
     * @brief int variable to keep track of the kind of dice
     */
    int kind;
    /**
     * @brief int variable to keep track of the (possible) added value of dice
     */
    int addedValue;

public:
    /**
     * @brief Construct a new Dice objectl
     */
    Dice();

    /**
     * @brief Dice object destructor
     */
    ~Dice(){};

    /**
     * @brief Getter function for the number of the Dice object
     * @return int
     */
    int getNumber() const;

    /**
     * @brief Getter function for the kind of the Dice object
     * @return int
     */
    int getKind() const;

    /**
     * @brief Getter function for the added value of the Dice object
     * @return int
     */
    int getAddedValue() const;

    /**
     * @brief Set the number attribute of the Dice object
     * @param _numberOfDice
     */
    void setNumber(int _number);

    /**
     * @brief Set the kind attribute of the Dice object
     * @param _kindOfDice
     */
    void setKind(int _kind);

    /**
     * @brief Set the added value attribute of the Dice object
     * @param _addedValue
     */
    void setAddedValue(int _addedValue);

    /**
     * @brief converts given string to integer
     * @param string str
     * @return int number
     */
    int convert(string str);

    /**
     * @brief picks a random number based on the number, kind and added value
     * @return int generated number
     */
    int generateNumber();

    /**
     * @brief sets the number(x), kind(y) and addedValue of dice attributes
     * based on the format xdy[+z] and checks for any errors in the rex
     * @param rex
     */
    void parse(string rex);

    /**
     * @brief rolls the Dice by parsing the passed rex string,
     * and generating a random number based on it
     * @param rex
     */
    int roll(string rex);

    /**
     * @brief check if kind of dice is d4, d6, d8, d10, d12, d20, or d100
     * @return boolean valid or not
     */
    bool checkKindOfDice() const;

    /**
     * @brief test function for the Dice class
     * @param d
     */
    static void test(Dice d);
    /**
     * @brief Roll 4d6
     * @param number
     */
    int roll4d6DropLowest();
};

#endif
