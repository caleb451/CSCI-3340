#include "inventory_ui.h"
#include "imgui.h"
#include <fstream>
#include <sstream>
#include "account_ui.h"
#include <filesystem>

using namespace std;
using namespace ImGui;

void loadInventoryFromFile(vector<vector<string>>& data, const string& filename) {
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string field;
        vector<string> row;

        while (getline(ss, field, ',')) {
            row.push_back(field);
        }
        if (!row.empty())
            data.push_back(row);
    }
}

void importInventoryFromFile(const string& newFile, string& importMessage) {
    namespace fs = std::filesystem;

    if (!fs::exists(newFile)) {
        importMessage = "File not found: " + newFile;
        return;
    }

    ifstream src(newFile);
    ofstream dst("inventory.txt", ios::trunc);  // Overwrite

    if (src && dst) {
        dst << src.rdbuf();
        importMessage = "Imported successfully from: " + newFile;
    } else {
        importMessage = "Failed to import from: " + newFile;
    }
}

void ShowInventoryUI(const account& currentUser, bool& viewingInventory) {
    BeginChild("InventoryContent", ImVec2(600, 500), true);

    Text("Logged in as: %s", currentUser.getPrivilege().c_str());
    Separator();

    static vector<vector<string>> inventory;
    static bool loaded = false;

    if (!loaded) {
        loadInventoryFromFile(inventory);
        loaded = true;
    }

    if (inventory.empty()) {
        Text("No inventory data found.");
    }

    if (BeginTable("InventoryTable", 6, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
        TableSetupColumn("Name");
        TableSetupColumn("ID");
        TableSetupColumn("Price");
        TableSetupColumn("Stock");
        TableSetupColumn("Department");
        TableSetupColumn("Aisle");
        TableHeadersRow();

        for (const auto& row : inventory) {
            if (row.size() < 6) continue;
            TableNextRow();
            for (int col = 0; col < 6; ++col) {
                TableSetColumnIndex(col);
                Text("%s", row[col].c_str());
            }
        }

        EndTable();
    }

    Spacing();

    if (Button("Back")) {
        viewingInventory = false;
        inventory.clear();     
        loaded = false;
        CloseCurrentPopup();
    }

    // Manager-only tools
    if (currentUser.getPrivilege() == "manager") {
        float buttonWidth = 150.0f;
        float spacing = 20.0f;
        float totalWidth = (buttonWidth * 2) + spacing;
        float startX = (GetContentRegionAvail().x - totalWidth) / 2.0f;
    
        SetCursorPosX(startX);
        if (Button("Import Inventory", ImVec2(buttonWidth, 0))) {
            OpenPopup("ImportPopup");
        }
    
        SameLine();
        if (Button("Export Inventory", ImVec2(buttonWidth, 0))) {
            OpenPopup("ExportPopup");
        }
    
        // --- Import Popup ---
        if (BeginPopup("ImportPopup")) {
            static char filename[128] = "new_inventory.txt";
            static std::string importMessage;
    
            InputText("Filename", filename, IM_ARRAYSIZE(filename));
    
            if (Button("Import")) {
                importInventoryFromFile(filename, importMessage);
                inventory.clear();
                loadInventoryFromFile(inventory);
            }
    
            if (!importMessage.empty()) {
                TextWrapped("%s", importMessage.c_str());
            }
    
            if (Button("Close")) {
                importMessage.clear();
                CloseCurrentPopup();
            }
    
            EndPopup();
        }
    
        // --- Export Popup ---
        if (BeginPopup("ExportPopup")) {
            Text("Export Inventory - Coming Soon");
            if (Button("Close")) CloseCurrentPopup();
            EndPopup();
        }
    }

    EndChild();
}

