#pragma once

#include <QWidget>
#include "ui_GUIFile.h"

class GUIFile : public QWidget
{
	Q_OBJECT

public:
	GUIFile(QWidget *parent = Q_NULLPTR);
	~GUIFile();

private:

	int fileType;

	Ui::GUIFile ui;

	void connectSignalsAndSlots();

	void CSVButton();
	void HTMLButton();

signals:
	void fileSignal(const int& fileType);

public slots:
	void selectedFile(const int& fileType);
};
