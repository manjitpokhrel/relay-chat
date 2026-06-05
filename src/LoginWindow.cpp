#include "LoginWindow.h"
#include "AppController.h"
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

LoginWindow::LoginWindow(AppController* ctrl, QWidget* parent)
    : QWidget(parent), controller(ctrl) {
    setupUI();
}

void LoginWindow::setupUI() {
    setWindowTitle("Relay — Login");

    // Outer layout that fills entire widget
    auto* outerLayout = new QVBoxLayout(this);
    outerLayout->setAlignment(Qt::AlignCenter);

    // Container for login form
    auto* container = new QWidget(this);
    container->setFixedSize(350, 300);
    container->setStyleSheet(
        "QWidget {"
        "  background-color: #2C2F33;"
        "  border-radius: 8px;"
        "}"
    );

    auto* layout = new QVBoxLayout(container);
    layout->setSpacing(12);
    layout->setContentsMargins(30, 30, 30, 30);

    auto* titleLabel = new QLabel("Relay", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet(
        "font-size: 28px; font-weight: bold; "
        "color: #5865F2; background: transparent;"
    );

    auto* subtitleLabel = new QLabel(
        "Welcome back!", this);
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setStyleSheet(
        "font-size: 13px; color: #72767D; "
        "background: transparent;"
    );

    usernameInput = new QLineEdit(this);
    usernameInput->setPlaceholderText("Username");
    usernameInput->setStyleSheet(
        "QLineEdit {"
        "  padding: 10px;"
        "  border-radius: 4px;"
        "  border: none;"
        "  background-color: #40444B;"
        "  color: white;"
        "  font-size: 14px;"
        "}"
    );

    passwordInput = new QLineEdit(this);
    passwordInput->setPlaceholderText("Password");
    passwordInput->setEchoMode(QLineEdit::Password);
    passwordInput->setStyleSheet(
        "QLineEdit {"
        "  padding: 10px;"
        "  border-radius: 4px;"
        "  border: none;"
        "  background-color: #40444B;"
        "  color: white;"
        "  font-size: 14px;"
        "}"
    );

    loginButton = new QPushButton("Login", this);
    loginButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #5865F2;"
        "  color: white;"
        "  padding: 10px;"
        "  border-radius: 4px;"
        "  font-weight: bold;"
        "  font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #4752C4;"
        "}"
    );

    registerButton = new QPushButton("Register", this);
    registerButton->setStyleSheet(
        "QPushButton {"
        "  background-color: transparent;"
        "  color: #5865F2;"
        "  padding: 8px;"
        "  border-radius: 4px;"
        "  font-size: 13px;"
        "}"
        "QPushButton:hover {"
        "  text-decoration: underline;"
        "}"
    );

    statusLabel = new QLabel("", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet(
        "color: #ED4245; background: transparent; "
        "font-size: 12px;"
    );

    layout->addWidget(titleLabel);
    layout->addWidget(subtitleLabel);
    layout->addWidget(usernameInput);
    layout->addWidget(passwordInput);
    layout->addWidget(loginButton);
    layout->addWidget(registerButton);
    layout->addWidget(statusLabel);

    outerLayout->addWidget(container);

    connect(loginButton, &QPushButton::clicked,
            this, &LoginWindow::onLoginClicked);
    connect(registerButton, &QPushButton::clicked,
            this, &LoginWindow::onRegisterClicked);
    connect(passwordInput, &QLineEdit::returnPressed,
            this, &LoginWindow::onLoginClicked);
}

void LoginWindow::onLoginClicked() {
    std::string username =
        usernameInput->text().toStdString();
    std::string password =
        passwordInput->text().toStdString();

    if (controller->login(username, password)) {
        emit loginSuccessful();
    } else {
        statusLabel->setText(
            "Invalid username or password.");
    }
}

void LoginWindow::onRegisterClicked() {
    std::string username =
        usernameInput->text().toStdString();
    std::string password =
        passwordInput->text().toStdString();

    if (username.empty() || password.empty()) {
        statusLabel->setText(
            "Username and password required.");
        return;
    }

    if (controller->registerUser(username, password)) {
        statusLabel->setStyleSheet(
            "color: #57F287; background: transparent; "
            "font-size: 12px;"
        );
        statusLabel->setText(
            "Registered! Please login.");
    } else {
        statusLabel->setText(
            "Username already exists.");
    }
}