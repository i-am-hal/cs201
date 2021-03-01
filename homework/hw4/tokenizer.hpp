/* Alastar Slater
 * March 1, 2021
 * tokenizer.hpp */
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using std::istringstream;
using std::vector;
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

//Given input from the user, chop up the input into lexemes, 
//and return the number of tokens found in the given user input.
unsigned StringToTokenWS(const string &input, vector<string> &tokens) {
    istringstream inputStream(input); //Input stream to read from
    string token;                     //Currently read token from stream
    unsigned tokenNumber = 0;         //Number of tokens processed

    //While able to w/o error, continously add each token from stream
    while (inputStream >> token) {
        tokens.push_back(token);
        tokenNumber++;
    }
    
    //Denote the end of this line.
    tokens.push_back("");

    return tokenNumber;
}

//Given the stream of tokens, it will analyze each one and print
//what `kind` of lexeme it is for the user to see.
void AnalyzeTokens(const vector<string> &tokens) {

}

