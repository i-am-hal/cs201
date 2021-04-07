/* Alastar Slater
 * April 7, 2021
 * CS201
 * lexer.cpp
 * Describes the lexer which will be used
 * in the Toki Pona parser. Will have the
 * defintiions for a Token (word), and also
 * have a routine to identify parts to speech. */
#include <string>
using std::string;

//Token types, end of line, verb, preposition, modifer, 
// (pro)noun, and name. Contains key seperator words in
// the language. 
// pi - of, connects two noun phrases.
// la - connects two utterances.
// li - marks start of main verb.
// e  - marks start of direct object.
// o  - command, addressing.
enum TokenType {
    Eol, 
    Unknown,
    Period,
    Question,
    Exclaim, 
    Verb, Prep, 
    Mod, Noun,
    Pronoun, Name,
    La, Li, Pi,
    E, O
};

//Defines a token, has a token type and a value.
struct Token {
    TokenType tokenType;
    string value;
};

//Creates a new instance of a token
Token newToken(TokenType type, string value) {
    return Token {type, value};
}

//Defines the lexer, which will go through some
// text, and split input into tokens
class Lexer {
    private:
        string text;
        int    pos;
        char   currChar;
        bool   error;
        string errorStr;
    
        //Moves character head forward one, updates currChar.
        void advance() {
            pos++;

            //If the pos is still within text size, get character
            if (pos < text.size()) {
                currChar = text.at(pos);
            }
        }
    
    public:
        //Creates the lexer, only needs the text which should be fed through
        Lexer(string text) {
            text = text; //Store away the text, to be used to lexer.
            pos = 0;
            error = false;

            //If text is nothing, make current char null
            if (text.size() == 0) {
                currChar = '\0';

            } else { //Otherwise, get first char in text
                currChar = text.at(0);
            }
        }

        //Lexer will attempt to get a new token to return.
        Token nextToken() {}
};

