/*
We will use this file to get everthing together. The other files like "example.cpp" is
what we will use to build off of
*/

#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include "include/systemCheck.h"
#include "include/InventorySystem.h"
#include "include/login.h"
#include "include/addEmp.h"
#include "include/account.h"

using namespace std;

int main() {
    Inventory inventory;
    char answer;
    account currentUser;
    bool quit = false;

    do {
        // Login Step
        currentUser = login(); // manager, worker, or guest
        Sleep(1000);
        (void) system("cls");

        // Show login status
        if (currentUser.privilege == "manager" || currentUser.privilege == "worker") {
            cout << "Login success." << endl;
            cout << "Welcome " << currentUser.name << "!" << endl;
        } else {
            cout << "Continuing as a Guest, you will have limited access." << endl;
        }

        Sleep(2000);
        load();

        // Main Menu
        do {
            answer = menu(currentUser);
            switch (answer) {
                case '1': // Login again
                    if (currentUser.privilege == "manager" || currentUser.privilege == "worker") {
                        cout << "Logging out...\n";
                        Sleep(1000);
                        currentUser = account{}; // Reset to guest
                        currentUser.privilege = "guest"; // explicitly mark as guest
                    } 
                    else {
                        currentUser = login();
                        Sleep(1000);
                        (void) system("cls");
                    }
                    break;

                case '2': // View Inventory
                    system("cls");
                    cout << "View Inventory" << endl;
                    cout << "------------------------" << endl;
                    inventory.view();
                    if (currentUser.privilege == "worker"){
                        char subChoice;
                        cout << "\nManager Options:" << endl;
                        cout << "1. Update Item" << endl;
                        cout << "Select an option: ";
                        cin >> subChoice;
                        if (subChoice == '1')
                            inventory.editStock(currentUser);
                        else
                            goBack();
                        
                    }
                    else if (currentUser.privilege == "manager") {
                        char subChoice;
                        do {
                            cout << "\nManager Options:" << endl;
                            cout << "1. Update Item" << endl;
                            cout << "2. Remove Item" << endl;
                            cout << "3. Add Item" << endl;
                            cout << "Select an option: ";
                            cin >> subChoice;
                
                            switch (subChoice) {
                                case '1':
                                    inventory.updateItemInfo(currentUser, inventory);
                                    break;
                                case '2':
                                    inventory.delSelection();
                                    break;
                                case '3': {
                                    string name, dept, aisle;
                                    int id, stock;
                                    double price;
                                    cout << "Enter item name: "; cin >> name;
                                    cout << "Enter item ID: "; cin >> id;
                                    cout << "Enter stock: "; cin >> stock;
                                    cout << "Enter price: "; cin >> price;
                                    cout << "Enter department: "; cin >> dept;
                                    cout << "Enter aisle: "; cin >> aisle;
                                    inventory.addItem(name, id, price, stock, dept, aisle);
                                    break;
                                }
                                default:
                                    cout << "Invalid option. Try again.\n";
                                    break;
                            }
                        } while (subChoice != 'b' && subChoice != 'B');
                    }
                    goBack();
                    break;
                case '3':
                    if (currentUser.privilege == "manager") {
                        createAccount();
                    }
                    break;
                case '4':
                    inventory.importInv(currentUser);
                    break;
                case '5':
                    inventory.exportInv(currentUser);
                    break;
                case 'q': // Quit program
                case 'Q':
                    quit = true;
                    break;

                default:
                    cout << "Invalid input. Please try again." << endl;
                    end();
                    break;
            }

        } while (!quit && (answer != '1')); // if they pick '1', we re-login

    } while (!quit);

    return 0;
}