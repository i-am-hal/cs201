/* Alastar Slater
 * April 21, 2021
 * parser.cpp
 * Describes the parser which will use the
 * lexer and break down the toki pona sentences
 * entered and represent them in some form of AST. */
#include "lexer.hpp"
#include <iostream>
#include <string>
using std::getline;
using std::string;
using std::vector;
using std::cout;
using std::endl;

enum NodeType {
    NTNounPhrase=0, NTVerbPhrase,
    NTPrepPhrase, NTAnd, NTOr, NTLa,
    NTOf, NTParagraph, NTNone
};

//The parent node of all nodes
class Node {
    public:
        NodeType nodeType;

        //Default constructor, make NTNone
        Node(): nodeType{NTNone} {}

        //Otherwise, use given type to create the node
        Node(NodeType type): nodeType{type} {}

        //Deconstructor for all nodes
        ~Node() { delete &nodeType; }
}; 

//Definition of a noun phrase
class NounPhrase: public Node {
    public:
        Token noun;
        vector<Token> modifiers;
    
    //Creates the noun phrase.
    NounPhrase(Token coreNoun, vector<Token> mods) {
        nodeType = NTNounPhrase;
        noun = coreNoun;
        modifiers = mods;
    }

    ~NounPhrase() {
        delete &nodeType;
        delete &noun;
        delete &modifiers;
    }
};

//Def of a verb phrase.
class VerbPhrase: public Node {
    public:
        Token preverb;
        Token verb;
        vector<Token> modifiers;

    //Creates the verb phrase.
    VerbPhrase(Token coreVerb, vector<Token> mods) {
        nodeType = NTVerbPhrase;
        verb = coreVerb;
        modifiers = mods;
    }

    //Creates the verb phrase.
    VerbPhrase(Token preverbWord, Token coreVerb, vector<Token> mods) {
        nodeType = NTVerbPhrase;
        preverb = preverbWord;
        verb = coreVerb;
        modifiers = mods;
    }

    ~VerbPhrase() {
        delete &nodeType;
        delete &preverb;
        delete &verb;
        delete &modifiers;
    }
};

//A prepositional node, has a preposition w/ modifiers and a noun
class PrepPhrase: public Node {
    public:
        Token preposition;
        vector<Token> modifiers;
        Node noun;
    
    PrepPhrase(Token prep, vector<Token> mods, Node nounNode): preposition{prep} {
        modifiers = mods;
        noun = nounNode;
    }
    
    ~PrepPhrase() {
        delete &nodeType;
        delete &modifiers;
        delete &noun;
    }
};

//Some kind of union of nouns
class NounJoin: public Node {
    public:
        Node left;
        Node right;
    
    //Creates the noun union.
    NounJoin(NodeType unionType, Node leftNode, Node rightNode) {
        nodeType = unionType;
        left = leftNode;
        right = rightNode;
    }

    ~NounJoin() {
        delete &nodeType;
        delete &left;
        delete &right;
    }
};

//Sentence will have the parts of speech
class Sentence: public Node {
    public:
        //Subj, main verb, direct object, indir object
        Node subject;
        Node mainVerb;
        Node dirObject;
        Node indirObject;

        Sentence(Node subj, Node verb, Node dirObj, Node indirObj) {
            subject = subj;
            mainVerb = verb;
            dirObject = dirObj;
            indirObject = indirObj;
        }

        Sentence(Node subj, Node verb, Node dirObj): indirObject{Node()} {
            subject = subj;
            mainVerb = verb;
            dirObject = dirObj;
        }

        ~Sentence() {
            delete &nodeType;
            delete &subject;
            delete &mainVerb;
            delete &dirObject;
            delete &indirObject;
        }
};

//A paragraph is a bunch of statement nodes
class Paragraph: public Node {
    public:
        vector<Node> sentences;
    
    Paragraph(vector<Node> statements) {
        nodeType = NTParagraph;
        sentences = statements;
    }

    ~Paragraph() {
        delete &nodeType;
        delete &sentences;
    }
};

//This class will be given a string and will parse it 
// into direct object indirect object and verb phrase
class Parser {
    private:
        string text;
        Lexer lexer;
        Token currToken;
        vector<Token> tokens;
        int tokenIndex;
        /* bool takenSubject;
        bool takenVerb;
        bool takenObj; */

        //Gets the next token by way of removing this based on type
        void eatType(TokenType type, string errorText) {
            tokenIndex++;

            //If the types are the same, get the next token
            if (type == currToken.tokenType) {
                currToken = tokens.at(tokenIndex);

            //If an error has not already been raised, raise one
            } else if (!error) {
                error = true;
                errorStr = "mi sona ala e toki sina.";
            }
        }

        //Should be used if we know FOR A FACT what the type is
        void remove(TokenType type) {
            eatType(type, "mi sona ala e toki sina.");
        }
    
        //Returns the current token's type
        TokenType currType() { return currToken.tokenType; }

        //Return true if this node is the none node
        bool isNoneNode(Node node) { return node.nodeType == NTNone; }

        //Returns true if this token is a end punctuation
        bool isEndPunctuation(TokenType type) {
            return type == Period || type == Question || type == Exclaim;
        }

        //Parses a base noun 
        Node baseNoun() {
            Token noun = currToken;
            eatType(Noun, "mi sona ala e toki sina.");

            //Collect all of the modifiers on this word
            vector<Token> mods;
            while (!error && currToken.tokenType == Mod) {
                mods.push_back(currToken);
                remove(Mod);
            }

            //If this is a pronoun, add it as a modifier
            if (isPronoun(currToken)) {
                mods.push_back(currToken);
                remove(currType());
            }

            return NounPhrase(noun, mods);
        }

        //Parses some sort of noun phrase
        Node nounPhrase() {
            Node noun = baseNoun();

            //If this is or, join with or operator
            if (currType() == Anu)
                return NounJoin(NTOr, noun, nounPhrase());
            
            //If this is and, join with and operator
            else if (currType() == En)
                return NounJoin(NTAnd, noun, nounPhrase());
            
            //If this is of, join w/ operator
            else if (currType() == Pi)
                return NounJoin(NTOf, noun, nounPhrase());
        }

        //Parses a verb phrase, a preverb, verb, modifiers
        Node verbPhrase() {
            //If this is some sort of of preverb, deal w/ differently
            if (currType() == Preverb) {
                Token preverb = currToken;
                remove(Preverb);
                //Attempt to get a verb
                Token verb = currToken;
                eatType(Verb, "mi sona ala e toki sina.");

                vector<Token> mods;
                while (!error && currType() == Mod) {
                    mods.push_back(currToken);
                    remove(Mod);
                }

                //Return this verb phrase
                return VerbPhrase(preverb, verb, mods);

            //If this is a verb, don't collect a preverb
            } else if (currType() == Verb) {
                Token verb = currToken;
                remove(Verb);

                vector<Token> mods;
                while (!error && currType() == Mod) {
                    mods.push_back(currToken);
                    remove(Mod);
                }

                return VerbPhrase(verb, mods);
            }
        }

        //Pares a direct noun phrase
        Node directNounPhrase() {
            //If the direct object marker, then parse noun phrase
            if (currType() == E) {
                remove(E);
                return nounPhrase();

            //Otherwise, return none node
            } else 
                return Node();
        }

        //Parses some sort of prepositional phrase
        Node indirNounPhrase() {
            //If this is a preposition, try to parse a prepositional phrase
            if (currType() == Prep) {
                Token prep = currToken;
                remove(Prep);

                //Collect all of the modifiers acting upon the preposition
                vector<Token> mods;
                while (!error && currType() == Mod) {
                    mods.push_back(currToken);
                    remove(Mod);
                }

                //Returns the prepositinoal phrase
                return PrepPhrase(prep, mods, nounPhrase());

            //Otherwise return a none node
            } else
                return Node();
        }

        //Parses some sort of noun phrase.
        Node sentence() {
            Node subject = nounPhrase();
            Node mainVerb = verbPhrase();
            //Attempt to get some sort of direct noun phrase.
            Node directObj = directNounPhrase();
            Node indirObj = indirNounPhrase();

            //Return the sentence that has all these parts of speech
            return Sentence(subject, mainVerb, directObj, indirObj);
        }

        //Parses an utterance of some form
        Node utterance() {
            //Get the first phrase which may not be joined
            Node phrase = sentence();

            //If this is la, conjoin another sentenec w/ that
            if (currType() == La)
                phrase = NounJoin(NTLa, phrase, utterance());
        }

    public:
        bool error;
        string errorStr;

        //Default constructor for the parser
        Parser() {
            error = true;
            errorStr = "sina seme? sina seme e seme?";
        }

        //Constructor for when we are actually given text to maybe parse
        Parser(string input): text{input}, error{false}, tokenIndex{0}, lexer{Lexer(input)} {
            tokens = lexer.exhaustTokens();
            labelWords(tokens);

            //If an error occured, record it
            if (lexer.error) {
                error = true;
                errorStr = lexer.errorStr;

            //Cannot get the first token, raise error.
            } else if (tokens.size() == 0) {
                error = true;
                errorStr = "mi sona ala toki sina.";

            //Otherwise, retrieve the first value.
            } else {
                currToken = tokens.at(0);
            }
        }

        //Deconstructor for the parser.
        ~Parser() {
            delete &text;
            delete &lexer;
            delete &error;
            delete &errorStr;
            delete &currToken;
            delete &tokens;
            delete &tokenIndex;
        }

        //Parses an expression
        Node parse() {
            Node phrase = utterance();
            vector<Node> phrases = {phrase};

            //Get all of the punction seperated sentences
            while (isEndPunctuation(currType()) && !error && currType() != Eol) {
                remove(currType());

                //If, somehow, we find only removing the punctuation
                // brings an error or to the end of the line, stop
                if (!error || currType() == Eol)
                    break;
                
                phrases.push_back(utterance());
            }

            //If there is only one phrase within the
            // list of phrases, return start phrase
            if (phrases.size() == 1)
                return phrase;
            
            else //Otherwise, return the paragraph of phrases
                return Paragraph(phrases);
        }
};

