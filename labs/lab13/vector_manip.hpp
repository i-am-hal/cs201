/* Alastar Slater
 * Feb 24, 2021
 * vector_manip.hpp */
#include <iostream>
#include <vector>
#include <string>
using std::vector;
using std::string;
using std::cout;
using std::endl;

//All of the strings we'll be printing out.
const vector<string> outStrings = {
    "And", "his", "mind", "he's", "a", "becon", "in", "the", "veil", "of", "the", "night"};

//Given a vector of comma seperated strings, print each one on the same line
void printStrings(vector<string> strings) {
    for (int i = 0; i < strings.size(); i++)
        cout << strings.at(i) << " ";
    cout << endl;
}

