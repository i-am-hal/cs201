/* Alastar Slater
 * names.cpp
 * Feb 8, 2021
 * This is a program that gets ten names from
 * the user, and then asks the user to enter
 * a name to see if we can find that name within
 * that list.
*/
#include <algorithm>
#include <iostream>
#include <vector>
#include <string>
using std::string;
using std::vector;
using std::getline;
using std::endl;
using std::cout;
using std::cin;

//Requests 10 names, stores them into the given vector
void inputNames(vector<string> &names) {
    cout << "You will be requested to enter 10 names:" << endl;

    for(int i=1; i <= 10; i++) {
        string name;
        cout << "Please enter name #" << i << ": ";
        getline(cin, name);
        names.push_back(name);
    }
}

//Tells us whether or not a name is in the lsit of names that we have.
bool doesNameExist(const string &searchName, vector<string> &names) {
    //Go through each name, if we find it, return true
    for(int i=0; i < names.size(); i++) {
        if (names.at(i) == searchName)
            return true;
    }
    return false;
}

//Prints out a list of names in a vector.
void printNames(const vector<string> &names) {
    int namesSize = names.size();

    cout << "All of the names given were.. " << endl;

    for(int i=0; i < namesSize; i++) {
        //Print out comma for every other name except before first
        if (i != 0)
            cout << ", ";

        //Print 'and' before last name
        if (i == namesSize-1)
            cout << "and ";

        cout << names.at(i);
    }
    cout << endl;
}

//Goes through and prints the length of each name
void printNameLengths(const vector<string> &names) {
    cout << endl << "Here are the lengths of each name: " << endl;

    //Print the length of each string.
    for(int i=0; i < names.size(); i++) {
        cout << "Name No. " << i+1 << " (" << names.at(i) << ") length: " << names.at(i).size() << endl;
    }
}

int main () {
    vector<string> names; //List of all the names given by user
    inputNames(names);

    //Test to see if an arbitrary name ('John') is in list of names
    if (doesNameExist("John", names))
        cout << endl << "John is one of the names in the list." << endl << endl;
    
    else
        cout << endl << "John is not a name in the list." << endl << endl;


    printNames(names);
    printNameLengths(names);

    return 0;
}