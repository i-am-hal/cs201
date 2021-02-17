/* Alastar Slater
 * Feb 17, 2021
 * boxer.hpp
 * This file contains the various functions required
 * for the boxer program (gets numerical input on the
 * size of the box, and a message to display within it
 * and then prints this box based on the specifications). 
*/

#include <iostream>
#include <string>
using std::getline;
using std::string;
using std::stoi;
using std::cout;
using std::endl;
using std::cin;

//For use of boxer program, gets a positive integer > 0, will only
//succeed once the user have given an integer that we can use 
int getPositiveInt() {
    string userInput;  //Raw string input from the user
    int numInput = -1; //The input converted into an integer

    do {
        cout << "Please enter an integer greater than zero: ";
        getline(cin, userInput);
        numInput = stoi(userInput);
    } while (numInput <= 0);

    return numInput;
}