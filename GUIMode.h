#pragma once

#include <QtWidgets/QWidget>
#include "ui_GUIMode.h"
#include "GUIFile.h"

class GUIMode : public QWidget
{
    Q_OBJECT

public:
    GUIMode(QWidget *parent = Q_NULLPTR);
    ~GUIMode() = default;

private:
    Ui::GUIModeClass ui;

    void connectSignalsAndSlots();

    void selectAdmin();

    void selectUser();
};
