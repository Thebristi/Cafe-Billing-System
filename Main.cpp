//Cafe Billing System
// PROG 102 - Object-Oriented Programming

  //  Concepts:
  //- Classes and Objects
  //- Encapsulation
  //- Constructors
  //- Inheritance
  //- Vector


#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;


// 1. MenuItem Class
// Stores item ID, name and price


class MenuItem
{
private:
    int id;
    string name;
    double price;

public:

    // Constructor
    MenuItem(int i, string n, double p)
    {
        id = i;
        name = n;
        price = p;
    }

    int getId()
    {
        return id;
    }

    string getName()
    {
        return name;
    }

    double getPrice()
    {
        return price;
    }
};


// 2. Person Class
// Base class


class Person
{
protected:
    string name;
    string contact;

public:

    // Constructor
    Person(string n, string c)
    {
        name = n;
        contact = c;
    }

    string getName()
    {
        return name;
    }

    string getContact()
    {
        return contact;
    }
};

// 3. Customer Class
// Inherits from Person

class Customer : public Person
{
private:
    int orderHistory;

public:

    // Constructor
    Customer(string n, string c)
        : Person(n, c)
    {
        orderHistory = 0;
    }

    // Increase order history
    void addOrder()
    {
        orderHistory++;
    }

    int getOrderHistory()
    {
        return orderHistory;
    }
};






