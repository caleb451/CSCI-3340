#ifndef LOGIN_UI_H
#define LOGIN_UI_H

#include <string>
#include "account.h"

void ShowLoginUI(std::string& username, std::string& password, bool& loggedIn, account& currentUser);
account login(const std::string& username, const std::string& password);

#endif