#pragma once
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class account {
private:
    string username;
    string password;
    string name;
    string phone;
    string privilege;
    int tries;

public:
    // Setters
    void setUsername(string user);
    void setPassword(string pass);
    void setName(string n);
    void setPhone(string digits);
    void setPrivilege(string priv);

    // Getters
    string getUsername() const;
    string getPassword() const;
    string getName() const;
    string getPhone() const;
    string getPrivilege() const;

    // Utilities
    void failedAtt();
    bool checkUser(string user);
    bool checkTries();
    void displayUsername();
    void displayName();
    void displayPhone();
    void displayInfo();
    void displayWelcome();
};
