

#include <fstream>
#include <iomanip>
#include <string>
#include<iostream>
#include<iomanip>
#include<limits>
using namespace std;
const int MAX_PRODUCTS = 5;
const int MAX_USERS = 10;

class Product {
public:
    string name;
    double price;
    int quantity;

    Product();
    Product(const string& n, double p);
};

class ShoppingCart {
private:
    Product items[MAX_PRODUCTS];
    int itemCount;

public:
    ShoppingCart();

    void addItem(const Product& product);
    double calculateTotal() const;
    void displayCart() const;
    void modifyCart();
    void saveToFile() const;
};

class User {
public:
    string username;
    string password;

    User();
    User(const string& u, const string& p);
};

class UserManager : public User {
private:
    User users[MAX_USERS];
    int userCount;

public:
    UserManager();

    void loadUsersFromFile();
    void saveUsersToFile() const;
    void registerUser(const string& username, const string& password);
    bool authenticateUser(const string& username, const string& password) const;
};

class OnlineShoppingSystem {
public:
    UserManager userManager;
    ShoppingCart cart;

    void login();
    void registerUser();
    void displayCategories() const;
    void displayProducts(int category) const;
    Product selectProduct(int category, int productChoice) const;
    void purchaseProduct();
    void enterdetails();
    void enteratmdetails();
    void checkout();
};

