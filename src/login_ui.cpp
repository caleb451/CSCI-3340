#include "login_ui.h"
#include "imgui.h"
#include <cstring>
#include "account_ui.h"
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

// string trim(const string& str) {
//     size_t start = str.find_first_not_of(" \t\r\n");
//     size_t end = str.find_last_not_of(" \t\r\n");
//     return (start == string::npos || end == string::npos) ? "" : str.substr(start, end - start + 1);
// }

string symbolToPrivilege(char symbol) {
    switch (symbol) {
        case '*': return "manager";
        case '+': return "worker";
        case '_': return "guest";
        case '-': return "guest"; // or "customer" if needed
        default: return "guest";
    }
}

bool validate_credentials(const string& username, const string& password, string& privilege, account& currentUser) {
    ifstream file("accountInformation.txt");
    if (!file.is_open()) return false;

    string line;
    while (getline(file, line)) {
        if (line.length() < 2) continue;  // skip invalid lines

        char typeSymbol = line[0]; // First character
        string accountLine = line.substr(1); // Rest of the line

        istringstream ss(accountLine);
        string u, p, fname, lname, phone;

        ss >> u >> p >> fname >> lname >> phone;

        u = trim(u);
        p = trim(p);

        if (trim(u) == trim(username) && trim(p) == trim(password)) {
            string fullName = fname + " " + lname;
            privilege = symbolToPrivilege(typeSymbol);

            currentUser.setUsername(u);
            currentUser.setPassword(p);
            currentUser.setName(fullName);
            currentUser.setPhone(phone);
            currentUser.setPrivilege(privilege);

            return true;
        }
    }

    return false;
}

void ShowLoginUI(string& username, string& password, bool& loggedIn, account& currentUser) {
    static char username_buf[64] = "";
    static char password_buf[64] = "";
    static bool open_guest_popup = false;
    static bool showError = false;
    username = username_buf;
    password = password_buf;

    ImGui::Begin("Login", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Please log in:");
    ImGui::InputText("Username", username_buf, IM_ARRAYSIZE(username_buf));
    ImGui::InputText("Password", password_buf, IM_ARRAYSIZE(password_buf), ImGuiInputTextFlags_Password);
    
    if (ImGui::Button("Login")) {
        string privilege;
        if (validate_credentials(username, password, privilege, currentUser)) {
            showError = false;
            loggedIn = true;
        } else {
            showError = true;
        }
    }
    if (showError) {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid username or password.");
    }
    

    ImGui::Separator();

    if (ImGui::Button("Continue as Guest")) {
        open_guest_popup = true;
        ImGui::OpenPopup("Guest Confirmation");
    }

    // Guest confirmation popup
    if (ImGui::BeginPopupModal("Guest Confirmation", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
        ImGui::Text("Are you sure you want to continue as guest?\n\n");
        ImGui::Separator();

        if (ImGui::Button("Yes", ImVec2(120, 0))) {
            currentUser.setUsername("guest");
            currentUser.setPrivilege("guest");
            loggedIn = true;
            ImGui::CloseCurrentPopup();
            open_guest_popup = false;
        }

        ImGui::SameLine();

        if (ImGui::Button("No", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
            open_guest_popup = false;
        }

        ImGui::EndPopup();
    }

    ImGui::End();
}
