#ifndef LOGIN_UI_H
#define LOGIN_UI_H

#include <string>
#include "account_ui.h"

using namespace std;

void ShowLoginUI(string& username, string& password, bool& loggedIn, account& currentUser);
account login(const string& username, const string& password);

#endif