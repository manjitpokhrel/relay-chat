#ifndef CHATWINDOW_H
#define CHATWINDOW_H

#include <QMainWindow>
#include <QListWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QSplitter>
#include <QTimer>
#include <QLabel>
#include <QMessageBox>
#include <QScrollBar>

class AppController;

class ChatWindow : public QMainWindow {
    Q_OBJECT

private:
    AppController* controller;

    QListWidget* roomList;
    QTextEdit* messageDisplay;
    QLineEdit* messageInput;
    QPushButton* sendButton;
    QPushButton* createRoomButton;
    QPushButton* clearChatButton;
    QLabel* currentRoomLabel;
    QLabel* currentUserLabel;
    QTimer* refreshTimer;

    void setupUI();
    void loadRooms();
    void loadMessages();

private slots:
    void onRoomSelected(QListWidgetItem* item);
    void onSendClicked();
    void onCreateRoomClicked();
    void onClearChatClicked();
    void onTimerTick();

public:
    ChatWindow(AppController* controller,
               QWidget* parent = nullptr);
};

#endif