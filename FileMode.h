#pragma once
#include <qdialog.h>
#include <QPushButton>
#include <QLabel>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>

#include "AdminService.h"
#include "UserService.h"

class FileMode : public QDialog
{
	Q_OBJECT;

public:
	FileMode(QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
	~FileMode() = default;



private:
	int mode;

	QPushButton* CSVButton;
	QPushButton* HTMLButton;
	QLabel* label_2;
	QSplitter* splitter;

	void initGUI();
	void connectSignalsAndSlots();
	void reject();

	void CSVButtonHandler();
	void HTMLButtonHandler();

	void loadNext();

signals:
	void modeSelectedSignal();

public slots:

};

