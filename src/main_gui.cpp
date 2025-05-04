#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "login_ui.h"
#include "account_ui.h"

using namespace std;

bool loggedIn = false;
string user, pass;
account currentUser;

//test for alfredo

int main() {
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Inventory GUI", NULL, NULL);
    glfwMakeContextCurrent(window);
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glfwSwapInterval(1);

    // Initialize ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (!loggedIn) {
            ShowLoginUI(user, pass, loggedIn, currentUser);
        } 
        else {
            ImGui::Begin("Inventory System", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

            ImGui::SeparatorText("------------------------ [STORE NAME] ------------------------");
            ImGui::Text("Logged In As: %s", currentUser.getPrivilege().c_str());
            ImGui::Spacing();
            
            if (currentUser.getPrivilege() == "manager") {
                ImGui::Text("Welcome %s", currentUser.getName().c_str());
                if (ImGui::Button("1. Logout")) {
                    loggedIn = false;
                    user.clear();
                    pass.clear();
                    currentUser = account(); // Reset
                }

                if (ImGui::Button("2. View Inventory")) {
                    ImGui::OpenPopup("InventoryPopup");
                }

                if (ImGui::Button("3. Create New Account")) {
                    ImGui::OpenPopup("CreateAccountPopup");
                }

                if (ImGui::Button("4. Import Inventory")) {
                    ImGui::OpenPopup("ImportPopup");
                }

                if (ImGui::Button("5. Export Inventory")) {
                    ImGui::OpenPopup("ExportPopup");
                }
            }
            else{
                if (ImGui::Button("1. Login")) {
                    loggedIn = false;
                    user.clear();
                    pass.clear();
                    currentUser = account();
                }

                if (ImGui::Button("2. View Inventory")) {
                    ImGui::OpenPopup("InventoryPopup");
                }
            }
                ImGui::End();

                // Popups (placeholder for now)
                if (ImGui::BeginPopup("InventoryPopup")) {
                    ImGui::Text("View Inventory - Coming Soon");
                    ImGui::EndPopup();
                }

                if (ImGui::BeginPopup("CreateAccountPopup")) {
                    ImGui::Text("Create Account - Coming Soon");
                    ImGui::EndPopup();
                }

                if (ImGui::BeginPopup("ImportPopup")) {
                    ImGui::Text("Import Inventory - Coming Soon");
                    ImGui::EndPopup();
                }

                if (ImGui::BeginPopup("ExportPopup")) {
                    ImGui::Text("Export Inventory - Coming Soon");
                    ImGui::EndPopup();
                }
        }

        // Render everything
        ImGui::Render();
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
