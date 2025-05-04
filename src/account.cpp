#include "account.h"

void account::setUsername(string user) { username = user; }
void account::setPassword(string pass) { password = pass; }
void account::setName(string n) { name = n; }
void account::setPhone(string digits) { phone = digits; }
void account::setPrivilege(string priv) { privilege = priv; }

void account::failedAtt() { tries++; }
bool account::checkTries() { return tries < 3; }
bool account::checkUser(string user) { return user == username; }

void account::displayUsername() { cout << "Username: " << username; }
void account::displayName() { cout << "Name: " << name; }
void account::displayPhone() { cout << "Phone number: " << phone; }

string account::getUsername() const {return username;}
string account::getPrivilege() const {return privilege;}

void account::displayInfo() {
    cout << "\n\n\tAccount information";
    cout << endl << setw(30) << setfill('-') << "-" << setfill(' ');
    cout << left;
    cout << setw(18) << "\nName: " << name;
    cout << setw(18) << "\nUsername: " << username;
    cout << setw(18) << "\nPhone: " << phone;
    cout << setw(18) << "\nAccount type: " << privilege;
}

void account::displayWelcome() {
    cout << "\n\nWelcome " << name;
}
