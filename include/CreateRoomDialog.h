#ifndef CREATEROOMDIALOG_H
#define CREATEROOMDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

class CreateRoomDialog : public QDialog {
    Q_OBJECT

private:
    QLineEdit* roomNameInput;
    QPushButton* createButton;
    QPushButton* cancelButton;

    void setupUI();

public:
    CreateRoomDialog(QWidget* parent = nullptr);
    std::string getRoomName() const;
};

#endif