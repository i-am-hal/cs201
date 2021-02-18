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

//Given an integer, n, if it is even, return n/2,
// otherwise (if odd) return 3n + 1
int collatz(int n) {
    if (n % 2 == 0)
        return n / 2;
    
    else
        return 3 * n + 1;
}

//
void collatzSequence(int n) {
    while (n != 1) {
        cout << n << " "; //Print out current collatz term
        n = collatz(n);   //Apply collatz to get next term
    }
    cout << n << endl;
}

int main() {
    return 0;
}