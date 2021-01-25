/* Alastar Slater
   Lab 02
   Jan 22, 2020 */

#include <iostream>
using std::cout;
using std::endl;
using std::cin;

int main () {
    int n;

    cout << "Please enter an integer: " << endl;
    cin >> n;

    n += 1;

    cout << n << " ^ 2 = " << n * n << endl;

    while (cin.get() != '\n');
    return 0;
}