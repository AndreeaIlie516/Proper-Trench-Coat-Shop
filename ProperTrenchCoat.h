#pragma once

#include <QtWidgets/QDialog>
#include "ui_ProperTrenchCoat.h"

class ProperTrenchCoat : public QDialog
{
    Q_OBJECT

public:
    ProperTrenchCoat(QWidget *parent = nullptr);
    ~ProperTrenchCoat();

private:
    Ui::ProperTrenchCoatClass ui;
};
