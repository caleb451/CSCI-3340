#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string trim(const string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
}

int main() {
    ifstream inFile("accountInformation.txt");
    ofstream outFile("accounts_cleaned.txt");

    if (!inFile.is_open() || !outFile.is_open()) {
        cerr << "Failed to open files.\n";
        return 1;
    }

    string line;
    while (getline(inFile, line)) {
        istringstream ss(line);
        string symbol, u, p, fname, lname, phone;

        symbol = line.substr(0, 1);
        ss >> symbol >> u >> p >> fname >> lname >> phone;

        u = trim(u);
        p = trim(p);
        fname = trim(fname);
        lname = trim(lname);
        phone = trim(phone);

        if (!u.empty() && !p.empty() && !fname.empty() && !lname.empty()) {
            outFile << symbol << " " << u << " " << p << " " << fname << " " << lname << " " << phone << '\n';
        }
    }

    cout << "Cleaned data written to accounts_cleaned.txt\n";
    return 0;
}