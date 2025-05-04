#ifndef LOGIN_UI_H
#define LOGIN_UI_H

#include <string>
#include "account_ui.h"

using namespace std;

void ShowLoginUI(string& username, string& password, bool& loggedIn, account& currentUser);
account login(const string& username, const string& password);
bool validate_credentials(const string& username, const string& password, string& privilege, account& currentUser);

#endif