#pragma once
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void createAccount() {
    string role, username, password, fname, lname, phone;
    char privilegeMarker;

    cout << "Create New Account\n------------------" << endl;
    cout << "Enter role (manager/worker/costumer): ";
    cin >> role;

    if (role == "manager") privilegeMarker = '*';
    else if (role == "worker") privilegeMarker = '-';
    else privilegeMarker = '+';

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter first name: ";
    cin >> fname;
    cout << "Enter last name: ";
    cin >> lname;
    cout << "Enter phone number: ";
    cin >> phone;

    ofstream file("accountInformation.txt", ios::app);
    if (file.is_open()) {
        file << privilegeMarker << " " << username << " " << password << " "
             << fname << " " << lname << " " << phone << endl;
        file.close();
        cout << "Account created successfully!" << endl;
    } else {
        cerr << "Error: Could not open file for writing." << endl;
    }

    goBack();
}