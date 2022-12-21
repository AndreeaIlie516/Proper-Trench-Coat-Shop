#include <QtWidgets/QApplication>
#include <QLabel>
#include <memory>
#include "UserService.h"
#include "AdminService.h"
#include "ProperTrenchCoatShop.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include "MyListWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::unique_ptr<FileRepository> repository = std::make_unique<FileRepository>("inputFile.txt");
    
    AdminService adminservice{ repository.get() };
    UserService userservice{ repository.get() };

    std::unique_ptr<MyListTableModel> model = std::make_unique<MyListTableModel>(userservice);
    
    MyListWidget myListWidget{ model.get() };
    ProperTrenchCoatShop gui{ adminservice, userservice, myListWidget };
    gui.show();

    return a.exec();
}