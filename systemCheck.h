//This will send default responses to the user if they want to quit or go back.
#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "account.h"
using namespace std;

//Function prototypes
void goBack();
void end();
void load();
char start(account& currentUser);

//Function definitions
char start(account& currentUser){
    char answer;
    system("cls");
    cout << "------------------------" << " [STORE NAME] " << "------------------------" << endl;
    if(currentUser.privilege == "manager" || currentUser.privilege == "worker"){
        cout << "Welcome " << currentUser.name << endl;
    }
    else
        currentUser.setPrivilege("guest");
    cout << "Logged In As: " << currentUser.privilege << endl;
    cout << setw(20) << left << "1. Login" << endl;
    cout << setw(20) << "2. View Inventory" << endl;
    if (currentUser.privilege == "manager") {
        cout << setw(20) << "3. Create New Account" << endl;
    }
    cout << setw(20)<< right << "Select one of the options above:" << endl;
    cin >> answer;
    return answer;
}
void end(){
    cout << "Do you want to quit? (Y/N): ";
    char answer;
    cin >> answer;
    if (answer == 'Y' || answer == 'y'){
       cout << "Program terminated." << endl;
        exit(0);
    }
    else
        goBack();
}
void goBack(){
    cout << "Do you want to go back? (Y/N): ";
    char answer;
    cin >> answer;
    if (answer == 'Y' || answer == 'y'){
        return;
    }
    else
        end();
}

void load(){
    (void) system("cls");
    for (int i = 0; i < 3; i++){
        cout << "Loading..";
        Sleep(500);
        cout << ".";
        Sleep(1000);
        (void) system("cls");
    }
}