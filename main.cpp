/*
We will use this file to get everthing together. The other files like "example.cpp" is
what we will use to build off of
*/

#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include "login.h"
#include "addEmp.h"
#include "account.h"

using namespace std;

int main(){
    char answer;
    // (void) system("cls");
    // for (int i = 0; i < 3; i++){
    //     cout << "Loading..";
    //     Sleep(500);
    //     cout << ".";
    //     Sleep(1000);
    //     (void) system("cls");
    // }
    
    cout << "------------------------" << " [STORE NAME] " << "------------------------" << endl;
    cout << setw(20) << left << "1. Login" << endl;
    cout << setw(20) << "2. View Inventory" << endl;
    cout << setw(20)<< right << "Select one of the options above:" << endl;
    cin >> answer;
    if (answer == '1')
        login();




    //login();
}