#include <algorithm>
#include <iostream>
#include <vector>
#include <random>
using std::random_device;
using std::mt19937;
using std::shuffle;
using std::vector;
using std::sort;
using std::endl;
using std::cout;

int main() {
    vector<int> haystack;
    // assume haystack has 1,000,000,000 random numbers
    random_device rd;
    mt19937 g(rd());
    shuffle(haystack.begin(), haystack.end(), g);
    int needle = rd();

    //Make a loop in which there are two variables, i and j.
    //i starts from the begining and works its' way to the middle, looking for needle
    //j starts at the end, working to the middle looking for needle
    // if i == j, needle is not in haystack.
    // if i == needle or j == needle, then we found the needle
    for(int i=0, j=haystack.size()-1; haystack.at(i)!=needle && haystack.at(j)!=needle; i++, j--) {
        //If i and j collide before we find the needle, no needle exists
        if (i == j && haystack.at(i) != needle) {
            cout << "Error, haystack doesn't have a needle in it!" << endl;
            return 1;
        }
    }

    cout << "First look for the needle, needle is: " << needle << endl << endl;


    //Now we will sort the array and use a faster search.
    sort(haystack.begin(), haystack.end());
    //Find the needle in the haystack.

    //The bottom most value within the list
    int bottom = 0;
    //Top most value within the list
    int top = haystack.size()-1;
    //The middle into the list, where we'll compare
    int middle = (bottom + top) / 2;

    //While we haven't found a single value, the needle
    while (bottom <= top) {
        //If needle is greater than middle, shift the bottom rightwards 
        if (needle > haystack.at(middle))
            bottom = middle + 1;
        
        //If teh needle is less than middle, shift top leftwards
        else if (needle < haystack.at(middle))
            top = middle - 1;
        
        //otherwise middle value IS the needle, stop, we're done
        else 
            break;
    }


    cout << "Second look for the needle, needle is: " << haystack.at(middle) << endl << endl;

    return 0;
}