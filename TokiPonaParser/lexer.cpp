/* Alastar Slater
 * April 7, 2021
 * CS201
 * lexer.cpp
 * Describes the lexer which will be used
 * in the Toki Pona parser. Will have the
 * defintiions for a Token (word), and also
 * have a routine to identify parts to speech. */
#include <iostream>
#include <ostream>
#include <utility>
#include <vector>
#include <string>
using std::make_pair;
using std::ostream;
using std::string;
using std::vector;
using std::cout;
using std::pair;

//Token types, end of line, verb, preposition, modifer, 
// (pro)noun, and name. Contains key seperator words in
// the language. 
// pi - of, connects two noun phrases.
// la - connects two utterances.
// li - marks start of main verb.
// e  - marks start of direct object.
// o  - command, addressing.
enum TokenType {
    Eol=0, 
    Unknown,
    Period,
    Comma,
    Question,
    Exclaim, 
    Verb, Prep, 
    Mod, Noun,
    Pronoun, Name,
    La, Li, Pi,
    E, O, Anu, 
    Seme, En, 
    Preverb, Mu
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

        //Moves character head forward one, updates currChar.
        void advance() {
            pos++;

            //If the pos is still within text size, get character
            if (pos < text.size()) {
                currChar = text.at(pos);

            } else { //Mark end of input
                currChar = '\0';
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
            while (!isspace(currChar) && !isPunctuation(currChar) && currChar != '\0') {
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
        bool   error;
        string errorStr;

        //Creates the lexer, only needs the text which should be fed through
        Lexer(string inputText) {
            text = inputText; //Store away the text, to be used to lexer.
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
            return newToken(Eol, "Eol");
        }
};


/* ~{ OBJECT / TYPE PRINTING SUPPORT }~ */

//Print out tokentype in a more pleasant way
ostream &operator<<(ostream &out, TokenType tokenType) {
    vector<string> outputForm = {
        "Eol", "Unknown", "Period",
        "Comma", "Question", "Exclaim", 
        "Verb", "Prep", "Mod", "Noun",
        "Pronoun", "Name", "La", "Li", 
        "Pi", "E", "O", "Anu", "Seme", "En", 
        "Preverb", "Mu"
    };

    return out << outputForm.at(tokenType);
}

//Overwhite printing operator so that we can print out token
ostream &operator<<(ostream &out, Token token) {
    return out << "Token {" << token.tokenType << ", '" << token.value << "'}";
}


/* ~{ TOKI PONA COMPLETE VOCABULARY }~ */

//Defines a macro, ENTRY, used to enter in vocabulary. Makes it simpler.
#define WORD(word, ...)  make_pair(word, ((vector<TokenType>) __VA_ARGS__))
#define N(word)          WORD(word,{Noun})                  //Defines a Noun, only a noun
#define M(word)          WORD(word,{Mod})                   //Defines only a Modifier
#define V(word)          WORD(word,{Verb})                  //Defines only a Verb
#define Pv(word)         WORD(word,{Preverb})               //Defines only a Preverb
#define VM(word)         WORD(word,{Verb,Mod})              //Defines word that is verb, and modifier
#define NV(word)         WORD(word,{Noun,Verb})             //Defines a word that is a noun and a verb
#define NM(word)         WORD(word,{Noun,Mod})              //Defines that is a noun, and modifier
#define NMV(word)        WORD(word,{Noun,Mod,Verb})         //Defines word that is a noun, modifier, and verb
#define PNMV(word)       WORD(word,{Prep,Noun,Mod,Verb})    //Defines word that is a prep, noun, modifier, and verb
#define NMPV(word)       WORD(word,{Preverb,Verb,Mod,Noun}) //Defines word that is a noun, mod, preverb, and verb
#define PNM(word)        WORD(word,{Prep,Mod,Noun})         //Defines a preposition, mod, noun

//A vector of pairs, where each pair is a vocabulary word, and the
// second element says what parts of speech it can act as
const auto VOCAB = {
    M("a"), N("akesi"), M("ala"), V("alasa"), NM("ali"), NMV("anpa"), NMV("ante"),
    WORD("anu", {Anu}), NMPV("awen"), WORD("en", {En}), NMV("esun"), NM("ijo"),
    NMV("ike"), NM("ilo"), NM("insa"), NMV("jaki"), NM("jan"), NMV("jelo"),
    WORD("jo",{Verb}), //Unconventual for it to be used as a noun
    N("kala"), NMV("kalama"), WORD("kama",{Preverb,Verb,Noun}), N("kasi"),
    WORD("ken",{Preverb,Noun,Mod}), WORD("kepeken",{Prep,Verb,Noun}), N("kili"),
    NM("kiwen"), N("ko"), NM("kon"), NMV("kule"), NM("kulupu"), NMV("kute"),
    NMV("lape"), NMV("laso"), NMV("lawa"), NMV("len"), NMV("lete"), NMV("lili"),
    N("linja"), NM("lipu"), NMV("loje"), PNMV("lon"), N("luka"), NMPV("lukin"),
    N("lupa"), N("ma"), NV("mama"), NM("mani"), NM("meli"), NM("mije"), NMV("moku"),
    NMV("moli"), NM("monsi"), WORD("mu",{Mu}), NM("mun"), NMV("musi"), NM("mute"), 
    NM("nanpa"), M("nasa"), WORD("nasin",{Noun,Mod}), //Unconventional for it to be used as a verb
    NM("nena"), N("nimi"), N("noka"), NMV("olin"), NMPV("open"), NMV("pakala"),
    NMV("pali"), NM("palisa"), N("pan"), VM("pana"), NMV("pilin"), NMV("primeja"),
    NMPV("pini"), N("pipi"), NM("poka"), NV("poki"), NMV("pona"), NMV("pu"), PNM("sama"),
    NMV("seli"), NM("selo"), WORD("seme",{Seme}), NM("sewi"), NM("sijelo"), NMV("sike"),
    NMV("sin"), NM("sinpin"), NMV("sitelen"), NMPV("sona"), N("soweli"), NMV("suli"),
    NMV("suno"), N("supa"), WORD("suwi",{Mod}), //Unconventionally used as a noun
    PNMV("tan"), M("tan"), PNMV("tawa"), NMV("telo"), NM("tenpo"), NMV("toki"), 
    NM("tomo"), NMV("tu"), NMV("unpa"), NM("uta"), NMV("utala"), NMV("walo"),
    NMV("wan"), N("waso"), NMV("wawa"), NMV("weka"), NMPV("wile")
};

//A vector of pairs. This will have the synonyms, and tell
// what to replace that word with (remove synonyms)
const auto SYNONYMS = {
    make_pair("kin", "a"), make_pair("ale", "ali"),
    make_pair("oko", "lukin"), make_pair("namako", "sin")
};

//Go through all of the synonyms and see if this word is a synonym
bool isSynonym(string word) {
    for (pair<string, string> synPair : SYNONYMS) {
        if (synPair.first == word)
            return true;
    }
    return false;
}

//Go through the list of vocabulary, return true if this word is part of vocab
bool isVocabWord(string word) {
    for (pair<string, vector<TokenType>> vocabPair : VOCAB) {
        if (vocabPair.first == word)
            return true;
    }
}


/* ~{ }~ */

int main() {
    Lexer lexer = Lexer("um[pa. uka mupa!?");

    Token tok = lexer.nextToken();

    while (tok.tokenType != Eol) {
        cout << tok << std::endl;
        tok = lexer.nextToken();
    }

    return 0;
}

