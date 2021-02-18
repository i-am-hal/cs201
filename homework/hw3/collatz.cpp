/* Alastar Slater
 * Feb 17, 2021
 * collatz.cpp
 * This program periodically takes an integer input from the user
 * then applies the collatz function onto it until the sequence
 * terminates with the number 1.
*/

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

//Prompts the user for a number >= 0, will only stop
//when it gets a valid whole number.
int getNumber() {
    string rawInput;
    int numInput = -1;

    do {
        cout << "Please enter a positive number, or zero: ";
        getline(cin, rawInput);

        if (!isPositiveInt(rawInput)) {
            cout << endl << "The number must be greater than, or equal to zero." << endl;
            continue;

        } else
            numInput = stoi(rawInput);
    } while (numInput < 0);

    return numInput;
}

//Given an integer, n, if it is even, return n/2,
// otherwise (if odd) return 3n + 1
int collatz(int n) {
    if (n % 2 == 0)
        return n / 2;
    
    else
        return 3 * n + 1;
}

//Given an integer, n, apply the collatz function
// onto it, and printing the result, until n = 1.
void collatzSequence(int n) {
    while (n != 1) {
        cout << n << " "; //Print out current collatz term
        n = collatz(n);   //Apply collatz to get next term
    }
    cout << n << endl;    //Print 1, and end sequence's line
}

int main() {
    cout << "Enter zero (0) to quit program.. " << endl;

    while (true) {
        cout << endl; // Add a buffer between last line and this one
        int number = getNumber();

        //If the number is zero, stop loop
        if (number == 0) break;

        //Print out the collatz sequence of this number.
        collatzSequence(number);
    }

    cout << endl << "Goodbye." << endl;

    return 0;
}