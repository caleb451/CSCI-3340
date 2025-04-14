#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <conio.h> // For _getch()
#include "account.h"
#include "addAcc.h"

using namespace std;


// Function to mask password input
string getHiddenPassword() {
    string password;
    char ch;

    while ((ch = _getch()) != '\r') { // Enter key ends input
        if (ch == '\b') { // Backspace
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        } else {
            password.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

account login() {
	
    vector<account> acc = addAcc();
    string username, password;
    char choice;
    int tries = 0;

    system("cls");
    cout << setw(5) << " " << "Login Page\n";
    cout << setfill('-') << setw(25) << "-" << setfill(' ');

    while (true) {
        cout << "\nDo you want to login? (y/n): ";
        cin >> choice;

        if (choice == 'n' || choice == 'N') {
            cout << "Exiting program.\n";
            return account{};
        } else if (choice == 'y' || choice == 'Y') {
            break;
        } else {
            cout << "Invalid input. Please try again.\n";
        }
    }
	
    while (true) {
		system("cls");
    	cout << setw(5) << " " << "Login Page\n";
    	cout << setfill('-') << setw(25) << "-" << setfill(' ');
        cout << "\nUsername: ";
        cin >> username;

        // Try to find matching user
        int i;
        bool userFound = false;
        for (i = 0; i < acc.size(); i++) {
            if (acc[i].checkUser(username)) {
                userFound = true;

                tries = 0;
                while (tries < 3) {
                    cout << "Password: ";
                    password = getHiddenPassword();

                    if (acc[i].password == password) {
                        cout << "Login success.\nWelcome " << acc[i].name << "!\n";
                        return acc[i];
                    } else {
                        cout << "Incorrect password. Try again.\n";
                        tries++;
                    }
                }

                cout << "Too many failed attempts. Returning as guest.\n";
                return account{};
            }
        }

        if (!userFound) {
            cout << "\nUsername does not exist. Please try again.\n";
            cout << "Press Enter to continue ...";
            cin.ignore();
            cin.get();
            system("cls");
        }
    }
}
