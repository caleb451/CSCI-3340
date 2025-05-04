#pragma once
#include <iostream>
#include "account.h"
#include <vector>
#include <fstream>
using namespace std;

vector<string> split(const string& str, char delimiter) {
    vector<string> result;
    size_t start = 0;
    size_t end = str.find(delimiter);

    // Loop through the string to find all delimiters
    while (end != string::npos) {
        result.push_back(str.substr(start, end - start));  // Extract the substring
        start = end + 1;  // Move start past the delimiter
        end = str.find(delimiter, start);  // Find the next delimiter
    }

    result.push_back(str.substr(start));  // Add the last part after the last delimiter
    return result;
}

account addinfo(string empInfo) {
	account employee;
    account currentUser;
    vector<string> info = split(empInfo, ' ');
    char x = info[0][0];
    
    switch(x){
        case '*':
            employee.privilege = "manager";
            break;
        case '-':
            employee.privilege = "worker";
            break;
        case '+':
            employee.privilege = "costumer";
            break;
        default:
            employee.privilege = "guest";
            currentUser.privilege = "guest";
    }
    employee.privilege = "manager";
    employee.username = info[1];
    employee.password = info[2];
    employee.name = info[3] + ' ' + info[4];
    employee.phone = info[5];

	return employee;
}

vector<account> addAcc() {
    ifstream empInfo("accountInformation.txt");
    if (!empInfo.is_open()) {
        cerr << "Error: file could not be opened." << endl;
        return {};
    }

    string line;
    vector<account> empAccounts;

    while (getline(empInfo, line)) {
        empAccounts.push_back(addinfo(line));
    }

    empInfo.close();
    return empAccounts;
}
