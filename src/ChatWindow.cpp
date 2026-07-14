#include <QScrollBar>
#include <QMessageBox>
#include "ChatWindow.h"
#include "AppController.h"
#include "CreateRoomDialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QListWidgetItem>
#include <QString>
#include <QSplitter>

ChatWindow::ChatWindow(AppController* ctrl, QWidget* parent)
    : QMainWindow(parent), controller(ctrl) {
    setupUI();

    refreshTimer = new QTimer(this);
    connect(refreshTimer, &QTimer::timeout,
            this, &ChatWindow::onTimerTick);
    refreshTimer->start(2000);

    loadRooms();
}

void ChatWindow::setupUI() {
    setWindowTitle("Relay Chat");
    setMinimumSize(800, 600);

    // ── Central Widget ──────────────────────
    auto* central = new QWidget(this);
    setCentralWidget(central);

    // Main layout fills the entire window
    auto* mainLayout = new QHBoxLayout(central);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // ── Left Panel ──────────────────────────
    auto* leftPanel = new QWidget(this);
    leftPanel->setMinimumWidth(200);
    leftPanel->setMaximumWidth(250);
    leftPanel->setStyleSheet("background-color: #2C2F33;");

    auto* leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(5, 5, 5, 5);
    leftLayout->setSpacing(5);

    // User label
    currentUserLabel = new QLabel("", this);
    currentUserLabel->setStyleSheet(
        "color: #5865F2; font-weight: bold; "
        "font-size: 14px; padding: 10px;"
    );

    if (controller->getCurrentUser()) {
        currentUserLabel->setText(
            QString::fromStdString(
                "👤 " + controller->getCurrentUser()->getUsername()
            )
        );
    }

    // Rooms header
    auto* roomsLabel = new QLabel("CHANNELS", this);
    roomsLabel->setStyleSheet(
        "color: #72767D; font-size: 11px; "
        "font-weight: bold; padding: 5px;"
    );

    // Room list
    roomList = new QListWidget(this);
    roomList->setStyleSheet(
        "QListWidget {"
        "  background-color: #2C2F33;"
        "  color: #DCDDDE;"
        "  border: none;"
        "  font-size: 14px;"
        "}"
        "QListWidget::item {"
        "  padding: 8px;"
        "  border-radius: 4px;"
        "  margin: 2px 5px;"
        "}"
        "QListWidget::item:selected {"
        "  background-color: #393C43;"
        "  color: white;"
        "}"
        "QListWidget::item:hover {"
        "  background-color: #34373C;"
        "}"
    );

    // Create room button
    createRoomButton = new QPushButton("+ Create Room", this);
    createRoomButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #5865F2;"
        "  color: white;"
        "  padding: 8px;"
        "  border-radius: 4px;"
        "  font-weight: bold;"
        "  margin: 5px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #4752C4;"
        "}"
    );

    leftLayout->addWidget(currentUserLabel);
    leftLayout->addWidget(roomsLabel);
    leftLayout->addWidget(roomList, 1);
    leftLayout->addWidget(createRoomButton);

    // ── Right Panel ─────────────────────────
    auto* rightPanel = new QWidget(this);
    rightPanel->setStyleSheet("background-color: #36393F;");

    auto* rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setContentsMargins(0, 0, 0, 0);
    rightLayout->setSpacing(0);

    // Header bar
    auto* headerBar = new QWidget(this);
    headerBar->setStyleSheet(
        "background-color: #36393F; "
        "border-bottom: 1px solid #202225;"
    );
    headerBar->setFixedHeight(50);

    auto* headerLayout = new QHBoxLayout(headerBar);
    headerLayout->setContentsMargins(15, 0, 15, 0);

    currentRoomLabel = new QLabel("Select a room", this);
    currentRoomLabel->setStyleSheet(
        "font-weight: bold; font-size: 16px; "
        "color: white;"
    );

    clearChatButton = new QPushButton("Clear Chat", this);
    clearChatButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #ED4245;"
        "  color: white;"
        "  padding: 6px 12px;"
        "  border-radius: 4px;"
        "  font-size: 12px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #C03537;"
        "}"
    );

    headerLayout->addWidget(currentRoomLabel);
    headerLayout->addStretch();
    headerLayout->addWidget(clearChatButton);

    // Message display
    messageDisplay = new QTextEdit(this);
    messageDisplay->setReadOnly(true);
    messageDisplay->setStyleSheet(
        "QTextEdit {"
        "  background-color: #36393F;"
        "  color: #DCDDDE;"
        "  border: none;"
        "  padding: 15px;"
        "  font-size: 14px;"
        "}"
    );

    // Input bar
    auto* inputBar = new QWidget(this);
    inputBar->setFixedHeight(60);
    inputBar->setStyleSheet("background-color: #36393F;");

    auto* inputLayout = new QHBoxLayout(inputBar);
    inputLayout->setContentsMargins(15, 5, 15, 15);
    inputLayout->setSpacing(10);

    messageInput = new QLineEdit(this);
    messageInput->setPlaceholderText("Type a message...");
    messageInput->setStyleSheet(
        "QLineEdit {"
        "  padding: 10px 15px;"
        "  border-radius: 8px;"
        "  background-color: #40444B;"
        "  color: #DCDDDE;"
        "  border: none;"
        "  font-size: 14px;"
        "}"
        "QLineEdit:focus {"
        "  background-color: #474B52;"
        "}"
    );

    sendButton = new QPushButton("Send", this);
    sendButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #5865F2;"
        "  color: white;"
        "  padding: 10px 20px;"
        "  border-radius: 8px;"
        "  font-weight: bold;"
        "  font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "  background-color: #4752C4;"
        "}"
    );

    inputLayout->addWidget(messageInput, 1);
    inputLayout->addWidget(sendButton);

    // Add to right layout
    rightLayout->addWidget(headerBar);
    rightLayout->addWidget(messageDisplay, 1);
    rightLayout->addWidget(inputBar);

    // ── Splitter ────────────────────────────
    auto* splitter = new QSplitter(Qt::Horizontal, this);
    splitter->addWidget(leftPanel);
    splitter->addWidget(rightPanel);
    splitter->setStretchFactor(0, 0);
    splitter->setStretchFactor(1, 1);
    splitter->setHandleWidth(1);
    splitter->setStyleSheet(
        "QSplitter::handle { background-color: #202225; }"
    );

    mainLayout->addWidget(splitter);

    // ── Connections ─────────────────────────
    connect(roomList, &QListWidget::itemClicked,
            this, &ChatWindow::onRoomSelected);
    connect(sendButton, &QPushButton::clicked,
            this, &ChatWindow::onSendClicked);
    connect(createRoomButton, &QPushButton::clicked,
            this, &ChatWindow::onCreateRoomClicked);
    connect(clearChatButton, &QPushButton::clicked,
            this, &ChatWindow::onClearChatClicked);
    connect(messageInput, &QLineEdit::returnPressed,
            this, &ChatWindow::onSendClicked);
}

void ChatWindow::loadRooms() {
    int currentID = -1;
    if (roomList->currentItem()) {
        currentID = roomList->currentItem()
                        ->data(Qt::UserRole).toInt();
    }

    roomList->clear();
    auto rooms = controller->getRooms();
    for (auto& room : rooms) {
        auto* item = new QListWidgetItem(
            QString::fromStdString("# " + room->getName())
        );
        item->setData(Qt::UserRole, room->getID());
        roomList->addItem(item);

        if (room->getID() == currentID) {
            roomList->setCurrentItem(item);
        }
    }
}

void ChatWindow::loadMessages() {
    messageDisplay->clear();
    auto messages = controller->getMessages();
    for (auto& msg : messages) {
        QString formatted = QString(
            "<span style='color: #5865F2; "
            "font-weight: bold;'>%1</span>"
            "<span style='color: #72767D; "
            "font-size: 11px;'> %2</span>"
            "<br>"
            "<span style='color: #DCDDDE;'>%3</span>"
            "<br><br>"
        )
        .arg(QString::fromStdString(msg->getSenderName()))
        .arg(QString::fromStdString(msg->getTimestamp()))
        .arg(QString::fromStdString(msg->getContent()));

        messageDisplay->insertHtml(formatted);
    }

    // Scroll to bottom
    auto* scrollBar = messageDisplay->verticalScrollBar();
    scrollBar->setValue(scrollBar->maximum());
}

void ChatWindow::onRoomSelected(QListWidgetItem* item) {
    int roomID = item->data(Qt::UserRole).toInt();
    controller->joinRoom(roomID);
    controller->selectRoom(roomID);

    QString roomName = item->text();
    currentRoomLabel->setText(roomName);
    loadMessages();
}

void ChatWindow::onSendClicked() {
    std::string content =
        messageInput->text().toStdString();

    if (content.empty()) return;
    if (!controller->getCurrentRoom()) return;

    if (controller->sendMessage(content)) {
        messageInput->clear();
        loadMessages();
    }
}

void ChatWindow::onCreateRoomClicked() {
    CreateRoomDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        std::string name = dialog.getRoomName();
        if (controller->createRoom(name)) {
            loadRooms();
        }
    }
}

void ChatWindow::onClearChatClicked() {
    if (!controller->getCurrentRoom()) return;

    auto reply = QMessageBox::question(
        this, "Clear Chat",
        "Are you sure you want to delete all messages "
        "in this room?",
        QMessageBox::Yes | QMessageBox::No
    );

    if (reply == QMessageBox::Yes) {
        if (controller->clearCurrentChat()) {
            loadMessages();
        }
    }
}

void ChatWindow::onTimerTick() {
    loadRooms();
    if (controller->getCurrentRoom()) {
        loadMessages();
    }
}