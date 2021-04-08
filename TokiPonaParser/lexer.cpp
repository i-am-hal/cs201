/* Alastar Slater
 * April 7, 2021
 * CS201
 * lexer.cpp
 * Describes the lexer which will be used
 * in the Toki Pona parser. Will have the
 * defintiions for a Token (word), and also
 * have a routine to identify parts to speech. */
#include <algorithm>
#include <string>
using std::transform;
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
    Comma,
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

//Takes a string, makes it all lowercase
string toLower(string str) {
    for(int i=0; i<str.size(); i++)
        str[i] = tolower(str.at(i));
    
    return str;
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

        //Skips over all whitespace characters
        void skipWhitespace() {
            //While char is whitespace, skip over it
            while (isspace(currChar))
                advance();
        }

        //Returns true if this character is a part of punctuation or not
        bool isPunctuation(char chr) {
            return chr == '.' || chr == ',' || chr == '?' || chr == '!';
        }

        //Gets a bunch of characters that are seperated by
        // whitespace or punctuation
        Token getWord() {
            string value = "";

            //Get all of the characters while the current character
            // is neither whitespace, nor punctuation marks
            while (!isspace(currChar) && !isPunctuation(currChar)) {
                value.push_back(currChar);
                advance();
            }

            //Make the string all lowercase
            string lowerVal = toLower(value);

            /* CHECK FOR A FEW IMPORTANT PARTICLE WORDS */

            //Catch if this is the direct object marker
            if (lowerVal == "e")
                return newToken(E, value);
            
            //Catch if this is the command / addressing
            else if (lowerVal == "o")
                return newToken(O, value);
            
            //Catch if this is the 'of' partcile
            else if (lowerVal == "pi")
                return newToken(Pi, value);
            
            //Catch if this is the main verb marker
            else if (lowerVal == "li")
                return newToken(Li, value);
            
            //Catch if this is the sentence connector
            else if (lowerVal == "la")
                return newToken(La, value);
            
            //If this is one of the pronouns, mark this premtively as a pronoun
            else if (lowerVal == "mi" || lowerVal == "ona" || lowerVal == "sina" || lowerVal == "ni")
                return newToken(Pronoun, lowerVal);
            
            else //Otherwise, show it as unknown for now
                return newToken(Unknown, value);
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
        Token nextToken() {
            //Continue trying to get a token while we can
            while (pos < text.size() && !error) {
                //If this is whitespace, skip over all whitespace
                if (isspace(currChar))
                    skipWhitespace();
                
                //Return period token
                else if (currChar == '.') {
                    advance();
                    return newToken(Period, ".");

                //Skip over comma
                } else if (currChar == ',') {
                    advance();
                    //return newToken(Comma, ",");

                //Return exclaimation mark token
                } else if (currChar == '!') {
                    advance();
                    return newToken(Exclaim, "!");

                //Return question mark token
                } else if (currChar == '?') {
                    advance();
                    return newToken(Question, "?");

                //Otherwise, try to get a word token
                } else {
                    return getWord();
                }
            }

            //Outside of bounds, or error, return Eol
            return newToken(Eol, "");
        }
};

