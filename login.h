#pragma once
#include <iostream>
#include "account.h"
#include <vector>
#include "addAcc.h"
#include <fstream>
#include <iomanip>
using namespace std;

account login() {
	vector<account> acc = addAcc();
	string username, password;
	int size = acc.size(), i;
	int accountIndex;
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
        } 
        else if (choice == 'y' || choice == 'Y') {
            break;  // proceed to login input
        } 
        else {
            cout << "Invalid input. Please try again.\n";
        }
    }
	
	while (true) {
		system("cls");
		cout << setw(5) << " " << "Login Page\n";
		cout << setfill('-') << setw(25) << "-" << setfill(' ');
        cout << "\nUsername: ";
        cin >> username;
        cout << "Password: ";
        cin >> password;

        for (i = 0; i < size; i++) {
			if (acc[i].checkUser(username)) {
				while (acc[i].checkTries()) {
					if (acc[i].password == password) {
						cout << "Login success.\n" << "Welcome " << acc[i].name << "!\n";
						return acc[i];
					} else {
						cout << "Password incorrect.\n\n";
						acc[i].failedAtt();
						cout << "Username: " << acc[i].username;
						cout << "\nPassword: ";
						cin >> password;
					}
				}
		
				cout << "Too many attempts\n";
				return account{};
			}
		}
		// No match found
		cout << "\nUsername does not exist. Please try another.\n";
		cout << "Press Enter to continue ...";
		cin.ignore();
		cin.get();
		system("cls");
    }
}