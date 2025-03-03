//This will send default responses to the user if they want to quit or go back.

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

//Function prototypes
void(goBack());
void(end());
char start();

//Function definitions
char start(){
    char answer;
    system("cls");
    cout << "------------------------" << " [STORE NAME] " << "------------------------" << endl;
    cout << setw(20) << left << "1. Login" << endl;
    cout << setw(20) << "2. View Inventory" << endl;
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