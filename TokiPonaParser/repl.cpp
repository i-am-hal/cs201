#include <iostream>
#include <string>
using std::endl;
using std::cout;
using std::cin;
using std::string;
using std::getline;


int main() {
    while (true) {
        string input;
        cout << "> ";
        getline(cin, input);

        //Parser parser = Parse(input)
        //Node ast = parser.parse();
        //
        // if(parser.error) {
        //  cout << parser.erroStr << endl;
        //
        // } else
        //  cout << endl << "Result: " << ast.toString() << endl;
    }

    return 0;
}
