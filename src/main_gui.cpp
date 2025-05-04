#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "login_ui.h"
#include "account_ui.h"
#include "inventory_ui.h"

using namespace std;
using namespace ImGui;

bool loggedIn = false;
string user, pass;
account currentUser;
bool viewingInventory = false;

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
    CreateContext();
    ImGuiIO& io = GetIO(); (void)io;
    StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330");

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        NewFrame();

        if (!loggedIn) {
            ShowLoginUI(user, pass, loggedIn, currentUser);
        } 
        else {
            Begin("Inventory System", nullptr, ImGuiWindowFlags_AlwaysAutoResize);

            SeparatorText("------------------------ [STORE NAME] ------------------------");
            Text("Logged In As: %s", currentUser.getPrivilege().c_str());
            Spacing();

            if (currentUser.getPrivilege() == "manager") {
                Text("Welcome %s", currentUser.getName().c_str());
                if (Button("1. Logout")) {
                    loggedIn = false;
                    user.clear();
                    pass.clear();
                    currentUser = account();
                }

                if (Button("2. View Inventory")) {
                    viewingInventory = true;
                }

                if (Button("3. Create New Account")) {
                    OpenPopup("CreateAccountPopup");
                }
            }
            else {
                if (Button("1. Login")) {
                    loggedIn = false;
                    user.clear();
                    pass.clear();
                    currentUser = account();
                }

                if (Button("2. View Inventory")) {
                    viewingInventory = true;
                }
            }

            End();

            if (BeginPopup("CreateAccountPopup")) {
                Text("Create Account - Coming Soon");
                if (Button("Close")) CloseCurrentPopup();
                EndPopup();
            }

            if (BeginPopup("ImportPopup")) {
                if (currentUser.getPrivilege() == "manager") {
                    static char filename[128] = "new_inventory.txt";
                    static string importMessage;

                    InputText("Filename", filename, IM_ARRAYSIZE(filename));

                    if (Button("Import")) {
                        importInventoryFromFile(filename, importMessage);
                    }

                    if (!importMessage.empty()) {
                        TextWrapped("%s", importMessage.c_str());
                    }

                    if (Button("Close")) {
                        importMessage.clear();
                        CloseCurrentPopup();
                    }
                } else {
                    Text("Access denied: Only managers can import inventory.");
                    if (Button("Close")) CloseCurrentPopup();
                }
                EndPopup();
            }

            if (BeginPopup("ExportPopup")) {
                Text("Export Inventory - Coming Soon");
                if (Button("Close")) CloseCurrentPopup();
                EndPopup();
            }
        }


        if (viewingInventory) {
            OpenPopup("InventoryPopup");
            viewingInventory = false;
        }

        if (BeginPopupModal("InventoryPopup", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
            ShowInventoryUI(currentUser, viewingInventory);
            EndPopup();
        }

        // Render everything
        Render();
        int w, h;
        glfwGetFramebufferSize(window, &w, &h);
        glViewport(0, 0, w, h);
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(GetDrawData());
        glfwSwapBuffers(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}
