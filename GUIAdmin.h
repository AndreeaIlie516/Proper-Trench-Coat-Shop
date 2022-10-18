#pragma once

#include <QWidget>
#include "ui_GUIAdmin.h"

class GUIAdmin : public QWidget
{
	Q_OBJECT

public:
	GUIAdmin(QWidget *parent = Q_NULLPTR);
	~GUIAdmin();

private:
	Ui::GUIAdmin ui;
};
