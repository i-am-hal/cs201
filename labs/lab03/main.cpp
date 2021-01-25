#include <iostream>
using std::cout;
using std::endl;
using std::cin;

int main () {

    cout << "Printing 1-10.." << endl;
    //Print 1-10
    int i = 1;
    while (i <= 10) {
        cout << i << endl;
        i++;
    }

   
    cout << "\nPrinting 10 x 60 rectangle.." << endl;

    i = 1;
    int j = 1;

    //Create 10 rows for the rectangle
    while (i <= 10) {
        //Create columns 60 wide, print '*' for each space.
        while (j <= 60) {
            j++;
            cout << "*";
        }
        //Move to next line, reset for next column, move to next row.
        cout << endl;
        j = 1;
        i++;
    }

    cout << "\nPress Enter to exit." << endl;
    while (cin.get() != '\n');
    

    return 0;
}