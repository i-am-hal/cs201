#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;
using std::endl;
using std::cout;
using std::cin;

//Tells program if given string to end loop of getting words or not
bool isEnd(string str) {
    return str == "end";
}

//Gets a single word as input from teh user
string getWord() {
    string input;
    cin >> input;
    return input;
}

//This function will endlessly get input until user types the word 'end'
void getWords() {
    cout << "Enter a series of strings (type \"end\" to finish):" << endl;
    string input;

    do { //Continually get input until user types the word 'end'
        input = getWord();
    } while (!isEnd(input));
}

