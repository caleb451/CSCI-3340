#include "login_ui.h"
#include "imgui.h"
#include <cstring>
#include "include/account.h"

// Temporary login logic — replace with real validation as needed
bool validate_credentials(const std::string& username, const std::string& password, std::string& privilege) {
    if (username == "manager" && password == "admin123") {
        privilege = "manager";
        return true;
    }
    if (username == "worker" && password == "work123") {
        privilege = "worker";
        return true;
    }
    return false;
}

void ShowLoginUI(bool& loggedIn, std::string& username, std::string& privilege) {
    static char inputUsername[128] = "";
    static char inputPassword[128] = "";
    static bool loginFailed = false;

    ImGui::Begin("Login", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::InputText("Username", inputUsername, IM_ARRAYSIZE(inputUsername));
    ImGui::InputText("Password", inputPassword, IM_ARRAYSIZE(inputPassword), ImGuiInputTextFlags_Password);

    if (ImGui::Button("Login")) {
        std::string user(inputUsername);
        std::string pass(inputPassword);
        if (validate_credentials(user, pass, privilege)) {
            username = user;
            loggedIn = true;
            loginFailed = false;
        } else {
            loginFailed = true;
        }
    }

    if (loginFailed) {
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid credentials.");
    }

    ImGui::End();
}
