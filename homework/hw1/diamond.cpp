/* Alastar Slater
 * diamond.cpp
 * Jan 25, 2020
 * CS 201
*/
#include <iostream>
#include <cstdlib>
using std::cin;
using std::endl;
using std::cout;
using std::abs;

int main () {
    int diamondWidth = 0; //Width of diamond, given by user.

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
    int numSpaces; //The number of spaces needed on either side of hashes
    int hashMaxima = charSize / 2; //Number at which we've hit maximum number of hashes

    //Print out each line of the diamond..
    for (int line = 0; line <= charSize; line++) {
        numSpaces = abs(hashMaxima - line); 

        //Print each column, changing based on how wide it should be
        for (int column = 1; column <= charSize; column++) {
            //If column is between the pair of 'space' buffers, print hashes
            if (column > numSpaces && column <= charSize-numSpaces) {
                cout << "#";
            
            //Otherwise, print out spaces for the buffers
            } else {
                cout << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
