#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProperTrenchCoatShop.h"
#include "AdminService.h"
#include "UserService.h"
#include "MyListWidget.h"

class ProperTrenchCoatShop : public QMainWindow
{
    Q_OBJECT

public:
	ProperTrenchCoatShop(AdminService& adminService, UserService& userService, MyListWidget& myListWidget, QWidget* parent = Q_NULLPTR);

private:
	MyListWidget& myListWidget;
	AdminService& adminService;
	UserService& userService;
	Ui::ProperTrenchCoatShopClass ui;
	bool modeAOrB;

	void connectSignalsAndSlots();
	int getSelectedIndex() const;

	void populateList();
	void populateMyList();
	void addTrenchCoat();
	void deleteTrenchCoat();
	void updateTrenchCoat();
	void undo();
	void redo();
	void sortBySize();
	void updateFileName();
	void updateMyListLocation();
	void openMyList();
	void addToBasket();
	void nextTrenchCoat();
	void openMyListInNewWindow();
	void modeA() { this->modeAOrB = 1; };
	void modeB() { this->modeAOrB = 0; };
};
