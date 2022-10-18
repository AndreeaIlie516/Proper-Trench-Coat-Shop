#include "GUIMode.h"

GUIMode::GUIMode(QWidget* parent)
    : QWidget(parent)
{
    ui.setupUi(this);

    this->connectSignalsAndSlots();
}

void GUIMode::connectSignalsAndSlots()
{
    QObject::connect(ui.adminModeButton, &QPushButton::clicked, this, &GUIMode::selectAdmin);
    QObject::connect(this->CSVModeButton, &QPushButton::clicked, this, &GUIMode::CSVButton);
    QObject::connect(this->HTMLModeButton, &QPushButton::clicked, this, &GUIMode::HTMLButton);

}

void GUIMode::selectAdmin()
{
    GUIFile w;
    w.show();
}

void GUIMode::selectUser()
{
    GUIFile w;
    w.show();
}
