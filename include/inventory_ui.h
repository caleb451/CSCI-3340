#pragma once
#include "account_ui.h"
#include <vector>
#include <string>

void ShowInventoryUI(const account& currentUser, bool& viewingInventory);
void loadInventoryFromFile(vector<vector<string>>& data, const string& filename = "inventory.txt");
void importInventoryFromFile(const string& newFile, string& importMessage);