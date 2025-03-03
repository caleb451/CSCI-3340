//This will send default responses to the user if they want to quit or go back.

#include <iostream>
#include <string>
using namespace std;


void quit(){
    cout << "Do you want to quit? (Y/N): ";
    char answer;
    cin >> answer;
    if (answer == 'Y' || answer == 'y'){
       cout << "Goodbye!";
        exit(0);
    }
}
void goBack(){
    cout << "Do you want to go back? (Y/N): ";
    char answer;
    cin >> answer;
    if (answer == 'Y' || answer == 'y'){
        return;
    }
}