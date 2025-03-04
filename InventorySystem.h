/*
Dev: Jay
Program: System in charge of handling the storage of items in the inventory and related functions
*/

/*
To Be Implemented:
general "delete" function
*/

#include <iostream>
#include <string>

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
    Item* prev;     // points to the previous item in the list

};


// Class for the linked list
class Inventory {
    Item* headPtr;      // Points to the start of the list
    
public:
    Inventory() : headPtr(NULL) {} // Constructor to initialize the head pointer to null



    // Functions 

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

    // Find a way to merge those two functions at some point.
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

    // Delete the first item from the list
    void deleteFromBeginning() {
        // Check that the list isn't empty
        if (!headPtr) {
            cout << "List is empty." << endl;
            return;
        }

        Item* temp = headPtr;   
        headPtr = temp->next;
        delete temp;
    }

    // Delete the last item in the list
    void deleteFromEnd() {
        // Check that the list isn't empty
        if (!headPtr) {
            cout << "List is empty." << endl;
            return;
        }

        // Check if there is only one item in the list
        if (!headPtr->next) {
            delete headPtr;     // Delete the pointer
            headPtr = NULL;     // Set the pointer to NULL
            return;
        }

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

    // Again, find a way to combine the delete functions into one all purpose delete function. Problem for Future Jay.

    // Display the list (To be Updated to look better in the future)
    void display() {
        if (!headPtr) {
            cout << "List is empty." << endl;
            return;
        }

        Item* temp = headPtr;   // used to traverse the list

        // Print the information in the list as long as it exists
        while (temp) {
            cout << "Item Name: " << temp->name << "\nItem ID: " << temp->ID <<
                "\nItem Price: $" << temp->price << "\nItem Stock: " << temp->stock <<
                "\nItem Department: " << temp->department << " in Aisle: " << temp->aisle << endl << endl;

            temp = temp->next;  // Move to next item
        }

        cout << "End of List" << endl;     // Prints when at the end of list
    }

};

int test() {

    // Test Code
    Inventory inventory;

    // Attempt to display empty list
    inventory.display();

    // Adding items to the list
    inventory.addItem("Carrots", 0001, 8.00, 500, "Vegetables", "A1");      // Add item when list is empty 
    inventory.addItem("Lettuce", 0002,  8.99, 450, "Vegetables", "A1");     // Add item at end of list
    inventory.addItem("Bananas", 0003, 8.50, 400, "Fruits", "A2");          // Add item at start of list
    inventory.addItem("Cherries", 0004, 5.50, 400, "Fruits", "A2");         // Add item in the middle of list
    inventory.addItem("Watermelon", 0005, 10.00, 100, "Fruits", "A2");      // Add item at end of list
    inventory.addItem("Apples", 0006, 7.60, 495, "Fruits", "A2");           // Add item at start of list


    // Display list
    inventory.display();

    return 0;
}

