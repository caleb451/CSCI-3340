/*
Dev: Jay
Program: System in charge of handling the storage of items in the inventory and related functions
*/

// To Be Implemented
/*
Confirmation for Item deletion
Display list of items for deletion?
More work on Edit function
Import data function
Export data function
*/
#include "account.h"
#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <ctime>
namespace fs = std::filesystem;

using namespace std;

// Structure for items in the list
struct Item {
    // The actual information
    string name;
    int ID;
    double price;
    int stock;
    string department;
    string aisle;
    
    // Links to the next and previous items in the list
    Item* next;         // points to the next item in the list
    Item* prev;         // points to the previous item in the list
};


// Class for the linked list
class Inventory {
    Item* headPtr;      // Points to the start of the list

private:
    // Item Addition Functions
    // Add a new item at the start of the list
    void insertAtBeginning(Item* target) {

        // Assigning pointers
        headPtr->prev = target;     // old headPtr points backwards to new headPtr
        target->next = headPtr;     // make this item point to the previous start
        headPtr = target;           // Makes the start point to the new item
    }

    // Add a new item at the end of the list
    void insertAtEnd(Item* target) {

        // Traverse to the last Item in the list
        Item* temp = headPtr;
        // moves to the next item as long as it exists (until it hits NULL)
        while (temp->next) {
            temp = temp->next;
        }
        // Update the last item's next pointer to the new item
        temp->next = target;
        target->prev = temp;
    }

    // Item Deletion Functions

    // Delete the first item from the list
    void deleteFromBeginning() {
        Item* temp = headPtr;
        headPtr = temp->next;
        delete temp;
    }

    // Delete the last item in the list
    void deleteFromEnd() {
        // Traversing to the second to last node
        Item* temp = headPtr;
        // checks that the next item points to another "next" item
        while (temp->next->next) {
            temp = temp->next;
        }

        // Delete the last item
        delete temp->next;
        // Set the second to last item's pointer to NULL
        temp->next = NULL;
    }

    // Function to actually delete items
    void delItem(Item* target) {
        // Variables
        Item* p = target->prev;     // Hold target item's previous pointer
        Item* n = target->next;     // Hold target item's next     pointer

        // Processes
        // Check if the target is the headPtr
        if (headPtr == target) {
            // Does a "next" item exist?
            if (target->next) {
                headPtr = target->next; // next item becomes the new headPtr
                n->prev = NULL;         // next item's previous pointer gets wiped
                delete target;          // Delete target for memory
                return;     // Exit function
            }
            // If headPtr is the only item in the list
            else {
                headPtr = NULL;
                delete target;
                return;     // Exit function
            }
        }

        // Else replace appropriate links
        else {
            // If the target item has no next pointer, set previous item's next pointer to NULL
            if (!target->next) {
                p->next = NULL;
                delete target;
                return;     // Exit function
            }

            // If the target does have a next pointer, replace appropriate pointers
            else if (target->next) {
                p->next = n;
                n->prev = p;

                delete target;
                return;     // Exit function
            }

        }

        // delete target to free up memory
        delete target;

    }

    // Miscellaneous Functions
    
    // Print Item
    void print(Item* temp) {
        cout << "Item Name: " << temp->name << "\nItem ID: " << temp->ID <<
            "\nItem Price: $" << temp->price << "\nItem Stock: " << temp->stock <<
            "\nItem Department: " << temp->department << " in Aisle: " << temp->aisle << endl << endl;
        return;     // Exit function
    }
  
public:
    Inventory() : headPtr(NULL) {} // Constructor to initialize the head pointer to null

    Item* getHead() {
        return headPtr;
    }
    // Functions 
    
    //view the inventory
    void view() {
        if (!headPtr) {
            cout << "Inventory is empty.\n";
            return;
        }
    
        cout << left << setw(10) << "ID"
            << setw(20) << "Name"
             << setw(10) << "Qty"
             << setw(10) << "Price"
             << setw(15) << "Department"
             << setw(10) << "Aisle"
             << setw(10) << "Status" << endl;
    
        cout << string(85, '-') << endl;
    
        Item* temp = headPtr;
        double totalValue = 0;
    
        while (temp) {
            string status;
            if (temp->stock == 0) status = "Out";
            else if (temp->stock < 5) status = "Low";
            else status = "In";
    
            cout << left << setw(10) << temp->ID
                 << setw(20) << temp->name
                 << setw(10) << temp->stock
                 << "$" << fixed << setprecision(2) << setw(9) << temp->price
                 << setw(15) << temp->department
                 << setw(10) << temp->aisle
                 << setw(10) << status << endl;
    
            totalValue += temp->stock * temp->price;
            temp = temp->next;
        }
    
        cout << "\nTotal Inventory Value: $" << fixed << setprecision(2) << totalValue << endl;
    }

    // Add Item
    void addItem(string n, int id, double p, int s, string dept, string a) {

        Item* newItem = new Item();     // creates a newItem variable holding the adress of the new item.

        // Assigning data
        newItem->name = n;
        newItem->ID = id;
        newItem->price = p;
        newItem->stock = s;
        newItem->department = dept;
        newItem->aisle = a;


        // Check if list is empty and add new item if it does
        if (!headPtr) {
            headPtr = newItem;
            return;     // Exit function
        }

        Item* temp = headPtr;   // Start at beginning of list
        
        // Check and add item to start of list
        if (temp->name > newItem->name) {
            insertAtBeginning(newItem);
            return;
        }

        //temp = temp->next;      // move forward off of the headPtr

        // Traverse List and check as we go. Probably
        while (temp) {
            if (temp->name > newItem->name) {
                newItem->next = temp;
                newItem->prev = temp->prev;
                
                // temporarily store temp's address
                Item* temp2 = temp;

                // Go back to assign next pointer
                temp = temp->prev;
                temp->next = newItem;

                // Back to original temp position
                temp = temp2;
                temp->prev = newItem;                

                return;
            }
            else {
                temp = temp->next;
            }
        }

        // If we've reached the end of the list, add it to the end
        if (!temp) {
            insertAtEnd(newItem);
            return;
        }

    }

    // Add items to the system from a file
    void import() {
    string folder = "./inventory_history";
    if (!fs::exists(folder) || !fs::is_directory(folder)) {
        cout << "No inventory history folder found.\n";
        return;
    }

    cout << "Available Inventory Files:\n";
    vector<string> fileList;
    int index = 1;

    for (const auto& entry : fs::directory_iterator(folder)) {
        if (entry.path().extension() == ".txt") {
            cout << index << ". " << entry.path().filename().string() << endl;
            fileList.push_back(entry.path().string());
            index++;
        }
    }

        if (fileList.empty()) {
            cout << "No valid inventory files found.\n";
            return;
        }

        int choice;
        cout << "\nSelect a file to import (by number): ";
        cin >> choice;

        if (choice < 1 || choice > fileList.size()) {
            cout << "Invalid choice.\n";
            return;
        }

        string selectedFile = fileList[choice - 1];

        ifstream file(selectedFile);
        if (!file.is_open()) {
            cout << "Failed to open selected file.\n";
            return;
        }

        // Clear current list before importing
        while (headPtr) {
            deleteFromBeginning();
        }

        string name, department, aisle;
        int ID, stock;
        double price;

        while (file >> ID >> name >> stock >> price >> department >> aisle) {
            addItem(name, ID, price, stock, department, aisle);
        }

        file.close();
        cout << "Inventory successfully imported from " << selectedFile << endl;
    }

    // Del Item
    void delSelection() {
        // Check that the list isn't empty
        if (!headPtr) {
            cout << "List is empty." << endl;
            return;
        }

        Item* temp = headPtr;
        string name;

        // Get Input
        cout << "What item would you like to delete?\nItem Name: ";
        cin >> name;

        // Find Item
        // While temp exists, search the list
        while (temp) {
            if (temp->name == name) {
                // Get user confirmation (to be implemented)
                delItem(temp);
                return;             // Exit function
            }

            else if (temp->next) {
                temp = temp->next;
            }

            else {
                // If item cannot be found
                cout << "Item not found, please try again." << endl;
                delSelection();       // Call function again
                return;             // Exit function once successfully executed
            }
        }
    }

    // Miscellaneous Functions
    
    // Edit Item
    void editStock(account user){
        // Checks whether or not they can edit the stock
        if (user.privilege != "manager" && user.privilege != "worker") {
            cout << "Access denied: insufficient privilege.\n";
            return;
        }
        // Check the list isn't empty
        if (!headPtr) {
            cout << "List is empty." << endl;
            return;     // Exit function
        }

        // Variables
        string target;          // Target Item's Name
        Item* temp = headPtr;   // temp item
        int s;                  // New Stock

        // Get user input
        cout << "Please input desired item's name: ";
        cin >> target;

        // Traverse the list until we find the right item or reach the end of the list (While temp exists)
        while (temp) {
            // check if current item is the target item
            if (temp->name == target) {
                cout << "Current Item Stock is: " << temp->stock << endl;
                cout << "Please input new stock: ";
                cin >> s;

                temp->stock = s;

                cout << "New stock for " << temp->name << " is: " << temp->stock << endl;

                return;     // Exit function
            }

            // Move forward in the list
            else {
                temp = temp->next;
            }

        }

        // In case item is not found
        cout << "Could not find item." << endl;

        return;
    }

    // Display the list (To be Updated to look better in the future)
    void displayList() {
        if (!headPtr) {
            cout << "List is empty." << endl;
            return;
        }

        Item* temp = headPtr;   // used to traverse the list

        // Print the information in the list as long as it exists
        while (temp) {
            print(temp);
            temp = temp->next;  // Move to next item
        }

        cout << "End of List" << endl;     // Prints when at the end of list
    }

    // Search for an Item by name
    void search() {
        // Check the list isn't empty
        if (!headPtr) {
            cout << "List is empty." << endl;
            return;     // Exit function
        }

        // Variables
        Item* temp = headPtr;
        string target;

        // Get user input
        cout << "Please input desired item's name: ";
        cin >> target;

        // Traverse the list until we find the right item or reach the end of the list (While temp exists)
        while (temp) {
            // check if current item is the target item
            if (temp->name == target) {
                print(temp);
                return;     // Exit function
            }

            // Move forward in the list
            else {
                temp = temp->next;
            }

        }

        // In case item is not found
        cout << "Could not find item." << endl;
        return;
    }

    // Export items to a file
    void exportInventory() {
        ofstream file("inventory.txt");
        if (!file.is_open()) {
            cout << "Failed to open file for export.\n";
            return;
        }

        Item* temp = headPtr;
        while (temp) {
            file << temp->ID << " "
                 << temp->name << " "
                 << temp->stock << " "
                 << temp->price << " "
                 << temp->department << " "
                 << temp->aisle << endl;
            temp = temp->next;
        }

        file.close();
        cout << "Inventory succesfully exported file.\n";
}

    void addEmployeeAccount() {
        ofstream out("accountInformation.txt", ios::app); // Append mode
        if (!out) {
            cout << "Error opening file.\n";
            return;
        }
    
        string username, password, name, phone;
        cout << "Enter employee username: "; cin >> username;
        cout << "Enter password: "; cin >> password;
        cout << "Enter full name: "; cin.ignore(); getline(cin, name);
        cout << "Enter phone number: "; cin >> phone;
    
        out << "- " << username << " " << password << " "
            << name << " " << phone << endl;
    
        out.close();
        cout << "Employee account added.\n";
    }
    
    void updateItemInfo(account user, Inventory& inventory) {
        if (user.privilege != "manager") {
            cout << "Access Denied. Only managers can update item info.\n";
            return;
        }
    
        string target;
        cout << "Enter item name to update: ";
        cin >> target;
    
        Item* temp = inventory.getHead();  // You'll need to expose `headPtr` via a getter
    
        while (temp) {
            if (temp->name == target) {
                int choice;
                cout << "1. Update name\n2. Update price\nChoice: ";
                cin >> choice;
    
                if (choice == 1) {
                    string newName;
                    cout << "New name: "; cin >> newName;
                    temp->name = newName;
                } else if (choice == 2) {
                    double newPrice;
                    cout << "New price: "; cin >> newPrice;
                    temp->price = newPrice;
                }
    
                cout << "Update successful.\n";
                return;
            }
            temp = temp->next;
        }
    
        cout << "Item not found.\n";
    }
    
};

/*
int test() {
    // Test Code
    Inventory inventory;
    account testEmployee, testCustomer;

    // Set up test accounts
    testEmployee.setName("Test Employee");
    testEmployee.setUsername("emp01");
    testEmployee.setPrivilege("worker");

    testCustomer.setName("Test Customer");
    testCustomer.setUsername("cust01");
    testCustomer.setPrivilege("costumer");

    // Add a sample item
    inventory.addItem("Orange Juice", 1001, 3.99, 50, "Beverages", "B2");

    // Attempt stock update with valid employee
    cout << "\n[TEST 1] Valid employee updating stock:" << endl;
    inventory.editStock(testEmployee);  // should proceed

    // Attempt stock update with invalid customer
    cout << "\n[TEST 2] Invalid customer attempting to update stock:" << endl;
    inventory.editStock(testCustomer);  // should deny access

    // Attempt to Display empty list
    inventory.displayList();

    // Attempt to Delete in an empty list
    inventory.delSelection();

    // Attemp to Search in an empty list
    inventory.search(); 

    // Adding items to the list
    inventory.addItem("Carrots", 0001, 8.00, 500, "Vegetables", "A1");      // Add item when list is empty 
    inventory.addItem("Lettuce", 0002,  8.99, 450, "Vegetables", "A1");     // Add item at end of list
    inventory.addItem("Bananas", 0003, 8.50, 400, "Fruits", "A2");          // Add item at start of list
    inventory.addItem("Cherries", 0004, 5.50, 400, "Fruits", "A2");         // Add item in the middle of list
    inventory.addItem("Watermelon", 0005, 10.00, 100, "Fruits", "A2");      // Add item at end of list
    inventory.addItem("Apples", 0006, 7.60, 495, "Fruits", "A2");           // Add item at start of list    
    // Display list
    inventory.displayList();    

    // Delete an item
    inventory.delSelection();   

    // Display updated List
    inventory.displayList();    

    // Search for an item
    inventory.search();
    inventory.search(); 

    // Edit Item Stock
    inventory.editStock();  

    if (currentUser.privilege == "manager") {
        inventory.addItem("Oranges", 101, 1.99, 100, "Produce", "A2");
    } else {
        cout << "Access Denied. Only managers can add items.\n";
    }
    
    if (currentUser.privilege == "manager") {
        inventory.delSelection();  // prompts for item name
    } else {
        cout << "Access Denied. Only managers can remove items.\n";
    }

    inventory.editStock(currentUser); // Only works if currentUser is employee/manager
    return 0;
} */
