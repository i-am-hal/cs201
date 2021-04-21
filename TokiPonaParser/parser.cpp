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
    NTNoun=0, NTMod,
    NTVerb, NTPreverb,
    NTNounPhrase, NTVerbPhrase,
    NTPrepPhrase
};

class Node {
    public:
        NodeType nodeType;
}; 

