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
    vector<string> info = split(empInfo, ' ');

    employee.setUsername(info[0]);
    employee.setPassword(info[1]);
    employee.setName(info[2] + ' ' + info[3]);
    employee.setPhone(info[4]);
	return employee;
}

vector<account> addEmp() {
    ifstream empInfo("EmployeeInformation.txt");

    if (!empInfo) {
        cout << "Error: file could not be opened." << endl;
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