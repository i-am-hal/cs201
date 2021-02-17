/* Alastar Slater
 * Feb 17, 2021
 * boxprint.cpp
 * This program gets the size of a box, and the text that
 * ought to be printed within it, and prints out a box
 * which conforms to those specifications.*/

#include <iostream>
#include <string>
#include "boxer.hpp"

int main() {
    int boxSize = getPositiveInt();
    string boxText = getBoxString();
    printBoxedText(boxSize, boxText);

    return 0;
}