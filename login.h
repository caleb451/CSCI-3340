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
	int tries = 0;
	system("cls");
	cout << setw(5) << " " << "Login Page\n";
	cout << setfill('-') << setw(25) << "-" << setfill(' ');
	do{
		cout << "\nUsername: ";
		cin >> username;
		cout << "Password: ";
		cin >> password;
		
		for (i = 0; i < size; i++) {
			if (acc[i].checkUser(username)) {
				while (acc[i].checkTries()) {
					if (acc[i].password == password) {
					    accountIndex = i;
						cout << "Login success.\n" << "Welcome " << acc[i].name << "!\n";
						break;
					}
					else {
						cout << "Password incorrect.\n\n";
						acc[i].failedAtt();
						cout << "Username: " << acc[i].username;
						cout << "\nPassword: ";
						cin >> password;
					}
				}
				if (!acc[i].checkTries()) {
					cout << "Too many attempts\n";
					return account{};
				}
				else
					break;
			}
		}
		if (i == size){
    		cout << "\nUsername does not exist. Please try another.\n";
			cout << "Press Enter to continue ...";
			cin.sync();
			cin.ignore();
			cin.get();
			system ("cls");
		}
		else 
		    break;
	}while (true);
	return acc[accountIndex];
}