#pragma once

#include <qdialog.h>
#include <QPushButton>
#include <QLabel>

#include "AdminService.h"
#include "UserService.h"

class GUIMode : public QDialog
{
	Q_OBJECT;

public:
	GUIMode(AdminService &adminService, UserService &userService, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
	~GUIMode() = default;

private:
	int mode;
	AdminService& adminService;
	UserService& userService;

	QPushButton* adminButton;
	QPushButton* userButton;

	void initGUI();
	void connectSignalsAndSlots();
	void reject();

	void AdminButtonHandler();
	void UserButtonHandler();

	void loadNext();

signals:
	void modeSelectedSignal();

public slots:

};