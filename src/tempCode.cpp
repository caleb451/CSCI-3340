//This is the deafult code for the qt creator

// #include "include/mainwindow.h"
// #include "include/ui_mainwindow.h"
// #include "include/account.h"
// #include "include/addAcc.h"

// MainWindow::MainWindow(QWidget *parent)
//     : QMainWindow(parent)
//     , ui(new Ui::MainWindow)
// {
//     ui->setupUi(this);

//     connect(ui->organicButton, &QPushButton::clicked, this, [=]() {
//         ui->stackedWidget->setCurrentWidget(ui->organicPage);
//     });

//     connect(ui->vegetablesButton, &QPushButton::clicked, this, [=]() {
//         ui->stackedWidget->setCurrentWidget(ui->vegetablesPage);
//     });

//     ui->welcomeLabel->setStyleSheet("QLabel { color: #2d3748; font-size: 28px; font-weight: bold; }");

//     ui->label->setAlignment(Qt::AlignCenter);
//     ui->label->setStyleSheet("QLabel { color: #2d3748; font-size: 28px; font-weight: bold; }");

//     connect(ui->loginButton, &QPushButton::clicked, this, &MainWindow::handleLogin);
//     this->setStyleSheet("background-color: #f3f4f6;");

//     connect(ui->logoutButton, &QPushButton::clicked, this, [=]() {
//         ui->stackedWidget->setCurrentWidget(ui->loginPage);  // Go back to login page
//         ui->usernameLineEdit->clear();  // Optional: clear username field
//         ui->passwordLineEdit->clear();  // Optional: clear password field
//         ui->statusLabel->clear();       // Optional: clear login status
//     });

//     ui->usernameLineEdit->setPlaceholderText("Email or Username");
//     ui->passwordLineEdit->setPlaceholderText("Password");

//     ui->usernameLineEdit->setStyleSheet(
//         "QLineEdit {"
//         "padding: 10px;"
//         "border: 2px solid #ccc;"
//         "border-radius: 5px;"
//         "background-color: white;"
//         "color: black;"
//         "}"
//         "QLineEdit:placeholder { color: gray; }"
//         );

//     ui->passwordLineEdit->setStyleSheet(
//         "QLineEdit {"
//         "padding: 10px;"
//         "border: 2px solid #ccc;"
//         "border-radius: 5px;"
//         "background-color: white;"
//         "color: black;"
//         "}"
//         "QLineEdit:placeholder { color: gray; }"
//         );

//     ui->loginButton->setStyleSheet(
//         "QPushButton {"
//         "padding: 10px;"
//         "border-radius: 5px;"
//         "background-color: #5A67D8;"
//         "color: white;"
//         "font-weight: bold;"
//         "}"
//         "QPushButton:hover {"
//         "background-color: #434190;"
//         "}"
//         );

//     // Start on the login page
//     ui->stackedWidget->setCurrentWidget(ui->loginPage);
// }

// MainWindow::~MainWindow()
// {
//     delete ui;
// }

// void MainWindow::handleLogin()
// {
//     QString inputUser = ui->usernameLineEdit->text();
//     QString inputPass = ui->passwordLineEdit->text();

//     vector<account> accList = addAcc(); // Load all accounts from file
//     bool found = false;

//     for (account& acc : accList) {
//         if (acc.checkUser(inputUser.toStdString())) {
//             found = true;
//             if (acc.checkPassword(inputPass.toStdString())) {
//                 // ✅ Display welcome message on homepage
//                 ui->welcomeLabel->setText("Hello, " + QString::fromStdString(acc.name) + "!");

//                 // ✅ Switch to homepage
//                 ui->stackedWidget->setCurrentWidget(ui->homePage);
//             } else {
//                 acc.failedAtt();
//                 ui->statusLabel->setText("Wrong password!");
//             }
//             break;
//         }
//     }

//     if (!found) {
//         ui->statusLabel->setText("User not found.");
//     }
// }
