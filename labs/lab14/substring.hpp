/* Alastar Slater
 * Feb 24, 2021
 * substring.hpp */
#include <iostream>
#include <string>
using std::getline;
using std::string;
using std::cout;
using std::endl;
using std::cin;

//Gets a string from the user for us to later modify & print out..
string getString() {
    string input;

    cout << "Please enter a line of text: ";
    getline(cin, input);

    return input;
}

//Given a string, will print a series of lines of that text
// progressively becoming shorter, until one character long
void printTextShortening(string text) {
    for(int i = 0; i < text.size(); i++)
        cout << text.substr(0, text.size() - i) << endl;
}

