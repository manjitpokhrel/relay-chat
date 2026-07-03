#include "CreateRoomDialog.h"

CreateRoomDialog::CreateRoomDialog(QWidget* parent)
    : QDialog(parent) {
    setupUI();
}

void CreateRoomDialog::setupUI() {
    setWindowTitle("Create Room");
    setFixedSize(300, 150);

    auto* layout = new QVBoxLayout(this);

    auto* label = new QLabel("Room Name:", this);

    roomNameInput = new QLineEdit(this);
    roomNameInput->setPlaceholderText("Enter room name...");

    createButton = new QPushButton("Create", this);
    createButton->setStyleSheet(
        "background-color: #5865F2; color: white; "
        "padding: 6px; border-radius: 4px;"
    );

    cancelButton = new QPushButton("Cancel", this);

    layout->addWidget(label);
    layout->addWidget(roomNameInput);
    layout->addWidget(createButton);
    layout->addWidget(cancelButton);

    connect(createButton, &QPushButton::clicked,
            this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked,
            this, &QDialog::reject);
}

std::string CreateRoomDialog::getRoomName() const {
    return roomNameInput->text().toStdString();
}