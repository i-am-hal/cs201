#include <iostream>
#include <string>
#include <map>
using std::string;
using std::cout;
using std::endl;
using std::map;

int main() {
    map<string, int> database;

    //Insert flamingo at my favorite integer, 42
    database.insert({"flamingo", 42});
    database.insert({"iguana", 17});

    //delete llama if it exists
    database.erase("llama");

    //Update "iguana" to my favorite number
    map<string, int>::iterator itr = database.find("iguana");

    //If this is not the end of the database, update iguana
    if (itr != database.end())
        itr->second = 42;
    
    //print "lorikeet" if it exists
    itr = database.find("lorikeet");

    //If it exists, print the first element, 'lorikeet'
    if (itr != database.end())
        cout << itr->first << endl;
    
    map<string, int> humans = {{"Jane", 17}};


    return 0;
}