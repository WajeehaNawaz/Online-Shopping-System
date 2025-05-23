#include "onlineshopping.h"
#include <fstream>
#include <iomanip>
#include <string>
#include<iostream>
#include<iomanip>
#include<limits>
using namespace std;
const int MAX_PRODUCTS = 5;
const int MAX_USERS = 10;
using namespace std;

int main() {
    OnlineShoppingSystem system;

    int choice;
    cout << "*************************************" << endl;
    cout << "-------------------------------------" << endl;
    cout << "*WELCOME TO MEGAMART SHOPPING SYSTEM**" << endl;
    cout << "-------------------------------------" << endl;
    cout << "*************************************" << endl;
    cout << "1. Login\n2. Register\n";
    cout << "Enter your choice: ";
    cin >> choice;

    if (choice == 1) {
        system.login();
    }
    else if (choice == 2) {
        system.registerUser();
    }
    else {
        std::cout << "Invalid choice. Exiting.\n";
        return 0;
    }

    system.purchaseProduct();
    if (system.cart.calculateTotal() > 0.0) {
        system.checkout();
    }

    return 0;
}
