#include "onlineshopping.h"

Product::Product() : price(0.0), quantity(0) {}

Product::Product(const std::string& n, double p) : name(n), price(p), quantity(0) {}

ShoppingCart::ShoppingCart() : itemCount(0) {}

void ShoppingCart::addItem(const Product& product) {
    if (itemCount < MAX_PRODUCTS) {
        items[itemCount++] = product;
    }
    else {
        std::cout << "Shopping cart is full.\n";
    }
}

double ShoppingCart::calculateTotal() const {
    double total = 0.0;
    for (int i = 0; i < itemCount; i++) {
        total += items[i].price * items[i].quantity;
    }
    return total;
}

void ShoppingCart::displayCart() const {
    double total = 0.0;
    double taxRate = 0.1; // Example tax rate of 10%
    double taxAmount;
    double finalTotal;
    std::cout << "\nShopping Cart:\n";
    std::cout << "-------------------------------------------------\n";
    std::cout << std::left << std::setw(20) << "Product Name" << std::setw(10) << "Price" << std::setw(10) << "Quantity" << std::setw(15) << "Subtotal\n";
    std::cout << "-------------------------------------------------\n";

    for (int i = 0; i < itemCount; ++i) {
        double subtotal = items[i].price * items[i].quantity;
        total += subtotal;
        std::cout << std::left << std::setw(20) << items[i].name << std::setw(10) << items[i].price << setw(10) << items[i].quantity << setw(15) << subtotal << "\n";
    }
    taxAmount = total * taxRate;
    finalTotal = total + taxAmount;

    std::cout << "-------------------------------------------------\n";
    std::cout << std::left << std::setw(30) << "Total:" << std::setw(15) << total << "\n";
    std::cout << std::left << std::setw(30) << "Tax (10%):" << std::setw(15) << taxAmount << "\n";
    std::cout << std::left << std::setw(30) << "Final Total:" << std::setw(15) << finalTotal << "\n";
    std::cout << "-------------------------------------------------\n";
}

void ShoppingCart::modifyCart() {
    int choice;

    do {
        std::cout << "Modify Cart:\n";
        displayCart();
        std::cout << "1. Change quantity\n2. Remove product\n3. Done\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string productName;
            int newQuantity;
            bool productFound = false;

            std::cout << "Enter the product name: ";
            std::cin.ignore();
            std::getline(std::cin, productName);

            for (int i = 0; i < itemCount; ++i) {
                if (items[i].name == productName) {
                    productFound = true;
                    std::cout << "Enter the new quantity: ";
                    std::cin >> newQuantity;
                    items[i].quantity = newQuantity;
                    std::cout << "Quantity updated.\n";
                    break;
                }
            }

            if (!productFound) {
                std::cout << "Invalid product name. Please enter a product that is present in the cart.\n";
            }

            break;
        }
        case 2: {
            std::string productName;
            bool productFound = false;

            std::cout << "Enter the product name to remove: ";
            std::cin.ignore();
            std::getline(std::cin, productName);

            for (int i = 0; i < itemCount; ++i) {
                if (items[i].name == productName) {
                    productFound = true;

                    for (int j = i; j < itemCount - 1; ++j) {
                        items[j] = items[j + 1];
                    }
                    --itemCount;
                    std::cout << "Product removed.\n";
                    break;
                }
            }

            if (!productFound) {
                std::cout << "Invalid product name. Please enter a product that is present in the cart.\n";
            }

            break;
        }
        case 3:
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

void ShoppingCart::saveToFile() const {
    std::ofstream outFile("shopping_cart.txt");
    if (!outFile) {
        throw std::runtime_error("Error opening the file for writing.");
    }


    for (int i = 0; i < itemCount; ++i) {
        outFile << items[i].name << "," << items[i].price << "," << items[i].quantity << "\n";
    }


    outFile.close();
}
User::User() : username(""), password("") {}

User::User(const std::string& u, const std::string& p) : username(u), password(p) {}

UserManager::UserManager() : userCount(0) {
    loadUsersFromFile();
}

void UserManager::loadUsersFromFile() {
    std::ifstream inFile("user_accounts.txt");
    if (!inFile) {
        std::cerr << "Error opening the file for reading user accounts.\n";
        return;
    }


    std::string username, password;
    while (inFile >> username >> password && userCount < MAX_USERS) {
        users[userCount++] = User(username, password);
    }


    inFile.close();
}

void UserManager::saveUsersToFile() const {
    std::ofstream outFile("user_accounts.txt");
    if (!outFile) {
      std::  cerr << "Error opening the file for writing user accounts.\n";
        return;
    }


    for (int i = 0; i < userCount; ++i) {
        outFile << users[i].username << " " << users[i].password << "\n";
    }


    outFile.close();
}

void UserManager::registerUser(const std::string& username, const std::string& password) {
    if (userCount < MAX_USERS) {
        users[userCount++] = User(username, password);
        std::cout << "Registration successful. You can now log in.\n";
        saveUsersToFile();
    }
    else {
        std::cout << "User limit reached. Cannot register new user.\n";
    }
}

bool UserManager::authenticateUser(const std::string& username, const std::string& password) const {
    for (int i = 0; i < userCount; ++i) {
        if (users[i].username == username && users[i].password == password) {
            return true;
        }
    }
    return false;
}

void OnlineShoppingSystem::login() {
    std::string username, password;
    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;


    if (userManager.authenticateUser(username, password)) {
        std::cout << "Login successful. Welcome to MegaMart Shopping System!\n";
    }
    else {
        std::cout << "Invalid username or password. Please register or try again.\n";
        registerUser();
    }
}

void OnlineShoppingSystem::registerUser() {
   std:: string username, password;


    std::cout << "Enter a new username: ";
    std::cin >> username;


    while (true) {
        std::cout << "Enter a password maximum 12 characters): ";
        std::cin >> password;


        if (password.length() <= 12) {
            break; // Exit the loop if the password is exactly 12 characters long
        }
        else {
            std::cout << "Invalid password. Please enter a maximum 12-character password.\n";
        }
    }


    userManager.registerUser(username, password);
    std::cout << "*************************************" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "*******REGISTRATION SUCCESSFUL*******" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "*************************************" << std::endl;
}

void OnlineShoppingSystem::displayCategories() const {
   std:: cout << "*************************************" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "*************CATEGORIES*************" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "*************************************" << std:: endl;
    std::cout << "1. Clothing\n2. Sports\n3. Electronics\n4. Makeup\n5. Medicine\n6. Exit\n";
    
}

void OnlineShoppingSystem::displayProducts(int category) const {
    switch (category) {
    case 1: // Clothing
        std::cout << "Clothing:\n";
        std::cout << "1. T-Shirt - $10\n2. Jeans - $20\n3. Jacket - $30\n4. Dress - $25\n";
        std::cout << "5. Shorts - $15\n6. Skirt - $18\n7. Hoodie - $35\n8. Sweater - $22\n";
        std::cout << "9. Blouse - $19\n10. Cap - $8\n";
        break;
    case 2: // Sports
        std::cout << "Sports:\n";
        std::cout << "1. Basketball - $15\n2. Soccer Ball - $12\n3. Yoga Mat - $18\n4. Running Shoes - $25\n";
        std::cout << "5. Tennis Racket - $30\n6. Golf Clubs - $100\n7. Baseball Glove - $40\n8. Swim Goggles - $10\n";
        std::cout << "9. Jump Rope - $7\n10. Skateboard - $50\n";
        break;
    case 3: // Electronics
        std::cout << "Electronics:\n";
        std::cout << "1. Smartphone - $300\n2. Laptop - $600\n3. Headphones - $50\n4. Smartwatch - $80\n";
        std::cout << "5. Tablet - $200\n6. Camera - $250\n7. E-Reader - $120\n8. Bluetooth Speaker - $70\n";
        std::cout << "9. External Hard Drive - $100\n10. USB Flash Drive - $20\n";
        break;
    case 4: // Makeup
       std:: cout << "Makeup:\n";
        std::cout << "1. Lipstick - $10\n2. Eyeshadow Palette - $25\n3. Foundation - $15\n4. Makeup Brushes - $12\n";
        std::cout << "5. Mascara - $8\n6. Eyeliner - $9\n7. Blush - $11\n8. Concealer - $7\n";
        std::cout << "9. Bronzer - $13\n10. Makeup Remover - $6\n";
        break;
    case 5: // Medicine
        std::cout << "Medicine:\n";
        std::cout << "1. Painkillers - $5\n2. Cough Syrup - $8\n3. Band-Aids - $3\n4. Multivitamins - $10\n";
        std::cout << "5. Antacids - $4\n6. Allergy Medication - $7\n7. Cold Relief - $6\n8. Antibiotic Ointment - $9\n";
        std::cout << "9. Eye Drops - $5\n10. Sleep Aids - $11\n";
        break;
    default:
       std:: cout << "Invalid category.\n";
    }
}

Product OnlineShoppingSystem::selectProduct(int category, int productChoice) const {
    switch (category) {
    case 1: // Clothing
        switch (productChoice) {
        case 1: return { "T-Shirt", 10.0 };
        case 2: return { "Jeans", 20.0 };
        case 3: return { "Jacket", 30.0 };
        case 4: return { "Dress", 25.0 };
        case 5: return { "Shorts", 15.0 };
        case 6: return { "Skirt", 18.0 };
        case 7: return { "Hoodie", 35.0 };
        case 8: return { "Sweater", 22.0 };
        case 9: return { "Blouse", 19.0 };
        case 10: return { "Cap", 8.0 };
        default: return { "", 0.0 };
        }
    case 2: // Sports
        switch (productChoice) {
        case 1: return { "Basketball", 15.0 };
        case 2: return { "Soccer Ball", 12.0 };
        case 3: return { "Yoga Mat", 18.0 };
        case 4: return { "Running Shoes", 25.0 };
        case 5: return { "Tennis Racket", 30.0 };
        case 6: return { "Golf Clubs", 100.0 };
        case 7: return { "Baseball Glove", 40.0 };
        case 8: return { "Swim Goggles", 10.0 };
        case 9: return { "Jump Rope", 7.0 };
        case 10: return { "Skateboard", 50.0 };
        default: return { "", 0.0 };
        }
    case 3: // Electronics
        switch (productChoice) {
        case 1: return { "Smartphone", 300.0 };
        case 2: return { "Laptop", 600.0 };
        case 3: return { "Headphones", 50.0 };
        case 4: return { "Smartwatch", 80.0 };
        case 5: return { "Tablet", 200.0 };
        case 6: return { "Camera", 250.0 };
        case 7: return { "E-Reader", 120.0 };
        case 8: return { "Bluetooth Speaker", 70.0 };
        case 9: return { "External Hard Drive", 100.0 };
        case 10: return { "USB Flash Drive", 20.0 };
        default: return { "", 0.0 };
        }
    case 4: // Makeup
        switch (productChoice) {
        case 1: return { "Lipstick", 10.0 };
        case 2: return { "Eyeshadow Palette", 25.0 };
        case 3: return { "Foundation", 15.0 };
        case 4: return { "Makeup Brushes", 12.0 };
        case 5: return { "Mascara", 8.0 };
        case 6: return { "Eyeliner", 9.0 };
        case 7: return { "Blush", 11.0 };
        case 8: return { "Concealer", 7.0 };
        case 9: return { "Bronzer", 13.0 };
        case 10: return { "Makeup Remover", 6.0 };
        default: return { "", 0.0 };
        }
    case 5: // Medicine
        switch (productChoice) {
        case 1: return { "Painkillers", 5.0 };
        case 2: return { "Cough Syrup", 8.0 };
        case 3: return { "Band-Aids", 3.0 };
        case 4: return { "Multivitamins", 10.0 };
        case 5: return { "Antacids", 4.0 };
        case 6: return { "Allergy Medication", 7.0 };
        case 7: return { "Cold Relief", 6.0 };
        case 8: return { "Antibiotic Ointment", 9.0 };
        case 9: return { "Eye Drops", 5.0 };
        case 10: return { "Sleep Aids", 11.0 };
        default: return { "", 0.0 };
        }
    default:
        return Product();
    }
}

void OnlineShoppingSystem::purchaseProduct() {
    int category;
    int productChoice;

    while (true) {
        displayCategories();
        std::cout << "Enter the category number (6 to exit): ";
        std::cin >> category;

        if (category == 6) {
            break;
        }

        displayProducts(category);
        std::cout << "Enter the product number (1-10): ";
        std::cin >> productChoice;

        if (productChoice < 1 || productChoice > 10) {
            std::cout << "Invalid product choice. Please try again.\n";
            continue;
        }

        Product product = selectProduct(category, productChoice);

        int quantity;
        std::cout << "Enter the quantity (maximum 100): ";
        std::cin >> quantity;

        if (quantity < 1 || quantity > 100) {
            std::cout << "Invalid quantity. Please enter a value between 1 and 100.\n";
            continue;
        }

        product.quantity = quantity;

        cart.addItem(product);
        std::cout << "Product added to the cart.\n";
    }

    // Check if the cart is empty
    if (cart.calculateTotal() <= 0.0) {
        std::cout << "Your cart is empty. Please add some items to your cart before checking out.\n";
        //  go back to the shopping process
        purchaseProduct();
        return;
    }
}

void OnlineShoppingSystem::enterdetails() {
    std::string name, email, address, contactnumberStr;


    std::cout << "Enter your name:" << std::endl;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, name);


    std::cout << "Enter your email:" << std::endl;
    std::getline(std::cin, email);


    while (true) {
        bool isValidNumber = true;
        std::cout << "Enter your contact number (11 digits):" << std::endl;
        std::getline(std::cin, contactnumberStr);


        if (contactnumberStr.length() != 11) {
            isValidNumber = false;
        }
        else {
            for (char c : contactnumberStr) {
                if (!isdigit(c)) {
                    isValidNumber = false;
                    break;
                }
            }
        }


        if (isValidNumber) {
            break; // Exit the loop if the number is valid
        }
        else {
            std::cout << "Invalid contact number. Please enter an 11-digit number.\n";
        }
    }
    std::cout << "Enter your address:" << std::endl;
    getline(std::cin, address);
}

void OnlineShoppingSystem::enteratmdetails() {
    std::string cardholdername, cardnumberStr, Expirationdate, address;


    std::cout << "Enter Card Holder's Name:" << std::endl;
std:: cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::getline(std::cin, cardholdername);


    while (true) {
        std::cout << "Enter Card Number (16 digits):" << std::endl;
        std::getline(std::cin, cardnumberStr);


        // Check if the card number is exactly 16 digits long
        if (cardnumberStr.length() == 16) {
            break; // Exit the loop if the number is 16 digits and only contains digits
        }
        else {
           std:: cout << "Invalid card number. Please enter a 16-digit number.\n";
        }
    }


    std::cout << "Enter your card expiration date (dd/mm/yy):" << std::endl;
    getline(std::cin, Expirationdate);


    std::cout << "Enter your address:" << std::endl;
    std::getline(std::cin, address);
}

void OnlineShoppingSystem::checkout() {
    try {
        std::cout << "Checking out...\n";
        cart.displayCart();
        cart.modifyCart();
        if (cart.calculateTotal() <= 0.0) {
            std::cout << "Your cart is empty. Please add some items to your cart before checking out.\n";
            // to go back to the shopping process
            purchaseProduct();
            return;
        }


        std::cout << "Do you want to proceed to checkout? (y/n): ";
        char choice;
        std::cin >> choice;


        if (choice == 'y' || choice == 'Y') {
            do {
                cart.displayCart();
                cart.saveToFile();
                if (cart.calculateTotal() <= 0.0) {
                    std::cout << "Your cart is empty. Please add some items to your cart before checking out.\n";
                    //  to go back to the shopping process
                    purchaseProduct();
                    return;
                }
                int paymentChoice;
                std::cout << "Select a payment option:\n1. Cash on delivery\n2. ATM\n";
                std::cout << "Enter your choice: ";
                std::cin >> paymentChoice;


                switch (paymentChoice) {
                case 1:
                   std:: cout << "You choose Cash on Delivery.\n";
                    enterdetails();
                    std::cout << "Your order has been placed successfully!\n";
                    std::cout << "You will soon receive your order in 3-5 working days.\n";
                    break;
                case 2:
                    std::cout << "You chose ATM. Please follow the instructions on the ATM for payment.\n";
                    enteratmdetails();
                    std::cout << "Your order has been placed successfully!\n";
                    std::cout << "You will soon receive your order in 3-5 working days.\n";
                    break;
                default:
                    std::cout << "Invalid payment choice.\n";
                }


                std::cout << "Do you want to choose another payment option? (y/n): ";
                std::cin >> choice;
            } while (choice == 'y' || choice == 'Y');
        }
        else {
            std::cout << "Checkout cancelled.\n";
        }
    }
    catch ( exception& e) {
        std::cerr << "Error during checkout: " << e.what() << "\n";
    }
}
