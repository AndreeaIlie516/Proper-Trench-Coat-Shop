#include "GUIUser.h"
#include <QEventLoop>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QFormLayout>

GUIUser::GUIUser(UserService& service, QWidget* parent, Qt::WindowFlags f) : QDialog{ parent, f }, service{ service }
{
	this->networkManager = new QNetworkAccessManager{ this };

	this->initGUI();
	this->connectSignalsAndSlots();
}

void GUIUser::initGUI()
{
	// General layout of the window
	QHBoxLayout* layout = new QHBoxLayout{ this };
	QFont f{ "Arial", 14 };

	// left side - just the image
	this->trenchCoatImage = new QLabel{};
	QImage image(IMAGE_WIDTH, IMAGE_HEIGHT, QImage::Format::Format_ARGB32);
	image.fill(Qt::white);
	this->trenchCoatImage->setPixmap(QPixmap::fromImage(image));
	// set the selection model
	layout->addWidget(this->trenchCoatImage);

	// right side - dog information + buttons
	QWidget* mainWidget = new QWidget{};
	QVBoxLayout* vLayout = new QVBoxLayout{ mainWidget };

	// dog information
	QWidget* trenchCoatDataWidget = new QWidget{};
	QFormLayout* formLayout = new QFormLayout{ trenchCoatDataWidget };

	//this->filterEdit = new QLineEdit{};
	this->trenchCoatIDEdit = new QLineEdit{};
	this->trenchCoatSizeEdit = new QLineEdit{};
	this->trenchCoatColourEdit = new QLineEdit{};
	this->trenchCoatPriceEdit = new QLineEdit{};
	this->trenchCoatQuantityEdit = new QLineEdit{};
	this->trenchCoatPhotographyUrlEdit = new QLineEdit{};

	/*QLabel* filterLabel = new QLabel{ "&Filter:" };
	filterLabel->setBuddy(this->filterEdit);*/
	QLabel* IDLabel = new QLabel{ "&Trench coat ID:" };
	IDLabel->setBuddy(this->trenchCoatIDEdit);
	QLabel* sizeLabel = new QLabel{ "&Trench coat size: " };
	sizeLabel->setBuddy(this->trenchCoatSizeEdit);
	QLabel* colourLabel = new QLabel{ "&Trench coat colour: " };
	colourLabel->setBuddy(this->trenchCoatColourEdit);
	QLabel* priceLabel = new QLabel{ "&Trench coat price: " };
	priceLabel->setBuddy(this->trenchCoatPriceEdit);
	QLabel* quantityLabel = new QLabel{ "&Trench coat quantity: " };
	quantityLabel->setBuddy(this->trenchCoatQuantityEdit);
	QLabel* photographyUrlLabel = new QLabel{ "&Trench coat photography url: " };
	photographyUrlLabel->setBuddy(this->trenchCoatPhotographyUrlEdit);

	//filterLabel->setFont(f);
	IDLabel->setFont(f);
	sizeLabel->setFont(f);
	colourLabel->setFont(f);
	priceLabel->setFont(f);
	quantityLabel->setFont(f);
	photographyUrlLabel->setFont(f);
	//this->filterEdit->setFont(f);
	this->trenchCoatIDEdit->setFont(f);
	this->trenchCoatSizeEdit->setFont(f);
	this->trenchCoatColourEdit->setFont(f);
	this->trenchCoatPriceEdit->setFont(f);
	this->trenchCoatQuantityEdit->setFont(f);
	this->trenchCoatPhotographyUrlEdit->setFont(f);

	//formLayout->addRow(filterLabel, this->filterEdit);
	formLayout->addRow(IDLabel, this->trenchCoatIDEdit);
	formLayout->addRow(sizeLabel, this->trenchCoatSizeEdit);
	formLayout->addRow(colourLabel, this->trenchCoatColourEdit);
	formLayout->addRow(priceLabel, this->trenchCoatPriceEdit);
	formLayout->addRow(quantityLabel, this->trenchCoatQuantityEdit);
	formLayout->addRow(photographyUrlLabel, this->trenchCoatPhotographyUrlEdit);

	vLayout->addWidget(trenchCoatDataWidget);

	// buttons
	QWidget* buttonsWidget1 = new QWidget{};
	QHBoxLayout* hLayout1 = new QHBoxLayout{ buttonsWidget1 };

	this->viewAllButton = new QPushButton("View All Trench Coats");
	this->viewAllButton->setFont(f);

	this->viewFilteredButton = new QPushButton("View Matching Trench Coats");
	this->viewFilteredButton->setFont(f);

	// buttons
	QWidget* buttonsWidget2 = new QWidget{};
	QHBoxLayout* hLayout2 = new QHBoxLayout{ buttonsWidget2 };

	this->showBasketButton = new QPushButton("Show Basket");
	this->showBasketButton->setFont(f);

	this->changeModeButton = new QPushButton("Change Mode");
	this->changeModeButton->setFont(f);

	// buttons
	QWidget* buttonsWidget3 = new QWidget{};
	QHBoxLayout* hLayout3 = new QHBoxLayout{ buttonsWidget3 };

	this->addToBasketButton = new QPushButton("Add to cart");
	this->addToBasketButton->setFont(f);

	this->nextButton = new QPushButton("Next");
	this->nextButton->setFont(f);

	this->stopButton = new QPushButton("Stop");
	this->stopButton->setFont(f);

	hLayout1->addWidget(this->viewAllButton);
	hLayout1->addWidget(this->viewFilteredButton);

	hLayout2->addWidget(this->showBasketButton);
	hLayout2->addWidget(this->changeModeButton);

	hLayout3->addWidget(this->addToBasketButton);
	hLayout3->addWidget(this->nextButton);
	hLayout3->addWidget(this->stopButton);

	vLayout->addWidget(buttonsWidget1);
	vLayout->addWidget(buttonsWidget2);
	vLayout->addWidget(buttonsWidget3);

	// add everything to the big layout
	layout->addWidget(mainWidget);

	trenchCoatSizeEdit->setEnabled(false);
	showBasketButton->setEnabled(false);

	addToBasketButton->setEnabled(false);
	nextButton->setEnabled(false);
	stopButton->setEnabled(false);
}

void GUIUser::connectSignalsAndSlots()
{
	QObject::connect(this->networkManager, &QNetworkAccessManager::finished, this, &GUIUser::receivedReply);

	// add button connections
	QObject::connect(this->viewAllButton, &QPushButton::clicked, this, &GUIUser::viewAllTrenchCoats);
	QObject::connect(this->viewFilteredButton, &QPushButton::clicked, this, &GUIUser::viewFilteredTrenchCoats);
	QObject::connect(this->showBasketButton, &QPushButton::clicked, this, &GUIUser::showBasket);
	QObject::connect(this->changeModeButton, &QPushButton::clicked, this, &GUIUser::changeUserMode);

	QObject::connect(this->addToBasketButton, &QPushButton::clicked, this, &GUIUser::addToBasketButtonHandler);
	QObject::connect(this->nextButton, &QPushButton::clicked, this, &GUIUser::loadNextTrenchCoat);
	QObject::connect(this->stopButton, &QPushButton::clicked, this, &GUIUser::stopShowingTrenchCoats);

	// connect the signals
	QObject::connect(this, &GUIUser::prepareBasketSignal, this, &GUIUser::prepareBasket);
	QObject::connect(this, &GUIUser::nextTrenchCoatSignal, this, &GUIUser::loadNextTrenchCoat);
	QObject::connect(this, &GUIUser::stopShowingTrenchCoatsSignal, this, &GUIUser::stopShowingTrenchCoats);

	QObject::connect(this, SIGNAL(addToBasketSignal(const TrenchCoat&)), this, SLOT(addToBasket(const TrenchCoat&)));
}

void GUIUser::reject()
{
	exit(0);
}

void GUIUser::showInformation(const std::string& info)
{
	QMessageBox::information(this, "Information", QString::fromStdString(info));
}

void GUIUser::showError(const std::string& err)
{
	QMessageBox::critical(this, "Error", QString::fromStdString(err));
}

void GUIUser::loadCurrentTrenchCoat()
{
	if (this->currentIndex == -1)
	{
		QImage image(IMAGE_WIDTH, IMAGE_HEIGHT, QImage::Format::Format_ARGB32);
		image.fill(Qt::white);

		this->trenchCoatImage->clear();
		this->trenchCoatImage->setPixmap(QPixmap::fromImage(image));

		this->trenchCoatIDEdit->clear();
		this->trenchCoatSizeEdit->clear();
		this->trenchCoatColourEdit->clear();
		this->trenchCoatPriceEdit->clear();
		this->trenchCoatQuantityEdit->clear();
		this->trenchCoatPhotographyUrlEdit->clear();

		return;
	}

	TrenchCoat trenchCoat = this->trenchCoatList[this->currentIndex];

	this->trenchCoatIDEdit->setText(QString::fromStdString(std::to_string(trenchCoat.getID())));
	this->trenchCoatSizeEdit->setText(QString::fromStdString(std::to_string(trenchCoat.getSize())));
	this->trenchCoatColourEdit->setText(QString::fromStdString(trenchCoat.getColour()));
	this->trenchCoatPriceEdit->setText(QString::fromStdString(std::to_string(trenchCoat.getPrice())));
	this->trenchCoatQuantityEdit->setText(QString::fromStdString(std::to_string(trenchCoat.getQuantity())));
	//this->trenchCoatPhotographyUrlEdit->setText(QString::fromStdString(trenchCoat.getPhotographyUrl()));
	this->loadImage(trenchCoat.getPhotographyUrl());

	//std::string command = "start ";
	//system(command.append(dog.getPhotohraph()).c_str());
}

void GUIUser::loadImage(const std::string& imageURL)
{
	QUrl url{ QString::fromStdString(imageURL) };
	this->networkManager->get(QNetworkRequest(url));
}

void GUIUser::viewAllTrenchCoats()
{
	this->trenchCoatList = this->service.userGetTrenchCoatList();
	emit prepareBasketSignal();
}

void GUIUser::viewFilteredTrenchCoats()
{
	int size = this->trenchCoatSizeEdit->text().size() == 0 ? -1 : std::stoi(this->trenchCoatSizeEdit->text().toStdString());

	this->trenchCoatList = this->service.filterTrenchCoatsBySize(size);
	emit prepareBasketSignal();
}

void GUIUser::showBasket()
{
	try
	{
		this->service.openBasket();
	}
	catch (RepositoryException& e)
	{
		this->showError(e.what());
	}
}

void GUIUser::changeUserMode()
{
	this->accept();
}

void GUIUser::addToBasketButtonHandler()
{
	TrenchCoat trenchCoat = trenchCoatList[this->currentIndex];

	emit addToBasketSignal(trenchCoat);

	if (trenchCoatList.size() == 0)
	{
		this->showInformation("There are no more trench coat available.");
		emit stopShowingTrenchCoatsSignal();
	}
	else
	{
		emit nextTrenchCoatSignal();
	}
}

void GUIUser::loadNextTrenchCoat()
{
	this->currentIndex++;
	if (this->currentIndex == this->trenchCoatList.size())
		this->currentIndex = 0;

	this->loadCurrentTrenchCoat();
}

void GUIUser::stopShowingTrenchCoats()
{
	this->currentIndex = -1;
	this->trenchCoatList.getAllTrenchCoats().clear();
	this->loadCurrentTrenchCoat();

	addToBasketButton->setEnabled(false);
	nextButton->setEnabled(false);
	stopButton->setEnabled(false);

	trenchCoatIDEdit->setEnabled(true);

	viewAllButton->setEnabled(true);
	viewFilteredButton->setEnabled(true);
	showBasketButton->setEnabled(true);
	changeModeButton->setEnabled(true);
}

void GUIUser::prepareBasket()
{
	if (trenchCoatList.size() == 0)
	{
		this->showInformation("There are no trench coats available.");
		return;
	}

	trenchCoatIDEdit->setEnabled(false);


	viewAllButton->setEnabled(false);
	viewFilteredButton->setEnabled(false);
	showBasketButton->setEnabled(false);
	changeModeButton->setEnabled(false);

	addToBasketButton->setEnabled(true);
	nextButton->setEnabled(true);
	stopButton->setEnabled(true);

	this->currentIndex = 0;
	this->loadCurrentTrenchCoat();
}

void GUIUser::addToBasket(const TrenchCoat& trenchCoat)
{
	try
	{
		this->service.addTrenchCoatToBasketList(trenchCoat);

		this->showInformation("Trench Coat added to cart successfully.");
	}
	catch (FileException& e)
	{
		this->showError(e.what());
	}
}

void GUIUser::receivedReply(QNetworkReply* reply)
{
	QImage image{ IMAGE_WIDTH, IMAGE_HEIGHT, QImage::Format::Format_ARGB32 };
	image.fill(Qt::black);

	if (reply->error() == QNetworkReply::NoError)
	{
		QByteArray replyData = reply->readAll();
		image.loadFromData(replyData);

		if (!image.isNull())
		{
			image = image.scaled(IMAGE_WIDTH, IMAGE_HEIGHT, Qt::AspectRatioMode::KeepAspectRatioByExpanding, Qt::TransformationMode::SmoothTransformation);
			image = image.copy(image.width() / 2 - IMAGE_WIDTH / 2, image.height() / 2 - IMAGE_HEIGHT / 2, IMAGE_WIDTH, IMAGE_HEIGHT);
		}
		else
		{
			image = QImage(IMAGE_WIDTH, IMAGE_HEIGHT, QImage::Format::Format_ARGB32);
			image.fill(Qt::black);
		}
	}

	this->trenchCoatImage->clear();
	this->trenchCoatImage->setPixmap(QPixmap::fromImage(image));

	reply->deleteLater();
}

GUIUser::~GUIUser()
{
	delete this->networkManager;
}