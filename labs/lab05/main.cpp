#include <iostream>
using std::cout;
using std::endl;
using std::cin;

int main() {
    bool endProgram = false;
    int input = -1;
    cout << "Enter 0 to exit program." << endl << endl;

    while (!endProgram) {
        cout << "Please enter an integer of at least 0." << endl;
        //Endlessly get input until a whole number is given
        do {
            cout << "Input your number: ";
            cin >> input;

            if (input < 0)
                cout << "Please enter a number greater than, or equal to 0." << endl;
        } while (input < 0);


        //Process the number that the user entered in.
        switch (input) {
            case 0: //In this case (0), exit the program
                cout << "Goodbye, thanks for having ya!\n" << endl;
                endProgram = true;
                break;
            
            case 1: //Reponse for 1, a nice song reference
                cout << "One is the lonliest number...\n" << endl;
                break;
            
            //Covers anything else, no specific response to anything else
            default:
                cout << "I don't quite know what to tell you for " << input << ", buddy!\n" << endl;
                break;
        }
    }

    return 0;
}