/* Alastar Slater
 * March 1, 2021
 * tokenizer.hpp */
#include <iostream>
#include <string>
using std::string;
using std::getline;
using std::endl;
using std::cout;
using std::cin;

//Will get a line from the user, store it into a variable, and
// return true if input isn't just spaces, false if otherwise.
bool ReadLine(string &str) {
    getline(cin, str); //Get a line of input from the user.

    //If string is of zero length, just return false
    if (str.size() == 0) return false;

    bool notJustSpaces = false; 

    //Go through each character, and if a character isn't a
    // whitespace character, update variale to true denoting
    // that this string isn't just whitespace
    for(char chr: str) {
        if (chr >= 33)
            notJustSpaces = true;
    }

    return notJustSpaces;
}



