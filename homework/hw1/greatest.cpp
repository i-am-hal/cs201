/* Alastar Slater
 * greatest.cpp
 * Jan 27, 2020
 * CS 201
*/
#include <iostream>
using std::cout;
using std::endl;
using std::cin;

int main () {
    int greatest = 0;
    int input;

    cout << "Enter a sequence of positive integers, ending with zero." << endl;
    cout << "I will print the greatest positive number entered." << endl;

    do {
        cout << "Enter a positive integer (0 to end): ";
        cin >> input;

        //If the user entered a negative number, request another positive integer
        if (input < 0) {
            cout << endl << input << " is negative, please give only positve integers." << endl;
            return 1;

        //If entered number is greater than greatest saved number, save it
        } else if (input > greatest)
            greatest = input;

    } while (input > 0);

    cout << endl << "The greatest number entered: " << greatest << endl;

    return 0;
}