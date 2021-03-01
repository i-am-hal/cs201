/* Alastar Slater
 * Feb 22, 2021
 * userInput.cpp 
 * Tests the three parts of the program.*/
#include "userInput.hpp"

//Tests to ensure that the function 'isEnd' operates as expected.
const vector<string> testInputsIsEnd = {"yes", "no", "good", "bad", "end", "  end", "stop"};
const vector<bool> testOutputsIsEnd = {false, false, false, false, true, false, false};

int main() {
    cout << "TESTING OF GETTING A SINGLE WORD:\nPlease enter a word: ";
    string input = getWord();
    cout << endl << "You entered: '" << input << "'" << endl << endl;

    cout << "TESTING isEnd() TO SEE IF IT CAN FIGURE OUT WHICH STRING IS 'end':" << endl;
    //Test to see if the functino isEnd fails unexpectedly.
    for(int i = 0; i < testInputsIsEnd.size(); i++) {
        string testInput = testInputsIsEnd.at(i); //The sample input to test
        bool testOutput = testOutputsIsEnd.at(i); //The sample output expected

        //If for some reason, this fails, complain to user.
        if (isEnd(testInput) != testOutput) {
            cout << "Test #" << i+1 << " input '" << testInput;
            cout << "' failed to return " << testOutput << " from isEnd!" << endl;
            return 1;
        }
    }
    cout << "All tests passed successfully!" << endl << endl;

    cout << "TESTING GETTING MANY WORDS:\nPlease type some words: ";
    getWords();

    return 0;
}