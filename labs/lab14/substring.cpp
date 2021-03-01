/* Alastar Slater
 * Feb 24, 2021
 * substring.cpp
 * Given a string from user, print it out on a series
 * of lines in which it gets one character shorter. */
#include "substring.hpp"

int main() {
    string userInput = getString();
    printTextShortening(userInput);

    return 0;
}