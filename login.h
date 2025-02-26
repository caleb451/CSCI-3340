#pragma once
#include <iostream>
#include "account.h"
#include <vector>
#include "addEmp.h"
#include <fstream>
using namespace std;

void login() {
	vector<account> empAcc = addEmp();
	string username, password;
	int empSize = empAcc.size(), i;
	int account, tries;

	cout << "Username: ";
	cin >> username;
	cout << "Password: ";
	cin >> password;
	
	while (true){
		for (i = 0; i < empSize; i++) {
			if (empAcc[i].username == username) {
				tries = 0;
				while (tries < 3) {
					if (empAcc[i].password == password) {
						account = i;
						cout << "Login success.\n" << "Welcome " << empAcc[i].name << "!\n";
						break;
					}
					else {
						cout << "Password incorrect.\n\n";
						tries += 1;
						cout << "Username: " << username;
						cout << "/nPassword: ";
						cin >> password;
					}
				}
				if (tries == 3) {
					cout << "Too many attempts, please try again later.\n";
				}
				else
					break;
			}
		}
		if (i == empSize) {
			cout << "\nUsername does not exist. Please try another.\n";
			cout << "\nUsername: ";
			cin >> username;
			cout << "Password: ";
			cin >> password;
		}
		else
			break;
	}
}