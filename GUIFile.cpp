#include "GUIFile.h"

GUIFile::GUIFile(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

GUIFile::~GUIFile()
{
}

void GUIFile::connectSignalsAndSlots()
{
	QObject::connect(this, SIGNAL(repoSelectedSignal(const int&)), this, SLOT(repoSelected(const int&)));

	QObject::connect(this->CSVModeButton, &QPushButton::clicked, this, &GUIFile::CSVButton);
	QObject::connect(this->HTMLModeButton, &QPushButton::clicked, this, &GUIFile::HTMLButton);

}

void GUIFile::CSVButton()
{
}

void GUIFile::HTMLButton()
{
}
