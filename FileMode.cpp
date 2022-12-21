#include <QGridLayout>
#include "FileMode.h"
#include "FileRepository.h"
#include "CSVRepository.h"
#include "HTMLRepository.h"
#include "TrenchCoatValidator.h"
#include "GUIMode.h"


FileMode::FileMode(QWidget* parent, Qt::WindowFlags f) : QDialog{ parent, f }
{
	this->mode = -1;

	this->initGUI();
	this->connectSignalsAndSlots();
}

void FileMode::initGUI()
{
	QFont f{ "Arial", 12 };
	QGridLayout* layout = new QGridLayout{ this };

	QLabel* label = new QLabel{ "Mode:" };
	label->setFont(f);

	this->CSVButton = new QPushButton("CSV");
	this->CSVButton->setFont(f);

	this->HTMLButton = new QPushButton("HTML");
	this->HTMLButton->setFont(f);

	layout->addWidget(new QLabel{}, 0, 1);
	layout->addWidget(label, 1, 1, Qt::AlignCenter);
	layout->addWidget(new QLabel{}, 2, 1);
	layout->addWidget(this->CSVButton, 3, 0);
	layout->addWidget(this->HTMLButton, 3, 2);
	layout->addWidget(new QLabel{}, 4, 1);

}

void FileMode::connectSignalsAndSlots()
{
	QObject::connect(this, &FileMode::modeSelectedSignal, this, &FileMode::loadNext);

	QObject::connect(this->CSVButton, &QPushButton::clicked, this, &FileMode::CSVButtonHandler);
	QObject::connect(this->HTMLButton, &QPushButton::clicked, this, &FileMode::HTMLButtonHandler);

}

void FileMode::reject()
{
	exit(0);
}

void FileMode::CSVButtonHandler()
{
	this->mode = 0;
	emit modeSelectedSignal();
}

void FileMode::HTMLButtonHandler()
{
	this->mode = 1;
	emit modeSelectedSignal();
}

void FileMode::loadNext()
{
	this->hide();

	FileRepository* basket = nullptr;
	switch (this->mode)
	{
	case 0:
		basket = new CSVRepository;
		break;
	case 1:
		basket = new HTMLRepository;
		break;
	default:
		return;
	}

	FileRepository repo{"input.txt" };
	TrenchCoatValidator validator;
	FileRepository* repository = new FileRepository{ "inputFile.txt" };
	int generate = 0;
	AdminService adminService{ repository, generate };
	UserService userService{ repository };
	GUIMode gui{ adminService, userService };
	while (gui.exec());

	delete basket;
	this->accept();
}
