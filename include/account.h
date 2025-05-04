#pragma once
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class account {
public:
    string username;
    string password;
    string name;
    string phone;
    string privilege;
    int tries;

    void failedAtt() {
        tries++;
    }

    bool checkTries() {
        return tries < 3;
    }

    bool checkUser(string user) {
        return user == username;
    }

    void displayUsername() {
        cout << "Username: " << username;
    }

    void displayName() {
        cout << "Name: " << name;
    }

    void displayPhone() {
        cout << "Phone number: " << phone;
    }

    void displayInfo() {
        cout << "\n\n\tAccount information";
        cout << endl << setw(30) << setfill('-') << "-" << setfill(' ');
        cout << left;
        cout << setw(18) << "\nName: " << name;
        cout << setw(18) << "\nUsername: " << username;
        cout << setw(18) << "\nPhone: " << phone;
        cout << setw(18) << "\nAccount type: " << privilege;
    }

    void displayWelcome() {
        cout << "\n\nWelcome " << name;
    }
};
