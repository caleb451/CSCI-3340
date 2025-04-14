/*
We will use this file to get everthing together. The other files like "example.cpp" is
what we will use to build off of
*/

#include <iostream>
#include <string>
#include <windows.h>
#include <iomanip>
#include "systemCheck.h"
#include "InventorySystem.h"
#include "login.h"
//#include "addEmp.h"
#include "account.h"

using namespace std;

int main(){
    Inventory inventory;
    char answer;
    account currentUser;
    bool quit = false;
    
    do{
        currentUser = login(); // Call the login function to get the current user
        if (currentUser.privilege == "manager" || currentUser.privilege == "worker") {
            cout << "Login success." << endl;
            cout << "Welcome " << currentUser.name << endl;
        }
        else{
            Sleep(2000);
            (void) system("cls");
            cout << "Continuing as a Guest, you will have limited access." << endl;
            Sleep(2000);
            load();
            answer = start(currentUser);
        }
        switch(answer){
            case '1':
                answer = start(currentUser);
                goBack();
                break;
            case '2':
                system("cls");
                cout << "View Inventory" << endl;
                cout << "------------------------" << endl;
                goBack();
                break;
            case 'q':
                quit = true;
                break;
            default:
                cout << "Invalid input. Please try again." << endl;
                end();
                break;
        }
    }while(quit != true);
    return 0;
}