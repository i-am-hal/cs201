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

//Start of definition of lexer.hpp
#ifndef LEXER_HPP
#define LEXER_HPP

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
    Preverb, Mu,
    IllegalUse
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

        Lexer() {
            error = true;
            errorStr = "mi sona ala e toki sina.";
        }

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

        //Deletes all of the info this object uses
        ~Lexer() {
            delete &text;
            delete &pos;
            delete &currChar;
            delete &error;
            delete &errorStr;
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

        //Make a list of all of the tokens generated.
        vector<Token> exhaustTokens() {
            vector<Token> tokens;
            Token tok = nextToken();

            //Get each token, add it to the list, until it is all
            while (tok.tokenType != Eol) {
                tokens.push_back(tok);
                tok = nextToken();
            }
            //Push an additional Eol at the end
            tokens.push_back(nextToken());

            return tokens;
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
        "Preverb", "Mu", "IllegalUse"
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
#define CON(word,role)   WORD(word,{role})                  //Defines a word with a constant role

//A vector of pairs, where each pair is a vocabulary word, and the
// second element says what parts of speech it can act as
const auto VOCAB = {
    M("a"), N("akesi"), M("ala"), V("alasa"), NM("ali"), NMV("anpa"), NMV("ante"),
    CON("anu",Anu), NMPV("awen"), CON("en",En), NMV("esun"), NM("ijo"),
    NMV("ike"), NM("ilo"), NM("insa"), NMV("jaki"), NM("jan"), NMV("jelo"),
    WORD("jo",{Verb}), //Unconventual for it to be used as a noun
    N("kala"), NMV("kalama"), WORD("kama",{Preverb,Verb,Noun}), N("kasi"),
    WORD("ken",{Preverb,Noun,Mod}), WORD("kepeken",{Prep,Verb,Noun}), N("kili"),
    NM("kiwen"), N("ko"), NM("kon"), NMV("kule"), NM("kulupu"), NMV("kute"),
    NMV("lape"), NMV("laso"), NMV("lawa"), NMV("len"), NMV("lete"), NMV("lili"),
    N("linja"), NM("lipu"), NMV("loje"), PNMV("lon"), N("luka"), NMPV("lukin"),
    N("lupa"), N("ma"), NV("mama"), NM("mani"), NM("meli"), NM("mije"), NMV("moku"),
    NMV("moli"), NM("monsi"), CON("mu",Mu), NM("mun"), NMV("musi"), NM("mute"), 
    NM("nanpa"), M("nasa"), WORD("nasin",{Noun,Mod}), //Unconventional for it to be used as a verb
    NM("nena"), N("nimi"), N("noka"), NMV("olin"), NMPV("open"), NMV("pakala"),
    NMV("pali"), NM("palisa"), N("pan"), VM("pana"), NMV("pilin"), NMV("primeja"),
    NMPV("pini"), N("pipi"), NM("poka"), NV("poki"), NMV("pona"), NMV("pu"), PNM("sama"),
    NMV("seli"), NM("selo"), CON("seme",Seme), NM("sewi"), NM("sijelo"), NMV("sike"),
    NMV("sin"), NM("sinpin"), NMV("sitelen"), NMPV("sona"), N("soweli"), NMV("suli"),
    NMV("suno"), N("supa"), WORD("suwi",{Mod}), //Unconventionally used as a noun
    PNMV("tan"), M("tan"), PNMV("tawa"), NMV("telo"), NM("tenpo"), NMV("toki"), 
    NM("tomo"), NMV("tu"), NMV("unpa"), NM("uta"), NMV("utala"), NMV("walo"),
    NMV("wan"), N("waso"), NMV("wawa"), NMV("weka"), NMPV("wile"), CON("e",E),
    CON("li",Li), CON("o",O), CON("pi",Pi), CON("la",La), CON("mi",Pronoun),
    CON("sina",Pronoun), CON("ni",Pronoun), CON("ona",Pronoun)
};

//A vector of pairs. This will have the synonyms, and tell
// what to replace that word with (remove synonyms)
const auto SYNONYMS = {
    make_pair("kin", "a"), make_pair("ale", "ali"),
    make_pair("oko", "lukin"), make_pair("namako", "sin")
};

//Check if the given word is part of the vocabulary.
bool isVocabWord(Token word) {
    for (const auto &entry : VOCAB) {
        if (entry.first == word.value) {
            return true;
        }
    }
    return false;
}

//Returns the vector of Word types, which describes what
// kinds of meanings this particular word (which is assumed)
// to exist.
vector<TokenType> getEntry(Token word) {
    for (const auto &entry : VOCAB) {
        if (entry.first == word.value)
            return entry.second;
    }
    return {Unknown};
}

//Returns true/false on if this word is ever this particular role
bool isWordRole(Token word, TokenType wordRole) {
    if (isVocabWord(word)) {
        //Find if this word is ever this role 
        for (const auto &role : getEntry(word)) {
            if (role == wordRole)
                return true;
        }
        //Doesn't have this role , return false
        return false;

    //If not vocab word, return false
    } else 
        return false;
}

//Return true/false if word can be a given part of speech
bool canBeNoun(Token word) { return isWordRole(word, Noun); }

bool canBePronoun(Token word) { return isWordRole(word, Pronoun); }

bool canBeMod(Token word) { return isWordRole(word, Mod); }

bool canBePreverb(Token word) { return isWordRole(word, Preverb); }

bool canBeVerb(Token word) { return isWordRole(word, Verb); }

bool canBeAnyVerb(Token word) { return canBeVerb(word) || canBePreverb(word); }

bool canBePrep(Token word) { return isWordRole(word, Prep); }

//Return true/false if this word is flagged for a particular role
bool isUnknown(Token word) { return word.tokenType == Unknown; }

bool isVerb(Token word) { return word.tokenType == Verb; }

bool isNoun(Token word) { return word.tokenType == Noun; }

bool isMod(Token word) { return word.tokenType == Mod; }

bool isPronoun(Token word) { return word.tokenType == Pronoun; }

bool isPreverb(Token word) { return word.tokenType == Preverb; }

bool isPrep(Token word) { return word.tokenType == Prep; }

//Return true if this character is a toki pona consosnant
bool isConsonant(char x) {
    switch (x) {
        case 'p':
        case 't':
        case 'k': 
        case 's':
        case 'm':
        case 'n':
        case 'l':
        case 'w':
        case 'j':
            return true;
            break;
        default:
            return false;
            break;
    }
}

//Return true if this character is one of toki pona's vowels
bool isVowel(char x) {
    return x == 'a' || x == 'e' || x == 'i' || x == 'o' || x == 'u';
}

//Returns true if this word is a toki ponized name
bool isTokiPonaName(string word) {
    bool isValidName   = true;
    bool testConsonant = true;
    int  startPos      = 0;
    int  endPos        = word.size();

    //If the first character is a vowel, skip it
    if (word.size() >= 1 && isVowel(word[0]))
        startPos++;
    
    //If last character is an 'n', stop before it
    if (word.at(endPos-1) == 'n')
        endPos--;
    
    //Go through each character, test consonant & vowel.
    // All names take the form (V) + (C)(V) + (n)
    // (An optional vowel at the start, optional vowel at the end,
    // and everthing between being consonant & vowel pairs)
    for (int i=startPos; i<endPos; i++) {
        char currChar = tolower(word.at(i));

        //If we are testing a consonant now, && w/ last result
        if (testConsonant) {
            isValidName = isValidName && isConsonant(currChar);
        
        //If we are testing a vowel now, && w/ last result
        } else {
            isValidName = isValidName && isVowel(currChar);
        }

        //Switch to testing either now a consonant, or now a vowel
        testConsonant = not testConsonant;
    }

    //Return result, the for loop should have eliminated any
    // words that aren't toki ponized names
    return isValidName;
}

//Returns true/false on if this word is a constant.
// A word is considered a constant if it is only ever
// one part of speech (ex: only a verb, only a noun)
bool wordIsConstant(Token word) {
    bool isWord = isVocabWord(word); //If this word is in vocab

    //Word is a constant if it only has one role
    return isWord && getEntry(word).size() == 1;
}

//Go through all of the synonyms and see if this word is a synonym
bool isSynonym(string word) {
    for (pair<string, string> synPair : SYNONYMS) {
        if (synPair.first == word)
            return true;
    }
    return false;
}

//Return true if pronoun is the first person pronoun 'mi'
bool isMiPronoun(const Token &token) {
    return token.tokenType == Pronoun && token.value == "mi";
}

//Return true if the pronoun is the second person pronoun 'sina'
bool isSinaPronoun(const Token &token) {
    return token.tokenType == Pronoun && token.value == "sina";
}

//Return true if the token is the pronoun 'mi' or 'sina'
bool isMiSina(const Token &token) {
    return isMiPronoun(token) || isSinaPronoun(token);
}

//Return true if there is the main verb phrase up down the line 
bool mainVerbAhead(const vector<Token> &lst, int index) {
    bool miSinaPronouns = false; //If we encounter mi/sina pronouns

    while (index < lst.size()) {
        Token word = lst.at(index);

        //If this word is marking start of the main verb phrase, return true
        if (word.tokenType == Li || word.tokenType == O)
            return true;
        
        //If this word is mi or sina, mark this is the case. The next
        // word 
        else if (isMiSina(word)) {
            miSinaPronouns = true;
            index++;
            continue;
        
        //If we bump into start of direct object, return false
        } else if (word.tokenType == E)
            return false;

        index++;
        //Reset this, so we don't accidentally find main verb
        miSinaPronouns = false;
    }
    //Otherwise, no.
    return false;
}

//Return true if the direct object particle is ahead
bool directObjectAhead(const vector<Token> &lst, int index) {
    while (index < lst.size()) {
        Token word = lst.at(index);

        //If we found the 'e' particle, return true
        if (word.tokenType == E)
            return true;

        index++;
    }
    //Otherwise, didn't find it
    return false;
}

//Goes through the list of words and labels constant words
void labelConstants(vector<Token> &lst) {
    for (int i=0; i<lst.size(); i++) {
        Token word = lst.at(i);

        //If this is an unknown word, and constant, give it its defined role
        if (/*word.tokenType == Unknown &&*/wordIsConstant(word)) {
            TokenType role = getEntry(word).at(0); //Get the role this word is playing
            word.tokenType = role;                 //Update the role of this word
            lst[i] = word;                         //Update the word in the list of words
        }
    }
}

//Goes through and attempts to find words that appear to be
// a modfier. Should allow us to label 
bool labelModifiers(vector<Token> &lst) {
    bool modifiersLabeled = false; //If we did label any modifiers

    for (int i=1; i < lst.size(); i++) {
        Token lastWord = lst.at(i-1);
        Token currWord = lst.at(i);

        //If this word is unknown, and the last word is either unknown or a verb
        if (isUnknown(currWord) && isUnknown(lastWord) || isVerb(lastWord) && canBeMod(currWord)) {
            currWord.tokenType = Mod; //Set role of curr word as a modifier
            lst[i] = currWord;        //Update word in list of words
            modifiersLabeled = true;

        //If the last word is either a noun or unknown, and this is an unknown, label mod
        } else if (isUnknown(lastWord) || isNoun(lastWord) && !isMod(currWord) && canBeMod(currWord)) {
            currWord.tokenType = Mod;
            lst[i] = currWord;
            modifiersLabeled = true;

        //If last word is a modifier, and this word is word can be a modifier, probably a modifier
        } else if (isMod(lastWord) && !isMod(currWord) && canBeMod(currWord)) {
            lst[i].tokenType = Mod;
            modifiersLabeled = true;
        }
    }
    return modifiersLabeled;
}

//Goes through and labels and Toki Pona names
bool labelNames(vector<Token> &lst) {
    bool hasLabeledNames = false;

    for (int i=0; i<lst.size(); i++) {
        Token word = lst.at(i);

        //If this word is a modifier (all names are 'imported' as adjectives)
        // and this word IS a valid toki pona name, and not an existing
        // toki pona word, then it is a name
        if (isMod(word) && !isVocabWord(word) && isTokiPonaName(word.value)) {
            word.tokenType = Name;
            lst[i] = word;
            hasLabeledNames = true;
        }
    }
    return hasLabeledNames;
}

//Labels all pronouns which are being used as pronouns
bool labelPronounMods(vector<Token> &lst) {
    bool labeledPronouns = false; //If we have relabeled the pronouns

    for (int i=1; i<lst.size(); i++) {
        Token lastWord = lst.at(i-1);
        Token currWord = lst.at(i);

        //If the last word is a noun or modifier, and this is a pronoun, this pronoun is a modifier
        if (isPronoun(currWord) && isNoun(lastWord)) {
            currWord.tokenType = Mod;
            lst[i] = currWord;
            labeledPronouns = true;

        //If last word is a modifier and this is a pronoun, mark as a mod
        } else if (isPronoun(currWord) && isMod(lastWord)) {
            lst[i].tokenType = Mod;
            labeledPronouns = true;
        }
    }
    return labeledPronouns;
}

//Label the preverb within the sentence
bool labelPreverb(vector<Token> &lst) {
    int verbPhraseDist = 0; //If we've found the verb phrase. Marks distance from li/o

    for (int i=0; i<lst.size(); i++) {
        Token word = lst.at(i);

        //If this is a verb marker, or if this is a noun, next could easily be a verb
        if (word.tokenType == O || word.tokenType == Li || isMiSina(word)) 
            verbPhraseDist = 1;
        
        //If just before was a verb marker, and this can be a preverb, mark it
        else if (verbPhraseDist == 1 && canBePreverb(word)) {
            word.tokenType = Preverb;
            lst[i] = word;
            return true;

        //If we haven't bumped into preverb, continue going
        } else if (verbPhraseDist >= 1)
            verbPhraseDist++;
    }
    return false;
}

//Finds the main verb and labels it.
bool labelVerb(vector<Token> &lst) {
    int preverbDistance = 0; //Distance from found preverb
    int subjectDistance = 0;

    //Try finding the verb by looking for a preverb
    for (int i=0; i<lst.size(); i++) {
        Token word = lst.at(i);

        //If we found the preverb, next verb is main verb
        if (isPreverb(word))
            preverbDistance = 1; 
        
        //If there is a potential verb right after preverb, it is a verb
        else if (preverbDistance == 1 && canBeVerb(word)) {
            word.tokenType = Verb;
            lst[i] = word;
            return true;

        //Increase distance from preverb, verb HAS to be right after preverb
        } else if (preverbDistance >= 1)
            preverbDistance++;
    }

    //Try to find main verb, and label it
    for (int i=0; i<lst.size(); i++) {
        Token word = lst.at(i);

        if (isPronoun(word) && i == 0 && subjectDistance == 0)
            subjectDistance = 1;
        
        else if (subjectDistance >= 1 && canBeVerb(word) && !isPreverb(word)) {
            word.tokenType = Verb;
            lst[i] = word;
            return true;
        }
    }

    //Go through, find a preverb that isn't modifying a verb, it is a verb
    for (int i=1; i<lst.size(); i++) {
        Token lastWord = lst.at(i-1);
        Token currWord = lst.at(i);

        if (isPreverb(lastWord) && canBeVerb(lastWord) && (!isVerb(currWord) || !isMod(currWord))) {
            lastWord.tokenType = Verb;
            lst[i-1] = lastWord;
            return true;
        }
    }

    //Find places were there is li/o/mi/sina and then an unlabeled verb, and label the verb
    for (int i=1; i<lst.size(); i++) {
        Token lastWord = lst.at(i-1);
        Token currWord = lst.at(i);
        TokenType lastType = lastWord.tokenType;

        if (lastType == O || lastType == Li || isMiSina(lastWord) && canBeVerb(currWord) && !isVerb(currWord)) {
            currWord.tokenType = Verb;
            lst[i] = currWord;
            return true;
        }
    }

    return false;
}

//Label words that are nouns but are left unlabeled
// because they are next to constructs such as pi, en
bool labelComplexNouns(vector<Token> &lst) {
    bool labeledNouns = false;
    for (int i=1; i<lst.size(); i++) {
        Token currWord = lst.at(i-1);
        Token nextWord = lst.at(i);

        //If the next word can be a noun, and this potential noun is right after 'en' or 'pi', then it is a noun
        if (currWord.tokenType == Pi || currWord.tokenType == En && canBeNoun(nextWord) && !isNoun(nextWord)) {
            nextWord.tokenType = Noun;
            lst[i] = nextWord;
            labeledNouns = true;

        //If this word is a potential noun, but is a preposition after 'e' then it is a noun
        } else if (currWord.tokenType == E && canBeNoun(nextWord) && !isNoun(nextWord) && isPrep(nextWord)) {
            lst[i].tokenType = Noun;
            labeledNouns = true;

        //If this current word is a preposition verb, and next is a potential noun, then next word is a noun
        } else if (isVerb(currWord) && canBePrep(currWord) && canBeNoun(nextWord) && !isNoun(nextWord)) {
            lst[i].tokenType = Noun;
            labeledNouns = true;
        }
    }
    return labeledNouns;
}

//Goes through and labels punctuation marks.
void labelPunctuation (vector<Token> &lst) {
    for (int i=0; i<lst.size(); i++) {
        Token token = lst.at(i);

        if (token.value == ".") {
            lst[i].tokenType = Period;

        } else if (token.value == "!") {
            lst[i].tokenType = Exclaim;

        } else if (token.value == "?") {
            lst[i].tokenType = Question;
        }
    }
}

//Go through and try to label all of the words in the sentence
void labelWords(vector<Token> &lst) {
    labelModifiers(lst);
    labelNames(lst);
    //labelPronounMods(lst);
    labelPreverb(lst);
    labelVerb(lst);
    labelConstants(lst);
    labelComplexNouns(lst);
    labelPunctuation(lst);
}

//End declaration of lexer.hpp
#endif
