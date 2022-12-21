#pragma once


#include <QtWidgets/QMainWindow>
#include <qdialog.h>
#include <QListWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include "AdminService.h"
#include "TrenchCoat.h"
#include "TrenchCoatValidator.h"


class GUIAdmin : public QDialog
{
	Q_OBJECT

public:
	GUIAdmin(AdminService& service, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
	~GUIAdmin() = default;

private:
	AdminService& service;
	std::vector<TrenchCoat> trenchCoatsToShow;
	TrenchCoat selectedTrenchCoat;

	QListWidget* trenchCoatList;

	//QLineEdit* filterEdit;
	QLineEdit* trenchCoatIDEdit;
	QLineEdit* trenchCoatSizeEdit;
	QLineEdit* trenchCoatColourEdit;
	QLineEdit* trenchCoatPriceEdit;
	QLineEdit* trenchCoatQuantityEdit;
	QLineEdit* trenchCoatPhotographyUrlEdit;

	QPushButton* addTrenchCoatButton;
	QPushButton* deleteTrenchCoatButton;
	QPushButton* updateTrenchCoatButton;
	QPushButton* changeModeButton;

	void initGUI();
	void connectSignalsAndSlots();
	void reject();
	void showInformation(const std::string& info);
	void showError(const std::string& err);

	void populateTrenchCoatsList();
	void listItemChanged();
	int getSelectedIndex();

	void addTrenchCoatButtonHandler();
	void deleteTrenchCoatButtonHandler();
	void updateTrenchCoatButtonHandler();

signals:
	void trenchCoatUpdatedSignal();
	void loadTrenchCoatsSignal(int oldIndex = 0);

	void addTrenchCoatSignal(const int& ID, const int& size, const std::string& colour, const double& price, const int& quantity, const std::string& photographyUrl);
	void removeTrenchCoatSignal(const int& ID);
	void updateTrenchCoatSignal(const int& ID, const int& size, const std::string& colour, const double& price, const int& quantity, const std::string& photographyUrl);

public slots:
	void loadTrenchCoats(int oldIndex = 0);
	//void filter(const QString& qstr);
	void changeUserMode();

	void addTrenchCoat(const int& ID, const int& size, const std::string& colour, const double& price, const int& quantity, const std::string& photographyUrl);
	void removeTrenchCoat(const int& ID);
	void updateTrenchCoat(const int& ID, const int& size, const std::string& colour, const double& price, const int& quantity, const std::string& photographyUrl);
};
