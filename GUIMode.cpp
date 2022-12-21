#include <QGridLayout>
#include "GUIMode.h"
#include "AdminGUI.h"

GUIMode::GUIMode(AdminService& adminService, UserService& userService, QWidget* parent, Qt::WindowFlags f) : QDialog{ parent, f }, adminService {adminService}, userService {userService}
{
	this->mode = -1;

	this->initGUI();
	this->connectSignalsAndSlots();
}

void GUIMode::initGUI()
{
	QFont f{ "Arial", 12 };
	QGridLayout* layout = new QGridLayout{ this };

	QLabel* label = new QLabel{ "Mode:" };
	label->setFont(f);

	this->adminButton = new QPushButton("Admin");
	this->adminButton->setFont(f);

	this->userButton = new QPushButton("User");
	this->userButton->setFont(f);

	layout->addWidget(new QLabel{}, 0, 1);
	layout->addWidget(label, 1, 1, Qt::AlignCenter);
	layout->addWidget(new QLabel{}, 2, 1);
	layout->addWidget(this->adminButton, 3, 0);
	layout->addWidget(this->userButton, 3, 2);
	layout->addWidget(new QLabel{}, 4, 1);

}

void GUIMode::connectSignalsAndSlots()
{
	QObject::connect(this, &GUIMode::modeSelectedSignal, this, &GUIMode::loadNext);

	QObject::connect(this->adminButton, &QPushButton::clicked, this, &GUIMode::AdminButtonHandler);
	QObject::connect(this->userButton, &QPushButton::clicked, this, &GUIMode::UserButtonHandler);

}

void GUIMode::reject()
{
	exit(0);
}

void GUIMode::AdminButtonHandler()
{
	this->mode = 0;
	emit modeSelectedSignal();
}

void GUIMode::UserButtonHandler()
{
	this->mode = 1;
	emit modeSelectedSignal();
}

void GUIMode::loadNext()
{
	this->hide();

	QDialog* gui = nullptr;
	switch (this->mode)
	{
	case 0:
		gui = new GUIAdmin{ this->adminService };
		break;
	case 1:
		gui = nullptr;
		break;
	default:
		return;
	}

	gui->exec();

	delete gui;
	this->accept();
}
