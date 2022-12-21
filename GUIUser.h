#pragma once

#include <qdialog.h>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>
#include "UserService.h"
#include "TrenchCoat.h"

#define IMAGE_WIDTH 240
#define IMAGE_HEIGHT 240

class GUIUser : public QDialog
{
	Q_OBJECT

public:
	GUIUser(UserService& service, QWidget* parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
	~GUIUser();

private:
	UserService& service;
	QNetworkAccessManager* networkManager;
	std::vector<TrenchCoat> trenchCoatList;
	int currentIndex = -1;
	//bool hasAdopted = false;

	QLabel* trenchCoatImage;

	QLineEdit* trenchCoatIDEdit;
	QLineEdit* trenchCoatSizeEdit;
	QLineEdit* trenchCoatColourEdit;
	QLineEdit* trenchCoatPriceEdit;
	QLineEdit* trenchCoatQuantityEdit;
	QLineEdit* trenchCoatPhotographyUrlEdit;

	QPushButton* viewAllButton;
	QPushButton* viewFilteredButton;
	QPushButton* showBasketButton;
	QPushButton* changeModeButton;

	QPushButton* addToBasketButton;
	QPushButton* nextButton;
	QPushButton* stopButton;

	void initGUI();
	void connectSignalsAndSlots();
	void reject();
	void showInformation(const std::string& info);
	void showError(const std::string& err);

	void loadCurrentTrenchCoat();
	void loadImage(const std::string& imageURL);

	void addToBasketButtonHandler();

signals:
	void prepareBasketSignal();
	void addToBasketSignal(const TrenchCoat& trenchCoat);

	void nextTrenchCoatSignal();
	void stopShowingTrenchCoatsSignal();

public slots:
	void viewAllTrenchCoats();
	void viewFilteredTrenchCoats();
	void showBasket();
	void changeUserMode();

	void prepareBasket();

	void addToBasket(const TrenchCoat& trenchCoat);
	void loadNextTrenchCoat();
	void stopShowingTrenchCoats();

	void receivedReply(QNetworkReply* reply);
};