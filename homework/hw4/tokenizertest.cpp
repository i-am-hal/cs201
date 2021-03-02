/* Alastar Slater 
 * March 1, 2021
 * tokenizertest.cpp */

#include "tokenizer.hpp"

//All of the premade test strings to see how well the program
// converts inputs into a series of tokens in a list.
const vector<string> stringToTokensTests = {
    "print \"Hello!\"",
    "FOR I = 1 TO 5 DO X = X * I END",
    "begin \"Wow\" end",
    "program testing x = 42 print x end"
};

//Given an input test string, return the set of tokens
// that are given back from the lexer when given this input.
vector<string> returnTokensFromString(const string &str) {
    vector<string> tokens;
    StringToTokenWS(str, tokens);
    return tokens;
}

int main() {
    return 0;
}