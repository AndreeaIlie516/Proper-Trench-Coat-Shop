#include "ProperTrenchCoatShop.h"
#include <iostream>
#include "qmessagebox.h"
#include <qshortcut.h>

ProperTrenchCoatShop::ProperTrenchCoatShop(AdminService& adminServiceGiven, UserService& userServiceGiven, MyListWidget& myListWidget, QWidget* parent)
    : QMainWindow(parent), adminService{ adminServiceGiven }, userService{ userServiceGiven }, myListWidget{ myListWidget }
{
    ui.setupUi(this);
    this->populateMyList();
    this->connectSignalsAndSlots();
    this->modeAOrB = 1;
}

void ProperTrenchCoatShop::populateList()
{
    this->ui.myListWidget->clear();
    try {
        if (this->adminService.adminGetTrenchCoatsList().size() == 0)
            return;
        std::vector<TrenchCoat> allTrenchCoats = this->adminService.adminGetTrenchCoatsList();
        for (TrenchCoat& trenchCoatUsed : allTrenchCoats)
            this->ui.movieListWidget->addItem(QString::fromStdString(trenchCoatUsed.getOutputForm()));
    }
    catch (std::exception& e) {
        return;
    }
}

void ProperTrenchCoatShop::connectSignalsAndSlots() {
    QShortcut* undoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z), this);
    QShortcut* redoShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y), this);

    QObject::connect(undoShortcut, &QShortcut::activated, this, &ProperTrenchCoatShop::undo);
    QObject::connect(redoShortcut, &QShortcut::activated, this, &ProperTrenchCoatShop::redo);
    QObject::connect(this->ui.movieListWidget, &QListWidget::itemSelectionChanged, [this]() {
        int selectedIndex = this->getSelectedIndex();
        if (selectedIndex < 0 || this->adminService.adminGetTrenchCoatsList().size() == 0)
            return;
        TrenchCoat trenchCoat = this->adminService.adminGetTrenchCoatsList()[selectedIndex];
        this->ui.IDLineEdit->setText(QString::fromStdString(std::to_string(trenchCoat.getID())));
        this->ui.sizeLineEdit->setText(QString::fromStdString(std::to_string(trenchCoat.getSize())));
        this->ui.colourLineEdit->setText(QString::fromStdString(trenchCoat.getColour()));
        this->ui.priceLineEdit->setText(QString::fromStdString(std::to_string(trenchCoat.getPrice())));
        this->ui.quantityLineEdit->setText(QString::fromStdString(std::to_string(trenchCoat.getQuantity())));
        this->ui.photographyUrlLineEdit->setText(QString::fromStdString(trenchCoat.getPhotographyUrl()));
        this->ui.fileLocationLineEdit->setText(QString::fromStdString(this->adminService.getFileName()));
        });
    QObject::connect(this->ui.myListWidget, &QListWidget::itemSelectionChanged, [this]() {
        this->ui.fileLocationLineEdit_2->setText(QString::fromStdString(this->userService.getFileName()));
        });
    QObject::connect(this->ui.deleteButton, &QPushButton::clicked, this, &ProperTrenchCoatShop::deleteTrenchCoat);
    QObject::connect(this->ui.addButton, &QPushButton::clicked, this, &ProperTrenchCoatShop::addTrenchCoat);
    QObject::connect(this->ui.updateButton, &QPushButton::clicked, this, &ProperTrenchCoatShop::updateTrenchCoat);
    QObject::connect(this->ui.undoButton, &QPushButton::clicked, this, &ProperTrenchCoatShop::undo);
    QObject::connect(this->ui.redoButton, &QPushButton::clicked, this, &ProperTrenchCoatShop::redo);
    QObject::connect(this->ui.updateFileLocationButton, &QPushButton::clicked, this, &ProperTrenchCoatShop::updateFileName);
    QObject::connect(this->ui.updateMyListLocationButton, &QPushButton::clicked, this, &ProperTrenchCoatShop::updateMyListLocation);
    QObject::connect(this->ui.sortBySizeButton, &QPushButton::clicked, this, &ProperTrenchCoatShop::sortBySize);
    QObject::connect(this->ui.saveToMyListButton, &QPushButton::clicked, this, &ProperTrenchCoatShop::addToBasket);
    QObject::connect(this->ui.openWatchListButton, &QPushButton::clicked, this, &ProperTrenchCoatShop::openMyList);
    QObject::connect(this->ui.nextButton, &QPushButton::clicked, this, &ProperTrenchCoatShop::nextTrenchCoat);
    QObject::connect(this->ui.adminButton, &QPushButton::clicked, this, &ProperTrenchCoatShop::modeA);
    QObject::connect(this->ui.userButton, &QPushButton::clicked, this, &ProperTrenchCoatShop::modeB);
    QObject::connect(this->ui.openMyListButton, &QPushButton::clicked, this, &ProperTrenchCoatShop::openMyListInNewWindow);
}


int ProperTrenchCoatShop::getSelectedIndex() const {
    QModelIndexList selectedIndexes = this->ui.movieListWidget->selectionModel()->selectedIndexes();
    if (selectedIndexes.size() == 0) {
        this->ui.IDLineEdit->clear();
        this->ui.sizeLineEdit->clear();
        this->ui.colourLineEdit->clear();
        this->ui.priceLineEdit->clear();
        this->ui.quantityLineEdit->clear();
        this->ui.photographyUrlLineEdit->clear();
        return -1;
    }

    int selectedIndex = selectedIndexes.at(0).row();
    return selectedIndex;
}

void ProperTrenchCoatShop::addTrenchCoat() {
    if (modeAOrB == 0) {
        QMessageBox::critical(this, "Error", "Mode Admin required");
        return;
    }
    std::string stringID = this->ui.IDLineEdit->text().toStdString();
    std::string stringSize = this->ui.sizeLineEdit->text().toStdString();
    std::string colour = this->ui.colourLineEdit->text().toStdString();
    std::string stringPrice = this->ui.priceLineEdit->text().toStdString();
    std::string stringQuantity = this->ui.quantityLineEdit->text().toStdString();
    std::string photographyUrl = this->ui.photographyUrlLineEdit->text().toStdString();

    int ID = stoi(stringID);
    int size = stoi(stringSize);
    int quantity = stoi(stringQuantity);
    float price = stof(stringPrice);
    TrenchCoat trenchCoatUsed{ ID , size, colour, price, quantity, photographyUrl };
    std::vector<TrenchCoat>movieList = this->adminService.adminGetTrenchCoatsList();
    if (std::find(movieList.begin(), movieList.end(), trenchCoatUsed) != movieList.end())
        try {
        //todo: quantity
        this->adminService.adminUpdateTrenchCoat(ID, size, colour, price, quantity, photographyUrl);
    }
    catch (std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    else
        try {
        this->adminService.adminAddTrenchCoat(ID, size, colour, price, quantity, photographyUrl);
    }
    catch (std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    this->populateList();

    int lastElem = this->adminService.adminGetTrenchCoatsList().size() - 1;
    this->ui.movieListWidget->setCurrentRow(lastElem);
}

void ProperTrenchCoatShop::updateTrenchCoat() {
    if (modeAOrB == 0) {
        QMessageBox::critical(this, "Error", "Mode Admin required");
        return;
    }
    int selectedIndex = this->getSelectedIndex();
    if (selectedIndex < 0) {
        QMessageBox::critical(this, "Error", "No movie selected!");
        return;
    }
    std::string stringID = this->ui.IDLineEdit->text().toStdString();
    std::string stringSize = this->ui.sizeLineEdit->text().toStdString();
    std::string colour = this->ui.colourLineEdit->text().toStdString();
    std::string stringPrice = this->ui.priceLineEdit->text().toStdString();
    std::string stringQuantity = this->ui.quantityLineEdit->text().toStdString();
    std::string photographyUrl = this->ui.photographyUrlLineEdit->text().toStdString();

    int ID = stoi(stringID);
    int size = stoi(stringSize);
    int quantity = stoi(stringQuantity);
    float price = stof(stringPrice);
    TrenchCoat trenchCoatUsed{ ID , size, colour, price, quantity, photographyUrl };
    std::vector<TrenchCoat>movieList = this->adminService.adminGetTrenchCoatsList();
    if (std::find(movieList.begin(), movieList.end(), trenchCoatUsed) != movieList.end())
        try {
        //todo: quantity
        this->adminService.adminUpdateTrenchCoat(ID, size, colour, price, quantity, photographyUrl);
    }
    catch (std::exception& e) {
        QMessageBox::critical(this, "Errorxx", e.what());
        return;
    }
    else {
        QMessageBox::critical(this, "Error", "No such movie in the list!");
    }

    this->populateList();

    int lastElem = this->adminService.adminGetTrenchCoatsList().size() - 1;
    this->ui.movieListWidget->setCurrentRow(lastElem);
}


void ProperTrenchCoatShop::deleteTrenchCoat() {
    if (modeAOrB == 0) {
        QMessageBox::critical(this, "Error", "Mode A required");
        return;
    }
    int selectedIndex = this->getSelectedIndex();
    if (selectedIndex < 0) {
        QMessageBox::critical(this, "Error", "No movie selected!");
        return;
    }
    int ID = this->adminService.adminGetTrenchCoatsList()[selectedIndex].getID();
    try {
        this->adminService.adminRemoveTrenchCoat(ID);
    }
    catch (std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }

    this->populateList();

    int lastElem = this->adminService.adminGetTrenchCoatsList().size() - 1;
    this->ui.movieListWidget->setCurrentRow(lastElem);

}

void ProperTrenchCoatShop::undo() {
    try {
        this->adminService.undo();
    }
    catch (std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    this->populateList();
    int lastElem = this->adminService.adminGetTrenchCoatsList().size() - 1;
    this->ui.movieListWidget->setCurrentRow(lastElem);
}

void ProperTrenchCoatShop::redo() {
    try {
        this->adminService.redo();
    }
    catch (std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    this->populateList();
    int lastElem = this->adminService.adminGetTrenchCoatsList().size() - 1;
    this->ui.movieListWidget->setCurrentRow(lastElem);

}

void ProperTrenchCoatShop::updateFileName() {
    std::string fileTitle = this->ui.fileLocationLineEdit->text().toStdString();
    try {
        this->adminService.changeRepositoryFileName(fileTitle);
    }
    catch (std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    this->populateList();
    int lastElem = this->adminService.adminGetTrenchCoatsList().size() - 1;
    this->ui.movieListWidget->setCurrentRow(lastElem);
}

void ProperTrenchCoatShop::sortBySize() {
    if (modeAOrB == 1) {
        QMessageBox::critical(this, "Error", "Mode User required");
        return;
    }
    std::string sizeGivenString = this->ui.sizeToSortByLineEdit->text().toStdString();
    int size = stoi(sizeGivenString);
    try {
        this->adminService.filterTrenchCoatsBySize(size);
    }
    catch (std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    this->populateList();
    int lastElem = this->adminService.adminGetTrenchCoatsList().size() - 1;
    this->ui.movieListWidget->setCurrentRow(lastElem);
}

void ProperTrenchCoatShop::updateMyListLocation() {
    std::string fileTitle = this->ui.fileLocationLineEdit_2->text().toStdString();
    try {
        std::vector<std::string> tokens = this->adminService.explode(fileTitle, '.');
        this->myListWidget.changeRepositoryFileName(tokens[0] + "." + tokens[1], tokens[1]);
    }
    catch (std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }
    this->populateList();
    int lastElem = this->adminService.adminGetTrenchCoatsList().size() - 1;
    this->ui.movieListWidget->setCurrentRow(lastElem);
    populateMyList();
}

void ProperTrenchCoatShop::addToBasket() {
    if (modeAOrB == 1) {
        QMessageBox::critical(this, "Error", "Mode User required");
        return;
    }
    std::string stringID = this->ui.IDLineEdit->text().toStdString();
    int ID = stoi(stringID);
    try {
        this->myListWidget.addInBasketList(ID);
    }
    catch (std::exception& e) {
        QMessageBox::critical(this, "Error", e.what());
        return;
    }

    populateMyList();
}

void ProperTrenchCoatShop::populateMyList() {
    this->ui.myListWidget->clear();
    if (this->userService.userGetBasketList().size() == 0)
        return;
    std::vector<TrenchCoat> allTrenchCoats = this->userService.userGetTrenchCoatList();
    for (TrenchCoat& movieUsed : allTrenchCoats)
        this->ui.myListWidget->addItem(QString::fromStdString(movieUsed.getOutputForm()));
    populateList();
}

void ProperTrenchCoatShop::openMyList() {
    if (modeAOrB == 1) {
        QMessageBox::critical(this, "Error", "Mode User required");
        return;
    }
    std::string command;
    if (userService.isRepositoryCSV())
        command = "open -a 'Numbers.app' " + userService.getFileName();
    if (userService.isRepositoryHTML())
        command = "open -a 'Google Chrome.app' " + userService.getFileName();
    if (userService.isRepositoryCSV() || userService.isRepositoryHTML())
        system(command.c_str());
}

void ProperTrenchCoatShop::nextTrenchCoat() {
    if (modeAOrB == 1) {
        QMessageBox::critical(this, "Error", "Mode User required");
        return;
    }
    int lastElem = this->getSelectedIndex();
    if (this->adminService.adminGetTrenchCoatsList().size() == 0) {
        QMessageBox::critical(this, "Error", "No movies in the list");
        return;
    }
    if (lastElem + 1 == this->adminService.adminGetTrenchCoatsList().size())
        lastElem = -1;
    this->ui.movieListWidget->setCurrentRow(lastElem + 1);
}

void ProperTrenchCoatShop::openMyListInNewWindow()
{
    myListWidget.show();
}
