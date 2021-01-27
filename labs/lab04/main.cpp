#include <iostream>
using std::endl;
using std::cout;

int main () {
    //Go through 1-100, doing Fizz Buzz
    for (int i = 1; i <= 100; i++) {
        //Say 'Fizz Buzz', has 3 & 5 as factors
        if (i % 15 == 0) {
            cout << "Fizz Buzz" << endl;

        //Say 'Fizz', has 3 as factor
        } else if (i % 3 == 0) {
            cout << "Fizz" << endl; 

        //Say 'Buzz', has 5 as factor
        } else if (i % 5 == 0) {
            cout << "Buzz" << endl;

        //Otherwise, just print the number
        } else {
            cout << i << endl;
        }
    }

    return 0;
}