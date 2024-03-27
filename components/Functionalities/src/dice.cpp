/**
 * @file Dice.cpp
 *
 * @author Melika Minaei Bidgoli
 *
 * @brief The dice are of the following kinds (d4, d6, d8, d10, d12, d20, d100)
 * The Dice class allows to roll any number of dice of one kind at once using
 * the following regular expression: xdy[+z] Where x is the number of dice of
 * the dy kind, optionally added with z after all the dice results have been
 * added.
 *
 * @version 0.1
 *
 * @date 2024-02-25
 *
 * @copyright Copyright (c) 2024
 */

// Including header file
#include "../include/Dice.h"
#include <algorithm>
#include <format>
#include <vector>
using namespace std;

/**
 * @brief Construct a new object Dice:: initialize Dice object with default 0
 * values
 */
Dice::Dice() {
    this->number = 0;
    this->kind = 0;
    this->addedValue = 0;
}

/**
 * @brief Returns the number of the dice object
 * @return int
 */
int Dice::getNumber() const { return this->number; }

/**
 * @brief Returns the kind of the dice object
 * @return int
 */
int Dice::getKind() const { return this->kind; }

/**
 * @brief Returns the added value of the dice object
 * @return int
 */
int Dice::getAddedValue() const { return this->addedValue; }

/**
 * @brief Set the number attribute of the Dice object
 * @param _numberOfDice
 */
void Dice::setNumber(int _numberOfDice) { this->number = _numberOfDice; }

/**
 * @brief Set the kind attribute of the Dice object
 * @param _kindOfDice
 */
void Dice::setKind(int _kindOfDice) { this->kind = _kindOfDice; }

/**
 * @brief Set the added value attribute of the Dice object
 * @param _addedValue
 */
void Dice::setAddedValue(int _addedValue) { this->addedValue = _addedValue; }

/**
 * @brief converts given string to integer
 * @param string str
 * @return int number
 */
int Dice::convert(string str) {
    int num = 0;
    int n = str.length();
    for (int i = 0; i < n; i++) {
        // Subtract 48 from the current digit in str to get integer of it
        num = num * 10 + (int(str[i]) - 48);
    }
    return num;
}

/**
 * @brief picks a random number based on the number, kind and added value
 * @return int generated number
 */
int Dice::generateNumber() {
    int sum = 0;
    srand(static_cast<unsigned int>(time(0))); // for generating random numbers
    for (int i = 0; i < number; i++) {
        int randNum = rand() % (kind - 1 + 1) + 1; // rand()%(max-min)+min
        sum += randNum;
    }
    return sum + addedValue;
}

/**
 * @brief sets the number(x), kind(y) and addedValue of dice attributes
 * based on the format xdy[+z] and checks for any errors in the rex
 * @param rex
 */
void Dice::parse(string rex) {
    // initialize the positions of "d" and "+" in the string
    int dPos = -1, additionPos = -1;
    // find "d" and "+" position in rex
    for (unsigned int i = 0; i < rex.size(); i++) {
        if (rex[i] == 'd') {
            if (dPos == -1) { // first time seeing "d" in rex, valid
                dPos = i;
            } else {
                cout << "Error in rex, more than one 'd'!" << endl;
                exit(1);
            }
        }
        if (rex[i] == '+') {
            if (additionPos == -1) { // first time seeing "+" in rex, valid
                additionPos = i;
            } else {
                cout << "Error in rex, more than one '+'!" << endl;
                exit(1);
            }
        }
    }
    if (dPos == -1) { // "d" must exist in rex, -1 shows no "d" was in rex
        cout << "Error in rex, no 'd's!" << endl;
        exit(1);
    }
    // "+" may or may not exist in rex
    if (additionPos == -1) { // "+" does not exist in rex, no added value
        setAddedValue(0);
        additionPos = rex.size(); // for the substring positions
    } else {                      // "+" exists in rex, set added value to it
        setAddedValue(
            convert(rex.substr(additionPos + 1, rex.size() - 1 - additionPos)));
    }
    setNumber(convert(rex.substr(0, dPos)));
    setKind(convert(rex.substr(dPos + 1, additionPos - dPos - 1)));
    if (!checkKindOfDice()) {
        cout << "Error in rex, kind of dice should be 4, 6, 8, 10, 12, 20, or "
                "100!"
             << endl;
        exit(1);
    }
}

/**
 * @brief rolls the Dice by parsing the passed rex string,
 * and generating a random number based on it
 * @param rex
 */
int Dice::roll(string rex) {
    parse(rex);
    int num = generateNumber();
    this->notify(std::format("Dice {} rolled and the result is {}. ", rex, num), "Dice");
    return num;
}

/**
 * @brief check if kind of dice is d4, d6, d8, d10, d12, d20, or d100
 * @return boolean valid or not
 */
bool Dice::checkKindOfDice() const {
    if (!(kind == 4 || kind == 6 || kind == 8 || kind == 10 || kind == 12 ||
          kind == 20 || kind == 100)) {
        return false;
    }
    return true;
}

/**
 * @brief for testing the functionality of Dice class
 * prints the attributes parsed from rex
 * and the output for each test case
 */
void Dice::test(Dice d) {
    int randomNum = 0;
    cout << "Testing rolling dice with format: xdy[+z]" << endl;
    cout << "Where x is the number of dice of the dy kind,\noptionally added "
            "with z after all the dice results have been added."
         << endl;
    cout << "--------------------------" << endl;
    randomNum = d.roll("1d6");
    cout << "x: " << d.getNumber() << " dy: d" << d.getKind()
         << " z: " << d.getAddedValue() << "\nGenerated number: " << randomNum
         << endl;
    cout << "--------------------------" << endl;
    randomNum = d.roll("8d100+90");
    cout << "x: " << d.getNumber() << " dy: d" << d.getKind()
         << " z: " << d.getAddedValue() << "\nGenerated number: " << randomNum
         << endl;
    cout << "--------------------------" << endl;
    randomNum = d.roll("1d4");
    cout << "x: " << d.getNumber() << " dy: d" << d.getKind()
         << " z: " << d.getAddedValue() << "\nGenerated number: " << randomNum
         << endl;
    cout << "--------------------------" << endl;
    randomNum = d.roll("3d6+5");
    cout << "x: " << d.getNumber() << " dy: d" << d.getKind()
         << " z: " << d.getAddedValue() << "\nGenerated number: " << randomNum
         << endl;
    cout << "--------------------------" << endl;
    randomNum = d.roll("7d20+700");
    cout << "x: " << d.getNumber() << " dy: d" << d.getKind()
         << " z: " << d.getAddedValue() << "\nGenerated number: " << randomNum
         << endl;
    cout << "--------------------------" << endl;
    randomNum = d.roll("7d100");
    cout << "x: " << d.getNumber() << " dy: d" << d.getKind()
         << " z: " << d.getAddedValue() << "\nGenerated number: " << randomNum
         << endl;
    cout << "--------------------------" << endl;
    randomNum = d.roll("5d8+10");
    cout << "x: " << d.getNumber() << " dy: d" << d.getKind()
         << " z: " << d.getAddedValue() << "\nGenerated number: " << randomNum
         << endl;
    cout << "--------------------------" << endl;
    randomNum = d.roll("2d10");
    cout << "x: " << d.getNumber() << " dy: d" << d.getKind()
         << " z: " << d.getAddedValue() << "\nGenerated number: " << randomNum
         << endl;
    cout << "--------------------------" << endl;
    randomNum = d.roll("20d12+1");
    cout << "x: " << d.getNumber() << " dy: d" << d.getKind()
         << " z: " << d.getAddedValue() << "\nGenerated number: " << randomNum
         << endl;
    cout << "--------------------------" << endl;
    randomNum = d.roll("30d20+0");
    cout << "x: " << d.getNumber() << " dy: d" << d.getKind()
         << " z: " << d.getAddedValue() << "\nGenerated number: " << randomNum
         << endl;
    cout << "--------------------------" << endl;
}

int Dice::roll4d6DropLowest() {
    std::vector<int> rolls(4);
    for (auto& roll : rolls) {
        roll = this->roll("1d6"); // Assuming roll method can handle single dice rolls
    }

    // Sort the rolls in ascending order
    std::sort(rolls.begin(), rolls.end());

    // Sum the three highest rolls
    return rolls[1] + rolls[2] + rolls[3];
}

//int main() {
//    Dice d;
//    test(d);
//    return 0;
//}
