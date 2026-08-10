// Project name: Cafe Billing System Using C++
// Object-Oriented Programming
// A Console-based billing system for a small cafe.
//This demonstrates classes/objects, encapsulation, constructors, and inheritance.

#include <iostream>
#include<iomanip>
#include<string>
#include<vector>
#include<limits>
using namespace std;
// MenuItem: Stores the details of a single food/drink item

class MenuItem{
    private:
    int id;
    string name;
    double price;
public:
    MenuItem() : id(0), name(""), price(0.0){}
    MenuItem(int id, const string& name, double price)
        : id(id), name(name), price (price){}
    int getId() const {return id;}
    string getName()const{return name;}
    double getPrice()const {return price;}
};
//Person: base class used to demonstrate inheritance