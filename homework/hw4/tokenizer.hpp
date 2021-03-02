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

//Given a string, well tell the AnalyzeTokens function 
// if the string is a kind of recognized operator.
bool isOperator(const string &token) {
    if (token == "+" || token == "-" || token == "*" || token == "/" || token == "=")
        return true;
    else
        return false;
}

//Given a token, will test if the token is made up of 
// only digits and therefore, and integer constant
bool isInteger(const string &token) {
    //Not a bunch of characters, return false
    for (char chr: token) {
        if (!(chr >= '0' && chr <= '9'))
            return false;
    }
    return true;
}

//Given a character, return true if it is either A-Z (a-z) or an underscore
bool isAlpha(const char &chr) {
    return (chr >= 'A' && chr <= 'Z' || chr >= 'a' && chr <= 'z' || chr == '_');
}

//Given a string, will return true/faslse depending
// on this conforms to being an identifier.
bool isIdentifier(const string &token) {
    //If first character isn't a letter, or underscore, then not valid identifier
    if (!isAlpha(token.at(0)))
        return false;
    
    //If character neither a letter, underscore, or digit, return false
    for(char chr: token) {
        if (!(isAlpha(chr) || chr >= '0' && chr <= '9'))
            return false;
    }
    return true;
}

//Given a string, tests if the token is a string literal.
bool isString(const string &token) {
    //If token starts and ends with a double quote, it is a string
    if (token.at(0) == '"' && token.at(token.size()-1) == '"')
        return true;
    else
        return false;
}

//Given the stream of tokens, it will analyze each one and print
//what `kind` of lexeme it is for the user to see.
void AnalyzeTokens(const vector<string> &tokens) {
    for (const string &token: tokens) {
        //Detect what kind of thing the token is, identify it
        if (token == "")
            cout << "[Whitespace]";
        
        else if (isOperator(token))
            cout << "[Operator]";
        
        else if (isInteger(token))
            cout << "[Integer]";
        
        else if (isIdentifier(token))
            cout << "[Identifier]";
        
        else if (isString(token))
            cout << "[String]";
        
        else //Unable to tell what this token is
            cout << "[Other]";
        
        cout << "\t\t\t" << "\"" << token << "\"" << endl;
    }
}

//Given the current set of tokens, check if the keyword
// END is anywhere within (to see if we should end REPL)
bool endRepl(const vector<string> &tokens) {
    for (const string token: tokens) {
        if (token == "END" || token == "end" || token == "End")
            return true;
    }
    return false;
}

//This will be the repl (read-eval-print-loop) for our lexer.
//Will continously get input from user until they enter END
void repl() {
    vector<string> tokens;
    string input;

    //Prompt for the user to ensure that they know what is going on
    cout << "Please type in some text. When you are done, type \"End\", \"end\" or \"END\":" << endl;

    do {
        ReadLine(input); //Read a line of input from the user
        //Truncate input into a series of tokens..
        StringToTokenWS(input, tokens);
    //If the keyword 'END' occurs, end input loop 
    } while (!endRepl(tokens));

    //Print out all analyzed tokens from the lexer
    AnalyzeTokens(tokens);
}
