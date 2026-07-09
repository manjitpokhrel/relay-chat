#include <QApplication>
#include "AppController.h"
<<<<<<< HEAD
=======
#include "LocalDataService.h"
// #include "RemoteDataService.h"
>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
#include "LoginWindow.h"
#include "ChatWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
<<<<<<< HEAD

    app.setStyle("Fusion");

    // Dark palette
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(54, 57, 63));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(64, 68, 75));
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(88, 101, 242));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Highlight, QColor(88, 101, 242));
    app.setPalette(darkPalette);

    AppController controller;

=======
    app.setStyle("Fusion");

    QPalette darkPalette;
    darkPalette.setColor(
        QPalette::Window, QColor(54, 57, 63));
    darkPalette.setColor(
        QPalette::WindowText, Qt::white);
    darkPalette.setColor(
        QPalette::Base, QColor(64, 68, 75));
    darkPalette.setColor(
        QPalette::Text, Qt::white);
    darkPalette.setColor(
        QPalette::Button, QColor(88, 101, 242));
    darkPalette.setColor(
        QPalette::ButtonText, Qt::white);
    darkPalette.setColor(
        QPalette::Highlight, QColor(88, 101, 242));
    app.setPalette(darkPalette);

    // ─────────────────────────────────────────────────
    // SWITCH SERVICE HERE
    // Local  → SQLite on disk
    // Remote → AWS RDS via server
    // ─────────────────────────────────────────────────
    auto service = std::make_unique<LocalDataService>(
        "relay.db"
    );

    // auto service = std::make_unique<RemoteDataService>(
    //     "http://your-server-url"
    // );

    AppController controller(std::move(service));

    // Show login window first
>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
    auto* loginWindow = new LoginWindow(&controller);
    loginWindow->setWindowTitle("Relay — Login");
    loginWindow->setFixedSize(400, 350);
    loginWindow->show();

<<<<<<< HEAD
=======
    // When login succeeds, close login and open chat
>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
    QObject::connect(
        loginWindow,
        &LoginWindow::loginSuccessful,
        [&]() {
            loginWindow->close();
<<<<<<< HEAD

=======
>>>>>>> 70d55099947c2fb834270d18a27649e7a233efd5
            auto* chatWindow = new ChatWindow(&controller);
            chatWindow->setWindowTitle("Relay Chat");
            chatWindow->resize(1000, 700);
            chatWindow->show();
        }
    );

    return app.exec();
}