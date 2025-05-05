#include "inventory_ui.h"
#include "imgui.h"
#include <fstream>
#include <sstream>
#include "account_ui.h"
#include <filesystem>

using namespace std;
using namespace ImGui;

void exportInventoryToFile(const vector<vector<string>>& data, const string& filename) {
    ofstream outFile(filename);
    if (!outFile.is_open()) {
        cerr << "Failed to open export file.\n";
        return;
    }

    // Write header row
    outFile << "Name,ID,Price,Stock,Department,Aisle\n";

    // Write each row
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            outFile << row[i];
            if (i != row.size() - 1)
                outFile << ",";
        }
        outFile << "\n";
    }

    outFile.close();
}

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
    static char editID[16] = "";
    static char newStock[16] = "";
    static char idToRemove[16] = "";
    static bool openEditPopup = false;
    static bool openRemovePopup = false;    

    if (!loaded) {
        loadInventoryFromFile(inventory);
        loaded = true;
    }

    if (inventory.empty()) {
        Text("No inventory data found.");
    }

    if ((currentUser.getPrivilege() == "manager") || (currentUser.getPrivilege() == "worker")) {
        if (BeginTable("InventoryTable", 7, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg)) {
            TableSetupColumn("Name");
            TableSetupColumn("ID");
            TableSetupColumn("Price");
            TableSetupColumn("Stock");
            TableSetupColumn("Department");
            TableSetupColumn("Aisle");
            TableSetupColumn("Actions");
            TableHeadersRow();
    
            for (const auto& row : inventory) {
                if (row.size() < 6) continue;
                TableNextRow();
    
                for (int col = 0; col < 6; ++col) {
                    TableSetColumnIndex(col);
                    Text("%s", row[col].c_str());
                }
    
                TableSetColumnIndex(6);
                string popupId = "Actions##" + row[1];
                if (SmallButton(("...##" + row[1]).c_str())) {
                    OpenPopup(popupId.c_str());
                }

                if (BeginPopup(popupId.c_str())) {
                    if (Selectable("Edit")) {
                        strcpy(editID, row[1].c_str());
                        strcpy(newStock, row[3].c_str());
                        openEditPopup = true;  // defer actual popup
                    }
                    if (currentUser.getPrivilege() == "manager"){
                        if (Selectable("Remove")) {
                            strcpy(idToRemove, row[1].c_str());
                            //OpenPopup("ConfirmRemovePopup");
                            openRemovePopup = true;
                        }
                    }
                    EndPopup();
                }
            }
    
            EndTable();

            if (openEditPopup) {
                OpenPopup("EditPopup");
                openEditPopup = false;
            }
            if (openRemovePopup) {
                OpenPopup("RemovePopup");
                openRemovePopup = false;
            }
        }
    }
    else {
        // For guests or others without "Actions" column
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
        float buttonWidth = 120.0f;
        float spacing = 10.0f;
        float totalWidth = (buttonWidth * 3) + (spacing * 2);
        float startX = (GetContentRegionAvail().x - totalWidth) / 2.0f;
        SetCursorPosX(startX);

        
        if (Button("Import", ImVec2(buttonWidth, 0))) {
            OpenPopup("ImportPopup");
        }

        SameLine(0.0f, spacing);
        if (Button("Export", ImVec2(buttonWidth, 0))) {
            OpenPopup("ExportPopup");
        }

        SameLine(0.0f, spacing);
        if (Button("Add", ImVec2(buttonWidth, 0))) {
            OpenPopup("AddPopup");
        }

        // SameLine(0.0f, spacing);
        // if (Button("Remove", ImVec2(buttonWidth, 0))) {
        //     OpenPopup("RemovePopup");
        // }
    
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
            static std::string exportMessage;
        
            if (Button("Export Now")) {
                exportInventoryToFile(inventory, "inventory_export.txt");
                exportMessage = "Exported to inventory_export.txt";
            }
        
            if (!exportMessage.empty()) {
                TextWrapped("%s", exportMessage.c_str());
            }
        
            if (Button("Close")) {
                exportMessage.clear();
                CloseCurrentPopup();
            }
        
            EndPopup();
        }
        
        if (BeginPopup("AddPopup")) {
            static char name[64] = "";
            static char id[16] = "";
            static char price[16] = "";
            static char stock[16] = "";
            static char department[64] = "";
            static char aisle[16] = "";
            static std::string addMessage;
        
            InputText("Name", name, IM_ARRAYSIZE(name));
            InputText("ID", id, IM_ARRAYSIZE(id));
            InputText("Price", price, IM_ARRAYSIZE(price));
            InputText("Stock", stock, IM_ARRAYSIZE(stock));
            InputText("Department", department, IM_ARRAYSIZE(department));
            InputText("Aisle", aisle, IM_ARRAYSIZE(aisle));
        
            if (Button("Submit")) {
                ofstream file("inventory.txt", ios::app); // append to inventory
                if (file) {
                    file << name << ","
                         << id << ","
                         << price << ","
                         << stock << ","
                         << department << ","
                         << aisle << "\n";
                    file.close();
                    addMessage = "Item added successfully.";
                    inventory.clear();
                    loadInventoryFromFile(inventory); // refresh inventory
                    loaded = true;
                } else {
                    addMessage = "Error: Could not open inventory file.";
                }
            }
        
            if (!addMessage.empty()) {
                TextWrapped("%s", addMessage.c_str());
            }
        
            if (Button("Close")) {
                name[0] = id[0] = price[0] = stock[0] = department[0] = aisle[0] = '\0';
                addMessage.clear();
                CloseCurrentPopup();
            }
        
            EndPopup();
        }

        if (BeginPopup("RemovePopup")) {
            static std::string removeMessage;
            static bool confirmRemove = false;
        
            if (!confirmRemove) {
                Text("Are you sure you want to remove item with ID: %s?", idToRemove);
                if (Button("Yes")) {
                    ifstream inFile("inventory.txt");
                    ofstream outFile("temp.txt");
                    bool removed = false;
        
                    string line;
                    while (getline(inFile, line)) {
                        stringstream ss(line);
                        vector<string> fields;
                        string field;
        
                        while (getline(ss, field, ',')) {
                            fields.push_back(field);
                        }
        
                        // Make sure ID matches
                        if (fields.size() < 2 || fields[1] != idToRemove) {
                            outFile << line << "\n";
                        } else {
                            removed = true;
                        }
                    }
        
                    inFile.close();
                    outFile.close();
                    remove("inventory.txt");
                    rename("temp.txt", "inventory.txt");
        
                    removeMessage = removed ? "Item removed successfully." : "Item ID not found.";
                    inventory.clear();
                    loadInventoryFromFile(inventory);
                    loaded = true;
        
                    idToRemove[0] = '\0';
                    confirmRemove = false;
                    CloseCurrentPopup();
                }
                SameLine();
                if (Button("Cancel")) {
                    idToRemove[0] = '\0';
                    confirmRemove = false;
                    CloseCurrentPopup();
                }
            }
        
            if (!removeMessage.empty()) {
                TextWrapped("%s", removeMessage.c_str());
            }
        
            EndPopup();
        }

        if (BeginPopupModal("ConfirmRemovePopup", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            Text("Are you sure you want to remove item with ID: %s?", idToRemove);
            static std::string removeMessage;
        
            if (Button("Yes")) {
                ifstream inFile("inventory.txt");
                ofstream outFile("temp.txt");
                bool removed = false;
            
                string line;
                while (getline(inFile, line)) {
                    stringstream ss(line);
                    vector<string> fields;
                    string field;
            
                    while (getline(ss, field, ',')) {
                        fields.push_back(field);
                    }
            
                    if (fields.size() < 2 || fields[1] != idToRemove) {
                        outFile << line << "\n";
                    } else {
                        removed = true;
                    }
                }
            
                inFile.close();
                outFile.close();
                remove("inventory.txt");
                rename("temp.txt", "inventory.txt");
            
                removeMessage = removed ? "Item removed." : "Item not found.";
                inventory.clear();
                loadInventoryFromFile(inventory);
                loaded = true;
                idToRemove[0] = '\0';
                CloseCurrentPopup();
            }
        
            SameLine();
            if (Button("No")) {
                idToRemove[0] = '\0';
                CloseCurrentPopup();
            }
        
            EndPopup();
        }
        
    }
    if (BeginPopup("EditPopup")) {
        static char name[64] = "";
        static char id[16] = "";
        static char price[16] = "";
        static char stock[16] = "";
        static char department[64] = "";
        static char aisle[16] = "";
        static string editMessage;
    
        // Pre-fill fields with current item data
        for (const auto& row : inventory) {
            if (row.size() >= 6 && row[1] == editID) {
                strcpy(name, row[0].c_str());
                strcpy(id, row[1].c_str());
                strcpy(price, row[2].c_str());
                strcpy(stock, row[3].c_str());
                strcpy(department, row[4].c_str());
                strcpy(aisle, row[5].c_str());
                break;
            }
        }
    
        InputText("Name", name, IM_ARRAYSIZE(name));
        InputText("ID", id, IM_ARRAYSIZE(id));
        InputText("Price", price, IM_ARRAYSIZE(price));
        InputText("Stock", stock, IM_ARRAYSIZE(stock));
        InputText("Department", department, IM_ARRAYSIZE(department));
        InputText("Aisle", aisle, IM_ARRAYSIZE(aisle));
    
        if (Button("Update")) {
            ifstream inFile("inventory.txt");
            ofstream outFile("temp.txt");
            bool updated = false;
    
            string line;
            while (getline(inFile, line)) {
                stringstream ss(line);
                vector<string> fields;
                string field;
    
                while (getline(ss, field, ',')) {
                    fields.push_back(field);
                }
    
                if (fields.size() == 6 && fields[1] == editID) {
                    fields[0] = name;
                    fields[1] = id;
                    fields[2] = price;
                    fields[3] = stock;
                    fields[4] = department;
                    fields[5] = aisle;
                    updated = true;
                }
    
                outFile << fields[0];
                for (int i = 1; i < 6; ++i)
                    outFile << "," << fields[i];
                outFile << "\n";
            }
    
            inFile.close();
            outFile.close();
            remove("inventory.txt");
            rename("temp.txt", "inventory.txt");
    
            editMessage = updated ? "Item updated successfully." : "Item ID not found.";
            inventory.clear();
            loadInventoryFromFile(inventory);
            loaded = true;
        }
    
        if (!editMessage.empty()) {
            TextWrapped("%s", editMessage.c_str());
        }
    
        if (Button("Close")) {
            name[0] = id[0] = price[0] = stock[0] = department[0] = aisle[0] = '\0';
            editMessage.clear();
            CloseCurrentPopup();
        }
    
        EndPopup();
    }

    EndChild();
}

