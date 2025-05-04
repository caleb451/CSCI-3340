#pragma once
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class account {
public:
    void setUsername(string user);
    void setPassword(string pass);
    void setName(string n);
    void setPhone(string digits);
    void setPrivilege(string priv);
    void failedAtt();
    bool checkUser(string user);
    bool checkTries();
    void displayUsername();
    void displayName();
    void displayPhone();
    void displayInfo();
    void displayWelcome();

    string username, password, name, phone, privilege;
    int tries;
};