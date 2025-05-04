#include "login_ui.h"
#include "imgui.h"
#include <cstring>
#include "account_ui.h"

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
    static char username_buf[64] = "";
    static char password_buf[64] = "";
    static bool open_guest_popup = false;
    username = username_buf;
    password = password_buf;
    ImGui::Begin("Login", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize);

    ImGui::Text("Please log in:");
    ImGui::InputText("Username", username_buf, IM_ARRAYSIZE(username_buf));
    ImGui::InputText("Password", password_buf, IM_ARRAYSIZE(password_buf), ImGuiInputTextFlags_Password);
    
    if (ImGui::Button("Login")) {
        string privilege;
        if (validate_credentials(username, password, privilege)) {
            currentUser.setUsername(username);
            currentUser.setPrivilege(privilege);
            loggedIn = true;
        } else {
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid credentials. Try again or continue as guest.");
        }
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
