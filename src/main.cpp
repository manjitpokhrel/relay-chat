#include <QApplication>
#include "AppController.h"
#include "LocalDataService.h"
#include "LoginWindow.h"
#include "ChatWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setStyle("Fusion");

    return app.exec();
}