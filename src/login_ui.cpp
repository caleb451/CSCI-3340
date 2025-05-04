#include "login_ui.h"
#include "imgui.h"
#include <cstring>
#include "account.h"

using namespace std;

// Temporary login logic — replace with real validation as needed
bool validate_credentials(const string& username, const string& password, string& privilege) {
    if (username == "manager" && password == "admin123") {
        privilege = "manager";
        return true;
    }
    if (username == "worker" && password == "worker123") {
        privilege = "worker";
        return true;
    }
    return false;
}

void ShowLoginUI(string& username, string& password, bool& loggedIn, account& currentUser) {
    ImGui::Begin("Login", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);

    static char userBuffer[128] = "";
    static char passBuffer[128] = "";
    static string loginError = "";

    ImGui::InputText("Username", userBuffer, IM_ARRAYSIZE(userBuffer));
    ImGui::InputText("Password", passBuffer, IM_ARRAYSIZE(passBuffer), ImGuiInputTextFlags_Password);

    if (ImGui::Button("Login")) {
        username = string(userBuffer);
        password = string(passBuffer);
        string privilege;

        if (validate_credentials(username, password, privilege)) {
            currentUser.setUsername(username);
            currentUser.setPassword(password);
            currentUser.setName(privilege == "manager" ? "Manager User" : "Worker User");
            currentUser.setPrivilege(privilege);
            loggedIn = true;
            loginError.clear();
        } 
        else {
            currentUser.setUsername("guest");
            currentUser.setPrivilege("guest");
            loggedIn = true;
            loginError = "Invalid credentials. Proceeding as guest.";
        }
    }

    if (!loginError.empty()) {
        ImGui::TextColored(ImVec4(1, 0.3f, 0.3f, 1), "%s", loginError.c_str());
    }

    ImGui::End();
}
