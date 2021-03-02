/* Alastar Slater 
 * March 1, 2021
 * tokenizertest.cpp */

#include "tokenizer.hpp"

//All of the premade test strings to see how well the program
// converts inputs into a series of tokens in a list.
const vector<string> stringToTokensTests = {
    "print \"Hello!\"",
    "FOR I = 1 TO 5 DO X = X * I END",
    "begin \"Wow\" End",
    "program testing x = 42 print x end"
};

//Each of the corresponding resulting token lists 
// from the various abive inputs to be processed.
const vector<vector<string>> corrTokenTests = {
    {"print", "\"Hello!\""},
    {"FOR", "I", "=", "1", "TO", "5", "DO", "X", "=", "X", "*", "I", "END"},
    {"begin", "\"Wow\"", "End"},
    {"program", "testing", "x", "=", "42", "print", "x", "end"}
};

//Given an input test string, return the set of tokens
// that are given back from the lexer when given this input.
vector<string> returnTokensFromString(const string &str) {
    vector<string> tokens;
    StringToTokenWS(str, tokens);
    return tokens;
};

//

int main() {
    cout << "TESTING LEXER (StringToTokensWS).." << endl;
    for (int i = 0; i < stringToTokensTests.size(); i++) {
        string testString = stringToTokensTests.at(i);         //Get the string to test
        vector<string> expectedResults = corrTokenTests.at(i); //Get corr expected results
        vector<string> returnedTokens = returnTokensFromString(testString);

        for (int j = 0; j < expectedResults.size(); j++) {
            string expectedToken = expectedResults.at(j);
            string returnedToken = returnedTokens.at(j);

            if (returnedToken != expectedToken) {
                cout << "Error: test input '" << testString << "' didn't result in expected output";
                cout << endl << "Where we expected the token '" << expectedToken << "' ";
                cout << "we instead got '" << returnedToken << "'" << endl;
                return 1;
            }
        }
    }
    cout << "All tests passed!" << endl;

    return 0;
}