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
#include "addEmp.h"
#include "account.h"

using namespace std;

int main(){
    Inventory inventory;
    char answer;
    bool quit = false;
    // (void) system("cls");
    // for (int i = 0; i < 3; i++){
    //     cout << "Loading..";
    //     Sleep(500);
    //     cout << ".";
    //     Sleep(1000);
    //     (void) system("cls");
    // }
    
    do{
        answer = start();
        switch(answer){
            case '1':
                login();
                break;
            case '2':
                system("cls");
                cout << "View Inventory" << endl;
                cout << "------------------------" << endl;
                inventory.display();
                goBack();
                break;
            default:
                cout << "Invalid input. Please try again." << endl;
                end();
                break;
        }
    }while(quit != true);
    return 0;
}