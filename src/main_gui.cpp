#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "login_ui.h"
#include "account_ui.h"
#include "inventory_ui.h"
#include <fstream>

using namespace std;
using namespace ImGui;

bool loggedIn = false;
string user, pass;
account currentUser;
bool viewingInventory = false;
static bool openCreateAccountPopup = false;

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
                    openCreateAccountPopup = true;
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

            if (BeginPopupModal("CreateAccountPopup", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {

                static char fname[64] = "";
                static char lname[64] = "";
                static char username[64] = "";
                static char password[64] = "";
                static char phone[32] = "";
                static int privilegeIndex = 1; // 0=manager, 1=worker, 2=guest, 3=customer
                static std::string createMessage;
            
                const char* privileges[] = { "manager", "worker", "guest", "customer" };
                const char symbols[]     = { '*',        '+',      '_',     '-'        };
            
                InputText("First Name", fname, IM_ARRAYSIZE(fname));
                InputText("Last Name", lname, IM_ARRAYSIZE(lname));
                InputText("Username", username, IM_ARRAYSIZE(username));
                InputText("Password", password, IM_ARRAYSIZE(password));
                InputText("Phone", phone, IM_ARRAYSIZE(phone));
                Combo("Privilege", &privilegeIndex, privileges, IM_ARRAYSIZE(privileges));
            
                if (Button("Create Account")) {
                    ofstream file("accountInformation.txt", ios::app);
                    if (file) {
                        file << symbols[privilegeIndex] << " "
                             << username << " "
                             << password << " "
                             << fname << " "
                             << lname << " "
                             << phone << "\n";
                        file.close();
                        createMessage = "Account created!";
                    } else {
                        createMessage = "Error: Could not write to file.";
                    }
                }
            
                if (!createMessage.empty()) {
                    TextWrapped("%s", createMessage.c_str());
                }
            
                if (Button("Close")) {
                    fname[0] = lname[0] = username[0] = password[0] = phone[0] = '\0';
                    privilegeIndex = 1;
                    createMessage.clear();
                    CloseCurrentPopup();
                }
            
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

        if (openCreateAccountPopup) {
            OpenPopup("CreateAccountPopup");
            openCreateAccountPopup = false;
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
