#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// Enum for user roles
enum class Role { Admin, Employee, Customer };

// Item class
class Item {
public:
    string name;
    string tag;  // Specific tag for categorization
    int id;      // Unique ID
    double price;
    int quantity;

    Item(string n, string t, int i, double p, int q) 
        : name(n), tag(t), id(i), price(p), quantity(q) {}
};

// User class
class User {
public:
    string username;
    string password;
    Role role;

    User(string u, string p, Role r) 
        : username(u), password(p), role(r) {}
};

// Inventory class
class Inventory {
private:
    vector<Item> items;
    vector<User> users;
    User* currentUser = nullptr;

    bool isAdmin() { return currentUser && currentUser->role == Role::Admin; }
    bool isEmployee() { return currentUser && currentUser->role == Role::Employee; }
    bool isCustomer() { return currentUser && currentUser->role == Role::Customer; }

public:
    Inventory() {
        // Default admin user
        users.push_back(User("admin", "admin123", Role::Admin));
    }

    bool login(string username, string password) {
        for (auto& user : users) {
            if (user.username == username && user.password == password) {
                currentUser = &user;
                return true;
            }
        }
        return false;
    }

    void logout() { currentUser = nullptr; }

    void addUser(string username, string password, Role role) {
        if (!isAdmin()) {
            cout << "Only admin can add users.\n";
            return;
        }
        users.push_back(User(username, password, role));
        cout << "User " << username << " added.\n";
    }

    void removeUser(string username) {
        if (!isAdmin()) {
            cout << "Only admin can remove users.\n";
            return;
        }
        users.erase(
            remove_if(users.begin(), users.end(), 
                [username](User& u) { return u.username == username; }), 
            users.end());
        cout << "User " << username << " removed.\n";
    }

    void addItem(string name, string tag, int id, double price, int quantity) {
        if (!isAdmin()) {
            cout << "Only admin can add items.\n";
            return;
        }
        items.push_back(Item(name, tag, id, price, quantity));
        cout << "Item " << name << " added.\n";
    }

    void adjustPrice(int id, double newPrice) {
        if (!isAdmin()) {
            cout << "Only admin can adjust prices.\n";
            return;
        }
        for (auto& item : items) {
            if (item.id == id) {
                item.price = newPrice;
                cout << "Price of " << item.name << " updated to " << newPrice << ".\n";
                return;
            }
        }
        cout << "Item not found.\n";
    }

    void updateQuantity(int id, int newQuantity) {
        if (!isAdmin() && !isEmployee()) {
            cout << "Only admin or employees can update quantities.\n";
            return;
        }
        for (auto& item : items) {
            if (item.id == id) {
                item.quantity = newQuantity;
                cout << "Quantity of " << item.name << " updated to " << newQuantity << ".\n";
                return;
            }
        }
        cout << "Item not found.\n";
    }

    void viewInventory() {
        if (!currentUser) {
            cout << "Please log in first.\n";
            return;
        }
        cout << "\nInventory:\n";
        for (const auto& item : items) {
            cout << "ID: " << item.id << ", Name: " << item.name 
                 << ", Tag: " << item.tag << ", Price: $" << item.price 
                 << ", Quantity: " << item.quantity << "\n";
        }
        cout << "\n";
    }
};

// Main function with a simple command-line interface
int main() {
    Inventory inv;
    string username, password, name, tag;
    int id, quantity, choice;
    double price;

    while (true) {
        cout << "\n1. Login\n2. Logout\n3. Add User (Admin)\n4. Remove User (Admin)\n"
             << "5. Add Item (Admin)\n6. Adjust Price (Admin)\n7. Update Quantity (Employee/Admin)\n"
             << "8. View Inventory\n9. Exit\nChoice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Username: ";
            cin >> username;
            cout << "Password: ";
            cin >> password;
            if (inv.login(username, password)) {
                cout << "Logged in as " << username << ".\n";
            } else {
                cout << "Invalid credentials.\n";
            }
            break;
        case 2:
            inv.logout();
            cout << "Logged out.\n";
            break;
        case 3:
            cout << "New username: ";
            cin >> username;
            cout << "New password: ";
            cin >> password;
            cout << "Role (0=Admin, 1=Employee, 2=Customer): ";
            cin >> choice;
            inv.addUser(username, password, static_cast<Role>(choice));
            break;
        case 4:
            cout << "Username to remove: ";
            cin >> username;
            inv.removeUser(username);
            break;
        case 5:
            cout << "Item name: ";
            cin >> name;
            cout << "Tag: ";
            cin >> tag;
            cout << "ID: ";
            cin >> id;
            cout << "Price: ";
            cin >> price;
            cout << "Quantity: ";
            cin >> quantity;
            inv.addItem(name, tag, id, price, quantity);
            break;
        case 6:
            cout << "Item ID: ";
            cin >> id;
            cout << "New price: ";
            cin >> price;
            inv.adjustPrice(id, price);
            break;
        case 7:
            cout << "Item ID: ";
            cin >> id;
            cout << "New quantity: ";
            cin >> quantity;
            inv.updateQuantity(id, quantity);
            break;
        case 8:
            inv.viewInventory();
            break;
        case 9:
            cout << "Exiting...\n";
            return 0;
        default:
            cout << "Invalid choice.\n";
        }
    }
}