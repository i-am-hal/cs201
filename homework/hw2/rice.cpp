/* Alastar Slater
 * rice.cpp
 * Feb 8, 2021
 * This calculates how much rice would be given to the
 * inventor in the famous story where an emperor wants to
 * reward the inventor w/ rice. Each tile has 2^(tile number - 1)
 * rice on that tile. So we take the sum of each of those values.
*/
#include <iostream>
#include <math.h>
using std::endl;
using std::cout;
using std::pow;

int main() {
    float numberOfRice = 0;
    
    //Take the sum of all the rice per tile.
    //(Calculated by 2 ^ square tile number)
    for(int square=0; square < 64; square++)
        numberOfRice += pow(2, square);

    cout << "The inventor would get " << numberOfRice << " grains of rice." << endl;

    return 0;
}