#pragma once
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class account{ //define account class to manipulate and store employee and costumer accounts
public:
	void setUsername(string user);
	void setPassword(string pass);
	void setName(string n);
	void setPhone(string digits);
	void setPrivilege(string priv);
	void failedAtt();
	bool checkUser(string user);
	bool checkTries();
	//define display functions to display the information of the accounts to users.
	void displayUsername();
	void displayName();
	void displayPhone();
    void displayInfo();
    void displayWelcome();
	//Variables that will store account information.
	string username, password, name, phone, privilege;
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

bool account::checkTries() {
	if(tries < 3)
		return true;
	else
		return false;
}

void account::failedAtt(){
    tries ++;
}

bool account::checkUser(string user){
    if (user == username)
        return true;
    else
        return false;
}

void account::setPrivilege(string priv){
    privilege = priv;
}

void account::displayInfo(){
    cout << "\n\n\tAccount information";
    cout << endl << setw(30) << setfill('-') << "-" << setfill(' ');
    cout << left;
    cout << setw(18) << "\nName: " << name;
    cout << setw(18) << "\nUsername: " << username;
    cout << setw(18) << "\nPhone: " << phone;
    cout << setw(18) << "\nAccount type: " << privilege;
}

void account::displayWelcome(){
    cout << "\n\nWelcome " << name;
}
