#include <iostream>
#include <string>
#include "boxer.hpp"

int main() {
    cout << "GETTING SIZE OF BOX .. " << endl;
    //Will get a positive integer from the user that is > 0
    int givenInput = getPositiveInt();
    cout << "You entered: " << givenInput << endl;

    cout << endl << "GETTING TEXT FOR INSIDE OF BOX.." << endl;
    string boxLine = getBoxString();
    cout << "You entered: \"" << boxLine << "\"" << endl;

    return 0;
}