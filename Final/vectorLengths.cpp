#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
using std::ifstream;
using std::ofstream;
using std::getline;
using std::vector;
using std::string;
using std::sqrt;
using std::endl;
using std::cout;

//Definition of my vector class
class MyVector {
    private:
        double _x = 0.0;
        double _y = 0.0;
        double _z = 0.0;
    
    public:
        MyVector() {}

        //If given one set of doubles, assign to x
        MyVector(double x): _x{x*x} {}

        //If given two set of doubles, assign to x and y
        MyVector(double x, double y): _x{x*x}, _y{y*y} {}

        //If given three set of doubles, assign to x, y and z
        MyVector(double x, double y, double z): _x{x*x}, _y{y*y}, _z{z*z} {}
        
        //Returns the length of the vector
        double length() {
            return sqrt(_x + _y + _z);
        }
};

int main() {
    //Attempt to open the input file
    ifstream fin;
    fin.open("vectors.txt");

    //Attempt to open the output file
    ofstream fout;
    fout.open("lengths.txt");

    //If there was an error opening the input file, quit program
    if (!fin) {
        cout << "Error, unable to open vectors.txt!" << endl;
        return 1;

    //If there was an error opening the output file, quit program
    } else if (!fout) {
        cout << "Error, unable to open lengths.txt!" << endl;
        return 2;

    //Otherwise, continue with the program
    } else {
        double x=0.0, y=0.0, z=0.0;

        cout << "Starting to compute lengths.." << endl;

        //Continually get input for x, y, z and make vectors for it
        while (fin >> x >> y >> z) {
            //Create the vector with these x y z values
            MyVector vect = MyVector(x, y, z);
            //Write out the length of the vector on a seperate line
            fout << vect.length() << endl;
        }

        cout << "Computaiton complete!" << endl;

        fin.close();
        fout.close();
    }
    
    return 0;
}