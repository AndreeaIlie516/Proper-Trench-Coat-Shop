#include <QHBoxLayout>
#include <QFormLayout>
#include <QMessageBox>
#include "AdminGUI.h"
#include <vector>
#include <string>

GUIAdmin::GUIAdmin(AdminService& service, QWidget* parent, Qt::WindowFlags f) : QDialog{ parent, f }, service{ service }
{
	this->initGUI();
	this->connectSignalsAndSlots();
	this->populateTrenchCoatsList();
	//tableView.setModel(model);
}

void GUIAdmin::initGUI()
{
	// General layout of the window
	QHBoxLayout* layout = new QHBoxLayout{ this };
	QFont f{ "Arial", 14 };

	// left side - just the list
	this->trenchCoatList = new QListWidget{};
	// set the selection model
	this->trenchCoatList->setSelectionMode(QAbstractItemView::SingleSelection);
	layout->addWidget(this->trenchCoatList);

	// right side - trench coat information + buttons
	QWidget* rightSide = new QWidget{};
	QVBoxLayout* vLayout = new QVBoxLayout{ rightSide };

	// trenchCoat information
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
	QWidget* buttonsWidget = new QWidget{};
	QHBoxLayout* hLayout = new QHBoxLayout{ buttonsWidget };

	this->addTrenchCoatButton = new QPushButton("Add");
	this->addTrenchCoatButton->setFont(f);

	this->deleteTrenchCoatButton = new QPushButton("Delete");
	this->deleteTrenchCoatButton->setFont(f);

	this->updateTrenchCoatButton = new QPushButton("Update");
	this->updateTrenchCoatButton->setFont(f);

	this->changeModeButton = new QPushButton("Change Mode");
	this->changeModeButton->setFont(f);

	hLayout->addWidget(this->addTrenchCoatButton);
	hLayout->addWidget(this->deleteTrenchCoatButton);
	hLayout->addWidget(this->updateTrenchCoatButton);
	hLayout->addWidget(this->changeModeButton);

	vLayout->addWidget(buttonsWidget);

	// add everything to the big layout
	layout->addWidget(this->trenchCoatList);
	layout->addWidget(rightSide);

	// disable buttons on initial empty list
	deleteTrenchCoatButton->setEnabled(false);
	updateTrenchCoatButton->setEnabled(false);


	// add gradient to list
	QLinearGradient listGradient(0, 0, 0, this->trenchCoatList->height());
	listGradient.setColorAt(0, Qt::white);
	listGradient.setColorAt(1, Qt::gray);

	QPalette palette = this->trenchCoatList->palette();
	palette.setBrush(QPalette::ColorRole::Base, QBrush(listGradient));
	this->trenchCoatList->setPalette(palette);
}

void GUIAdmin::connectSignalsAndSlots()
{
	// when the list of dogs is updated - re-populate the list
	QObject::connect(this, &GUIAdmin::trenchCoatUpdatedSignal, this, &GUIAdmin::populateTrenchCoatsList);
	//QObject::connect(filterEdit, &QLineEdit::textChanged, this, &GUIAdmin::filter);
	QObject::connect(this, &GUIAdmin::loadTrenchCoatsSignal, this, &GUIAdmin::loadTrenchCoats);

	// add a connection: function listItemChanged() will be called when an item in the list is selected
	QObject::connect(this->trenchCoatList, &QListWidget::itemSelectionChanged, this, [this]() { this->listItemChanged(); });

	// add button connections
	QObject::connect(this->addTrenchCoatButton, &QPushButton::clicked, this, &GUIAdmin::addTrenchCoatButtonHandler);
	QObject::connect(this->deleteTrenchCoatButton, &QPushButton::clicked, this, &GUIAdmin::deleteTrenchCoatButtonHandler);
	QObject::connect(this->updateTrenchCoatButton, &QPushButton::clicked, this, &GUIAdmin::updateTrenchCoatButtonHandler);
	QObject::connect(this->changeModeButton, &QPushButton::clicked, this, &GUIAdmin::changeUserMode);

	// connect the signals
	QObject::connect(this, SIGNAL(addTrenchCoatSignal(const int&, const int&, const std::string&, const double&, const int& const std::string&)),
		this, SLOT(addTrenchCoat(const int&, const int&, const std::string&, const double&, const int& const std::string&)));

	QObject::connect(this, SIGNAL(removeTrenchCoatSignal(const int&)),
		this, SLOT(removeTrenchCoat(const int&)));

	QObject::connect(this, SIGNAL(updateTrenchCoatSignal(const int&, const int&, const std::string&, const double&, const int& const std::string&)),
		this, SLOT(updateTrenchCoat(const int&, const int&, const std::string&, const double&, const int& const std::string&)));
}

void GUIAdmin::reject()
{
	exit(0);
}

void GUIAdmin::showInformation(const std::string& info)
{
	QMessageBox::information(this, "Information", QString::fromStdString(info));
}

void GUIAdmin::showError(const std::string& err)
{
	QMessageBox::critical(this, "Error", QString::fromStdString(err));
}

void GUIAdmin::populateTrenchCoatsList()
{
	/*if (this->filterEdit->text().size() > 0)
	{
		this->filter(this->filterEdit->text());
		return;
	}*/

	int oldIndex = this->getSelectedIndex();
	this->trenchCoatList->clear();

	this->trenchCoatsToShow = this->service.adminGetTrenchCoatsList();
	emit loadTrenchCoatsSignal(oldIndex);
}

//void GUIAdmin::filter(const QString& qstr)
//{
//	std::string text = qstr.toStdString();
//	if (text.size() == 0)
//	{
//		emit trenchCoatUpdatedSignal();
//		return;
//	}
//
//	int oldIndex = this->getSelectedIndex();
//	this->trenchCoatList->clear();
//
//	this->trenchCoatsToShow = this->service.filterByName(text).getTrenchCoatsList();
//	emit loadTrenchCoatsSignal(oldIndex);
//}

void GUIAdmin::loadTrenchCoats(int oldIndex)
{
	for (auto& trenchCoat : this->trenchCoatsToShow)
	{
		QString itemInList = QString::fromStdString(std::to_string(trenchCoat.getID()));
		QListWidgetItem* item = new QListWidgetItem{ itemInList };

		QFont f{ "Arial", 14 };
		item->setFont(f);

		this->trenchCoatList->addItem(item);
	}

	// set the selection to the previous one
	// (if possible) so the cursor doesn't jump
	if (oldIndex == -1 || this->trenchCoatList->count() == 0)
	{
		this->trenchCoatList->setCurrentRow(0);

		if (this->trenchCoatList->count() > 0)
			this->selectedTrenchCoat = this->trenchCoatsToShow[0];
		else
			this->selectedTrenchCoat = TrenchCoat{};
	}
	else
	{
		while (oldIndex >= this->trenchCoatList->count())
			oldIndex--;

		this->trenchCoatList->setCurrentRow(oldIndex);
		this->selectedTrenchCoat = this->trenchCoatsToShow[oldIndex];
	}

	deleteTrenchCoatButton->setEnabled(this->trenchCoatList->count() > 0);
	updateTrenchCoatButton->setEnabled(this->trenchCoatList->count() > 0);
}

void GUIAdmin::listItemChanged()
{
	int index = this->getSelectedIndex();
	if (index == -1 || index >= this->trenchCoatsToShow.size())
		return;

	TrenchCoat trenchCoat = this->trenchCoatsToShow[index];
	this->selectedTrenchCoat = trenchCoat;

	this->trenchCoatIDEdit->setText(QString::fromStdString(std::to_string(trenchCoat.getID())));
	this->trenchCoatSizeEdit->setText(QString::fromStdString(std::to_string(trenchCoat.getSize())));
	this->trenchCoatColourEdit->setText(QString::fromStdString(trenchCoat.getColour()));
	this->trenchCoatPriceEdit->setText(QString::fromStdString(std::to_string(trenchCoat.getPrice())));
	this->trenchCoatQuantityEdit->setText(QString::fromStdString(std::to_string(trenchCoat.getQuantity())));
	this->trenchCoatPhotographyUrlEdit->setText(QString::fromStdString(trenchCoat.getPhotographyUrl()));
}

int GUIAdmin::getSelectedIndex()
{
	if (this->trenchCoatList->count() == 0)
		return -1;

	// get selected index
	QModelIndexList listIndex = this->trenchCoatList->selectionModel()->selectedIndexes();
	if (listIndex.size() == 0)
	{
		this->trenchCoatIDEdit->clear();
		this->trenchCoatSizeEdit->clear();
		this->trenchCoatColourEdit->clear();
		this->trenchCoatPriceEdit->clear();
		this->trenchCoatQuantityEdit->clear();
		this->trenchCoatPhotographyUrlEdit->clear();

		return -1;
	}

	return listIndex.at(0).row();
}

void GUIAdmin::addTrenchCoatButtonHandler()
{
	// read data from the textboxes and add the new dog
	int ID = this->trenchCoatIDEdit->text().size() == 0 ? -1 : std::stoi(this->trenchCoatIDEdit->text().toStdString());
	int size = this->trenchCoatSizeEdit->text().size() == 0 ? -1 : std::stoi(this->trenchCoatSizeEdit->text().toStdString());
	std::string colour = this->trenchCoatColourEdit->text().toStdString();
	double price = this->trenchCoatPriceEdit->text().size() == 0 ? -1 : std::stod(this->trenchCoatPriceEdit->text().toStdString());
	int quantity = this->trenchCoatQuantityEdit->text().size() == 0 ? -1 : std::stoi(this->trenchCoatQuantityEdit->text().toStdString());
	std::string photographyUrl = this->trenchCoatPhotographyUrlEdit->text().toStdString();
	//std::string photographyUrl = this->trenchCoatPhotographyUrlEdit->toPlainText().toStdString();

	emit addTrenchCoatSignal(ID, size, colour, price, quantity, photographyUrl);
}

void GUIAdmin::deleteTrenchCoatButtonHandler()
{
	// read data from the textboxes and delete the dog

	int ID = this->trenchCoatIDEdit->text().size() == 0 ? -1 : std::stoi(this->trenchCoatIDEdit->text().toStdString());

	emit removeTrenchCoatSignal(ID);
}

void GUIAdmin::updateTrenchCoatButtonHandler()
{
	// read data from the textboxes and add the new dog
	int ID = this->trenchCoatIDEdit->text().size() == 0 ? -1 : std::stoi(this->trenchCoatIDEdit->text().toStdString());
	int size = this->trenchCoatSizeEdit->text().size() == 0 ? -1 : std::stoi(this->trenchCoatSizeEdit->text().toStdString());
	std::string colour = this->trenchCoatColourEdit->text().toStdString();
	double price = this->trenchCoatPriceEdit->text().size() == 0 ? -1 : std::stod(this->trenchCoatPriceEdit->text().toStdString());
	int quantity = this->trenchCoatQuantityEdit->text().size() == 0 ? -1 : std::stoi(this->trenchCoatQuantityEdit->text().toStdString());
	std::string photographyUrl = this->trenchCoatPhotographyUrlEdit->text().toStdString();
	//std::string photographyUrl = this->trenchCoatPhotographyUrlEdit->toPlainText().toStdString();

	emit updateTrenchCoatSignal(ID, size, colour, price, quantity, photographyUrl);
}

void GUIAdmin::changeUserMode()
{
	this->accept();
}

void GUIAdmin::addTrenchCoat(const int& ID, const int& size, const std::string& colour, const double& price, const int& quantity, const std::string& photographyUrl)
{
	try
	{
		this->service.adminAddTrenchCoat(ID, size, colour, price, quantity, photographyUrl);
		emit trenchCoatUpdatedSignal();

		this->showInformation("Trench coat added successfully.");
	}
	catch (RepositoryException& e)
	{
		this->showError(e.what());
	}
}

void GUIAdmin::removeTrenchCoat(const int& ID)
{
	try
	{
		this->service.adminRemoveTrenchCoat(ID);
		emit trenchCoatUpdatedSignal();

		this->showInformation("Trench coat removed successfully.");
	}
	catch (RepositoryException& e)
	{
		this->showError(e.what());
	}
}

void GUIAdmin::updateTrenchCoat(const int& ID, const int& size, const std::string& colour, const double& price, const int& quantity, const std::string& photographyUrl)
{
	/*TrenchCoat trenchCoat{ ID, size, colour, price, quantity, photographyUrl };
	if (this->selectedDog == dog)
	{
		this->showError("The dog was not modified!");
		return;
	}*/

	try
	{
		this->service.adminUpdateTrenchCoat(ID, size, colour, price, quantity, photographyUrl);
		emit trenchCoatUpdatedSignal();

		this->showInformation("Trench coat update successfully.");
	}
	catch (RepositoryException& e)
	{
		this->showError(e.what());
	}
}