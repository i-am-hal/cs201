/* Alastar Slater
 * diamond.cpp
 * Jan 25, 2020
 * CS 201
*/
#include <iostream>
using std::cin;
using std::endl;
using std::cout;

int main () {
    int diamondWidth = 0; //Width of diamond, input by user.

    //Continuously prompt user for input until we get an integer > 0
    while (diamondWidth <= 0) {
        cout << "Please enter a non-zero integer: ";
        cin >> diamondWidth; // REPLACE W/ LINE ORIENTED INPUT

        //Complain to user, to ask them to correct malformed input.
        if (diamondWidth <= 0) 
            cout << "Integer must be greater than zero." << endl << endl;
    }

    //Calculate the size of the rows, and columns (in characters)
    int charSize = 2 * diamondWidth - 1;

}