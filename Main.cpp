//Cafe Billing System
// PROG 102 - Object-Oriented Programming

  //  Concepts:
  //- Classes and Objects
  //- Encapsulation
  //- Constructors
  //- Inheritance
  //- Vector
  //- File Handling


#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

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

// 4. Order Class
// Stores ordered items and calculates the bill
class Order
{
private:
    vector<MenuItem> items;
    vector<int> quantities;

public:

    // Add item to order
    void addItem(MenuItem item, int quantity)
    {
        items.push_back(item);
        quantities.push_back(quantity);
    }

    // Calculate subtotal
    double calculateBill()
    {
        double subtotal = 0;

        for (int i = 0; i < items.size(); i++)
        {
            subtotal += items[i].getPrice()
                        * quantities[i];
        }

        return subtotal;
    }

    // Calculate 10% discount
    double calculateDiscount()
    {
        double subtotal = calculateBill();

        if (subtotal > 1000)
        {
            return subtotal * 0.10;
        }

        return 0;
    }

    // Calculate final amount
    double calculateTotal()
    {
        return calculateBill() - calculateDiscount();
    }

    // Return ordered items
    vector<MenuItem> getItems()
    {
        return items;
    }

    // Return quantities
    vector<int> getQuantities()
    {
        return quantities;
    }
};

// 5. Receipt Class
// Prints the customer's receipt

class Receipt
{
public:

    void printReceipt(Order order,
                      Customer customer,
                      int orderNumber)
    {
        vector<MenuItem> items = order.getItems();
        vector<int> quantities = order.getQuantities();

        cout << "\n----\n";
        cout << " CAFE RECEIPT\n";
        cout << "----\n";

        cout << "Order No. : "
             << orderNumber << endl;

        cout << "Customer  : "
             << customer.getName() << endl;

        cout << "Contact   : "
             << customer.getContact() << endl;

        cout << "----\n";

        for (int i = 0; i < items.size(); i++)
        {
            double amount =
                items[i].getPrice()
                * quantities[i];

            cout << items[i].getName()
                 << " x "
                 << quantities[i]
                 << " = Rs. "
                 << amount << endl;
        }

        cout << "----\n";

        cout << "Subtotal : Rs. "
             << order.calculateBill() << endl;

        cout << "Discount : Rs. "
             << order.calculateDiscount() << endl;

        cout << "Total    : Rs. "
             << order.calculateTotal() << endl;

        cout << "----\n";
        cout << "          Thank You!\n";
        cout << "----\n";
    }
};

// 6. Cafe Class
// Manages menu, orders and daily sales

class Cafe
{
private:
    vector<MenuItem> menu;

    double dailySales;

    int orderCount;

public:

    // Constructor
    Cafe()
    {
        dailySales = 0;
        orderCount = 0;

        // Load previously saved sales data (if any) on startup
        loadSalesFromFile();
    }

    // Load saved sales data from sales.txt
    void loadSalesFromFile()
    {
        ifstream inFile("sales.txt");

        if (inFile)
        {
            string label1, label2, label3;

            // Reads "Orders:" then the number
            inFile >> label1 >> orderCount;

            // Reads "Total" "Sales:" "Rs." then the number
            inFile >> label1 >> label2 >> label3 >> dailySales;

            inFile.close();
        }
    }

    // Save current sales data to sales.txt (overwrites old data)
    void saveSalesToFile()
    {
        ofstream outFile("sales.txt");

        if (outFile)
        {
            outFile << "Orders: " << orderCount << endl;
            outFile << "Total Sales: Rs. " << dailySales << endl;
            outFile.close();
        }
    }

    // Append this order's customer details to customers.txt
    void saveCustomerToFile(Order order,
                            Customer customer,
                            int orderNumber)
    {
        ofstream outFile("customers.txt", ios::app);

        if (outFile)
        {
            outFile << "Order No: " << orderNumber << endl;
            outFile << "Name    : " << customer.getName() << endl;
            outFile << "Contact : " << customer.getContact() << endl;
            outFile << "Total   : Rs. " << order.calculateTotal() << endl;
            outFile << "----" << endl;

            outFile.close();
        }
    }

    // Add item to menu
    void addMenuItem(MenuItem item)
    {
        menu.push_back(item);
    }

    // Display menu
    void displayMenu()
    {
        cout << "\n---- CAFE MENU ----\n";

        for (int i = 0; i < menu.size(); i++)
        {
            cout << menu[i].getId()
                 << ". "
                 << menu[i].getName()
                 << " - Rs. "
                 << menu[i].getPrice()
                 << endl;
        }

        cout << "----\n";
    }

    // Find menu item using ID
    MenuItem getMenuItem(int id)
    {
        for (int i = 0; i < menu.size(); i++)
        {
            if (menu[i].getId() == id)
            {
                return menu[i];
            }
        }

        // Return invalid item
        return MenuItem(0, "Invalid", 0);
    }

    // Complete the order
    void completeOrder(Order order,
                       Customer customer)
    {
        orderCount++;

        dailySales += order.calculateTotal();

        customer.addOrder();

        Receipt receipt;

        receipt.printReceipt(
            order,
            customer,
            orderCount
        );

        // Save updated data to file after every completed order
        saveSalesToFile();
        saveCustomerToFile(order, customer, orderCount);
    }

    // Show daily sales
    void showDailySales()
    {
        cout << "\n ----DAILY SALES---- \n";

        cout << "Orders Served: "
             << orderCount << endl;

        cout << "Total Sales: Rs. "
             << dailySales << endl;

        cout << "--\n";
    }
};

// MAIN FUNCTION

int main()
{
    cout << fixed << setprecision(2);

    // Create Cafe object
    Cafe cafe;

    // Add fixed menu items
    cafe.addMenuItem(
        MenuItem(1, "Coffee", 150)
    );

    cafe.addMenuItem(
        MenuItem(2, "Tea", 80)
    );

    cafe.addMenuItem(
        MenuItem(3, "Burger", 250)
    );

    cafe.addMenuItem(
        MenuItem(4, "Pizza", 500)
    );


    bool running = true;

    while (running)
    {
        int choice;

        cout << "\n ----\n";
        cout << " CAFE BILLING SYSTEM\n";
        cout << "\n----\n";

        cout << "1. View Menu\n";
        cout << "2. Place Order\n";
        cout << "3. View Daily Sales\n";
        cout << "4. Exit\n";

        cout << "Enter choice: ";
        cin >> choice;


       // 1. VIEW MENU

        if (choice == 1)
        {
            cafe.displayMenu();
        }

        // 2. PLACE ORDER

        else if (choice == 2)
        {
            string name;
            string contact;

            cin.ignore();

            cout << "\nEnter customer name: ";
            getline(cin, name);

            cout << "Enter contact: ";
            getline(cin, contact);

            Customer customer(name, contact);

            Order order;

            char more = 'y';

            while (more == 'y' || more == 'Y')
            {
                int id;
                int quantity;

                cafe.displayMenu();

                cout << "Enter item ID: ";
                cin >> id;

                cout << "Enter quantity: ";
                cin >> quantity;

                if (quantity <= 0)
                {
                    cout << "Invalid quantity!\n";
                    continue;
                }

                MenuItem item =
                    cafe.getMenuItem(id);

                if (item.getId() == 0)
                {
                    cout << "Invalid item ID!\n";
                    continue;
                }

                order.addItem(item, quantity);

                cout << "Add another item? (y/n): ";
                cin >> more;
            }

            cafe.completeOrder(
                order,
                customer
            );
        }

        // 3. DAILY SALES

        else if (choice == 3)
        {
            cafe.showDailySales();
        }

        // 4. EXIT

        else if (choice == 4)
        {
            cout << "\nThank you!\n";

            running = false;
        }

        // INVALID CHOICE

        else
        {
            cout << "Invalid choice!\n";
        }
    }

    return 0;
}