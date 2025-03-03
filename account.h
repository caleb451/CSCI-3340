#pragma once
#include <string>
#include <iostream>
using namespace std;

class account{ //define account class to manipulate and store employee and costumer accounts
public:
	void setUsername(string user);
	void setPassword(string pass);
	void setName(string n);
	void setPhone(string digits);
	bool checkTries();
	//define display functions to display the information of the accounts to users.
	void displayUsername();
	void displayName();
	void displayPhone();
	//Variables that will store account information.
	string username, password, name, phone;
	int tries;
};

void account::setUsername(string user) {
	username = user;
}

void account::setPassword(string pass) {
	password = pass;
}

void account::setName(string n) {
	name = n;
}

void account::setPhone(string digits) {
	phone = digits;
}

void account::displayUsername() {
	cout << "Username: " << username;
}

void account::displayName() {
	cout << "Name: " << name;
}

void account::displayPhone() {
	cout << "Phone number: " << phone;
}

// bool account::checkTries() {
// 	if(tries < 3)
// 		return TRUE;
// 	else
// 		return FALSE;
// }
