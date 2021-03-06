/* Alastar Slater
 * Feb 17, 2021
 * boxer.hpp
 * This file contains the various functions required
 * for the boxer program (gets numerical input on the
 * size of the box, and a message to display within it
 * and then prints this box based on the specifications). 
*/

#pragma once
#include <iostream>
#include <string>
using std::getline;
using std::string;
using std::stoi;
using std::cout;
using std::endl;
using std::cin;

//If given string reference is not made of only digits,
//then return false (not positive integer)
bool isPositiveInt(string &str) {
    for (char chr: str) 
        if (!(chr >= '0' && chr <= '9'))
            return false;
    
    return true;
}

//For use of boxer program, gets a positive integer > 0, will only
//succeed once the user have given an integer that we can use 
int getPositiveInt() {
    string userInput;  //Raw string input from the user
    int numInput = -1; //The input converted into an integer

    do {
        cout << "Please enter an integer greater than zero: ";
        getline(cin, userInput);

        //Check if user gave a positive integer, if not, give error
        if (!isPositiveInt(userInput)) {
            cout << endl << "Malformed input, an integer greater than 0 is needed." << endl;

        } else //Otherwise, convert string into integer
            numInput = stoi(userInput);
    } while (numInput <= 0);

    return numInput;
}

//Prompts the user to input a line of text which they'd like to be
//in the box that we shall print to their specifications later.
string getBoxString() {
    string userInput;
    cout << "Enter the text desired to be within the box: ";
    getline(cin, userInput);
    return userInput;
}

//Prints a given number of asterisks (stars), this will
// allow us to reduce the amount of boilerplate code 
void printStars(int numOfStars) {
    while (numOfStars > 0) {
        cout << "*";
        numOfStars--;
    }
}

/* Prints out the given text between `boxSize` number of stars
   with two spaces between them (so that we can easily see text)

   Example: printTextInBox(2, "help")
                   ** help **
*/
void printTextInBox(int boxSize, string boxedText) {
    printStars(boxSize);
    cout << " " << boxedText << " ";
    printStars(boxSize);
    cout << endl; //End off this line
}

/* Given the number of stars per line, and the number of lines
   that need to be printed, prints N number of lines w/ X stars in them
   
   Example: printStarLines(2, 10)
                **********
                **********
*/
void printStarLines(int numOfStars, int numOfLines) {
    while (numOfLines > 0) {
        printStars(numOfStars);
        cout << endl; // Stop this line of stars
        numOfLines--;
    }
}

/* Given the size of the box (thickness of the walls), and
   the text to be placed therein, it prints the box based
   on those parameters.

   Example:   printBoxedText(2, "help")

                    **********
                    **********
                    ** help **
                    **********
                    **********
*/
void printBoxedText(int boxSize, string boxedText) {
    //Calculates the length of the stars on either side of text
    int boxCapSize = 2 * boxSize + 2 + boxedText.size();

    printStarLines(boxCapSize, boxSize); //Print top star cap above text
    printTextInBox(boxSize, boxedText); //Print the middle line w/ the text in it.
    printStarLines(boxCapSize, boxSize); //Print bottom star cap below text
}

