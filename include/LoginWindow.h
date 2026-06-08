#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>

class AppController;

class LoginWindow : public QWidget {
    Q_OBJECT

private:
    AppController* controller;
    QLineEdit* usernameInput;
    QLineEdit* passwordInput;
    QPushButton* loginButton;
    QPushButton* registerButton;
    QLabel* statusLabel;

    void setupUI();

private slots:
    void onLoginClicked();
    void onRegisterClicked();

signals:
    void loginSuccessful();

public:
    LoginWindow(AppController* controller,
                QWidget* parent = nullptr);
};

#endif