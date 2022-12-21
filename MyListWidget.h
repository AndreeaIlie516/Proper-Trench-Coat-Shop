#pragma once

#include <QWidget>
#include "ui_MyListWidget.h"
#include "MyListTableModel.h"

class MyListWidget : public QWidget
{
	Q_OBJECT

public:
	MyListWidget(MyListTableModel* model, QWidget* parent = Q_NULLPTR);
	~MyListWidget() {};
	void addInBasketList(const int& ID) {
		model->addInBasket(ID);

	};
	void changeRepositoryFileName(std::string fileName, std::string extension) {
		this->model->changeRepositoryFileName(fileName, extension);
	}
private:
	Ui::MyListWidgetClass ui;
	MyListTableModel* model;
};