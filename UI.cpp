//#include "UI.h"
//#include "Service.h"
//#include <iostream>
//#include <exception>
//#include <string>
//#include "TrenchCoatValidator.h"
//#include "RepositoryExceptions.h"
//#include <Windows.h>
//#include <shellapi.h>
//
///*
//* UI Class
//*/
//UI::UI(Service& service) : service { service } {}
//
//void UI::printMenu()
//{
//    std::cout << "\n";
//    std::cout << "Welcome to 'Proper Trench Coats'!\n";
//    std::cout << "Please select one of the following options:\n";
//    std::cout << "\t1.Continue as administrator\n";
//    std::cout << "\t2.Continue as user\n";
//    std::cout << "\t3.Exit\n";
//    std::cout << "\n";
//}
//
//
///*
//* Method for printing the menu
//*/
//void UI::printMenuAdmin()
//{
//    std::cout << "\n";
//    std::cout << "Please select one of the following options:\n";
//    std::cout << "\t1.Add a trench coat\n";
//    std::cout << "\t2.Delete a trench coat\n";
//    std::cout << "\t3.Update a trench coat\n";
//    std::cout << "\t4.List all available trench coats\n";
//    std::cout << "\t5.Change the mode\n";
//    std::cout << "\t6.Exit\n";
//    std::cout << "\n";
//}
//
//void UI::printMenuUser()
//{
//    std::cout << "\n";
//    std::cout << "Please select one of the following options:\n";
//    std::cout << "\t1.List all available trench coats by size\n";
//    std::cout << "\t2.List the basket list\n";
//    std::cout << "\t3.Change the mode\n";
//    std::cout << "\t4.Exit\n";
//    std::cout << "\n";
//}
//
//void UI::runMenu()
//{
//    std::string consoleInput = "";
//    while (1) {
//        printMenu();
//        std::cout << "Choose mode: ";
//        std::cin >> consoleInput;
//        if (consoleInput == "admin")
//            runAdmin();
//        else if (consoleInput == "user")
//            runUser();
//        else if (consoleInput == "exit")
//        {
//            std::cout << "You exited the application!\n";
//            break;
//        }
//        else
//            std::cout << "Invalid input! \n";
//    }
//}
//
//
///*
//* Method for creating the menu in admin form
//*/
//void UI::runAdmin()
//{
//    std::string consoleInput = "";
//    int changeMode = 0;
//    while (!changeMode) {
//        printMenuAdmin();
//        std::cout << "Option: ";
//        std::cin >> consoleInput;
//        if (consoleInput == "add")
//            uiAdminAdd();
//        else if (consoleInput == "update")
//            uiAdminUpdate();
//        else if (consoleInput == "delete")
//            uiAdminDelete();
//        else if (consoleInput == "list")
//            uiAdminList();
//        else if (consoleInput == "mode") {
//            std::cout << "Choose mode: ";
//            std::cin >> consoleInput;
//            if (consoleInput == "user") {
//                changeMode = 1;
//                runUser();
//            }
//            else
//            {
//                if (consoleInput == "admin")
//                    continue;
//                else
//                    std::cout << "Invalid input! \n";
//            }
//        }
//        else if (consoleInput == "exit")
//            break;
//        else
//            std::cout << "Invalid input! \n";
//    }
//}
//
///*
//* Method for creating the menu in user form
//*/
//void UI::runUser()
//{
//    try {
//        service.listTrenchCoatsBySize(0);
//    }
//    catch (std::exception& exception) {
//        std::cout << exception.what() << '\n';
//    }
//    TrenchCoat currentTrenchCoat;
//    std::string consoleInput = "";
//    int changeMode = 0;
//    int inAListLoop = 0;
//    std::cout << "Please select the extension for the file: \n";
//    uiUserChangeFile();
//    while (!changeMode && !inAListLoop) {
//        printMenuUser();
//        std::cout << "Option: ";
//        std::cin >> consoleInput;
//        if (consoleInput == "list")
//        {
//            inAListLoop = 1;
//            uiUserList();
//            inAListLoop = 0;
//        }
//        else if (consoleInput == "next")
//        {
//            currentTrenchCoat = basket.getCurrentTrenchCoat();
//            std::cout << "ID: " << currentTrenchCoat.getID() << ", Size: " << currentTrenchCoat.getSize() << ", Colour: " << currentTrenchCoat.getColour() << ", Price: " << currentTrenchCoat.getPrice() << ", Quantity: " << currentTrenchCoat.getQuantity() << ", Photography Link: " << currentTrenchCoat.getPhotographyUrl() << '\n';
//            uiUserNext();
//        }
//        else if (consoleInput == "basket")
//        {
//            uiUserBasketList();
//        }
//        else if (consoleInput == "mode") {
//            std::cout << "Choose mode: ";
//            std::cin >> consoleInput;
//            if (consoleInput == "admin") {
//                changeMode = 1;
//                runAdmin();
//            }
//            else
//            {
//                if (consoleInput == "user")
//                    continue;
//                else
//                    std::cout << "Invalid input! \n";
//            }
//        }
//        else if (consoleInput == "exit")
//            break;
//        else
//            std::cout << "Invalid input! \n";
//    }
//}
//
///*
//* Method for adding an element in admin form
//*/
//void UI::uiAdminAdd()
//{
//    std::string colour, photographyUrl, consoleInput;
//    int size, quantity, ID = 10;
//    double price;
//
//    std::vector<TrenchCoat> listOfTrenchCoats = service.getTrenchCoatsList();
//    ID = (int)listOfTrenchCoats.size() + 1;
//    int ok = 1;
//
//    std::cout << "Size: ";
//    std::cin >> consoleInput;
//    for (auto character : consoleInput)
//    {
//        if (isdigit(character) == 0)
//            ok = 0;
//    }
//    if (ok == 1)
//        size = stoi(consoleInput);
//
//    std::cout << "Colour: ";
//    std::cin >> consoleInput;
//    colour = consoleInput;
//
//    std::cout << "Price: ";
//    std::cin >> consoleInput;
//    for (auto character : consoleInput)
//    {
//        if (isdigit(character) == 0 || character == '.')
//            ok = 0;
//    }
//    if (ok == 1)
//        price = stod(consoleInput);
//
//    std::cout << "Quantity: ";
//    std::cin >> consoleInput;
//    for (auto character : consoleInput)
//    {
//        if (isdigit(character) == 0)
//            ok = 0;
//    }
//    if (ok == 1)
//        quantity = stoi(consoleInput);
//
//    std::cout << "Photography link: ";
//    std::cin >> consoleInput;
//    photographyUrl = consoleInput;
//
//    if (ok == 1)
//    {
//
//        try {
//            this->service.addTrenchCoatToRepository(ID, size, colour, price, quantity, photographyUrl);
//            std::cout << "Trench added successfully!\n";
//        }
//        catch (ValidationException& e)
//        {
//            for (auto trenchCoatE : e.getErrors())
//                std::cout << trenchCoatE;
//        }
//        catch (RepositoryException& e)
//        {
//            std::cout << e.what() << '\n';
//        }
//        catch (FileException& e)
//        {
//            std::cout << e.what() << '\n';
//        }
//    }
//    else
//        std::cout << "Please insert a valid input\n";
//}
//
///*
//* Method for removing an element in admin form
//*/
//void UI::uiAdminDelete()
//{
//    std::string consoleInput;
//    int ID, ok = 1;
//    std::cout << "ID: ";
//    std::cin >> consoleInput;
//    for (auto character : consoleInput)
//    {
//        if (isdigit(character) == 0)
//            ok = 0;
//    }
//    if (ok == 1)
//        ID = stoi(consoleInput);
//    if (ok == 1)
//    {
//        try {
//            this->service.removeTrenchCoatFromRepository(ID);
//            std::cout << "Trench coat deleted successfully!\n";
//        }
//        catch (std::exception& exception)
//        {
//            std::cout << exception.what() << '\n';
//        }
//    }
//    else
//        std::cout << "Please insert a valid input\n";
//}
//
///*
//* Method for updating an element in admin form
//*/
//void UI::uiAdminUpdate()
//{
//    std::string colour, photographyUrl, consoleInput;
//    int size, quantity, ID = 0;
//    double price;
//    int ok = 1;
//    std::cout << "ID: ";
//    std::cin >> consoleInput;
//    for (auto character : consoleInput)
//    {
//        if (isdigit(character) == 0)
//            ok = 0;
//    }
//    if (ok == 1)
//        ID = stoi(consoleInput);
//
//    std::cout << "Size: ";
//    std::cin >> consoleInput;
//    for (auto character : consoleInput)
//    {
//        if (isdigit(character) == 0)
//            ok = 0;
//    }
//    if (ok == 1)
//        size = stoi(consoleInput);
//
//    std::cout << "Colour: ";
//    std::cin >> consoleInput;
//    colour = consoleInput;
//
//    std::cout << "Price: ";
//    std::cin >> consoleInput;
//    for (auto character : consoleInput)
//    {
//        if (isdigit(character) == 0 || character == '.')
//            ok = 0;
//    }
//    if (ok == 1)
//        price = stod(consoleInput);
//
//    std::cout << "Quantity: ";
//    std::cin >> consoleInput;
//    for (auto character : consoleInput)
//    {
//        if (isdigit(character) == 0)
//            ok = 0;
//    }
//    if (ok == 1)
//        quantity = stoi(consoleInput);
//
//    std::cout << "Photography link: ";
//    std::cin >> consoleInput;
//    photographyUrl = consoleInput;
//
//    if (ok == 1)
//    {
//        try {
//            this->service.updateTrenchCoatToRepository(ID, size, colour, price, quantity, photographyUrl);
//            std::cout << "Trench updated successfully!\n";
//        }
//        catch (std::exception& exception)
//        {
//            std::cout << exception.what() << '\n';
//        }
//    }
//    else
//        std::cout << "Please insert a valid input\n";
//
//}
//
///*
//* Method for printing the elements list
//*/
//void UI::uiAdminList()
//{
//    std::vector<TrenchCoat> listOfTrenchCoats = this->service.getTrenchCoatsList();
//    if (listOfTrenchCoats.size() == 0)
//        std::cout << "There is no trench coat in the list. \n";
//    else
//    {
//        std::cout << "There are " << listOfTrenchCoats.size() << " trench coats in the list. \n";
//        for (const TrenchCoat& trenchCoat : listOfTrenchCoats)
//            std::cout << "ID: " << trenchCoat.getID() << ", Size: " << trenchCoat.getSize() << ", Colour: " << trenchCoat.getColour() << ", Price: " << trenchCoat.getPrice() << ", Quantity: " << trenchCoat.getQuantity() << ", Photography Link: " << trenchCoat.getPhotographyUrl() << '\n';
//    }
//}
//
//void UI::uiUserAdd()
//{
//    /*int isFunctionSuccessful = userService.addTrenchCoatToBasketList();
//    if(isFunctionSuccessful == -1)
//        userService.deleteTrenchCoatFromList();*/
//    try {
//        userService.addTrenchCoatToBasketList();
//    }
//    catch (std::exception& exception)
//    {
//        std::cout << exception.what() << '\n';
//    }
//    /*if (isFunctionSuccessful == -1)
//        std::cout << "You cannot add this item to the basket!\n";*/
//}
//
//void UI::uiUserBasketList()
//{
//    std::string command;
//    if (userService.isRepositoryCSV())
//        ShellExecuteA(NULL, NULL, "notepad++.exe", userService.getFileName().c_str(), NULL, SW_SHOWMAXIMIZED);
//    if (userService.isRepositoryHTML())
//        //command = "open -a 'Google Chrome.app' " + userService.getFileName();
//        ShellExecuteA(NULL, NULL, "microsoftedge.exe", "file:///D:/Fuckulta_2.0_(Babes)/An%201/Sem%202/Object%20Oriented%20Programming/Laboratory/Assignment8-9/Assignment8-9/Assignment8-9/file.html", NULL, SW_SHOWMAXIMIZED);
//    //std::cout << userService.getFileName().c_str();
//    //std::cout << userService.getFileName() << '\n';
//   // system(command.c_str());
//    //ShellExecuteA(NULL, NULL, "chrome.exe", userService.fileName.c_str(), NULL, SW_SHOWMAXIMIZED);
//}
//
//void UI::uiUserNext()
//{
//    userService.goToNextTrenchCoatBySize();
//}
//
//
//void UI::uiUserList()
//{
//    std::string consoleInput = "";
//    int size = 0;
//    TrenchCoat currentTrenchCoat;
//
//    int ok = 1;
//
//    std::cout << "Size (if doesn't matter, put '-'): ";
//    std::cin >> consoleInput;
//    if (consoleInput == "-")
//    {
//        size = 0;
//    }
//    else {
//        for (auto character : consoleInput)
//        {
//            if (isdigit(character) == 0)
//                ok = 0;
//        }
//        if (ok == 1)
//            size = stoi(consoleInput);
//
//    }
//
//    if (ok == 0)
//        std::cout << "Invalid input!\n";
//    else
//    {
//        int isFunctionSuccessful = userService.listTrenchCoatsBySize(size);
//        if (isFunctionSuccessful == -1)
//            std::cout << "No trench coats with this size!\n";
//
//        while (isFunctionSuccessful != -1) {
//            try {
//                currentTrenchCoat = userService.getCurrentTrenchCoat();
//            }
//            catch (std::exception& Exception) {
//                std::cout << Exception.what() << '\n';
//            }
//            std::string op = std::string("start ").append(currentTrenchCoat.getPhotographyUrl());
//            std::cout << "\nID: " << currentTrenchCoat.getID() << ", Size: " << currentTrenchCoat.getSize() << ", Colour: " << currentTrenchCoat.getColour() << ", Price: " << currentTrenchCoat.getPrice() << ", Quantity: " << currentTrenchCoat.getQuantity() << ", Photography Link: " << system(op.c_str()) << '\n';
//            std::cout << "\nSelect if you want to add the product to the basket or go to the next element:\n ";
//            std::cout << "Option: ";
//            std::cin >> consoleInput;
//            if (consoleInput == "add") {
//                uiUserAdd();
//                double totalSum = userService.getTotalSumOfProducts();
//                int adminFunction = adminService.checkStock();
//                std::cout << "\nTotal sum: " << totalSum << "\n";
//                isFunctionSuccessful = userService.listTrenchCoatsBySize(size);
//                currentTrenchCoat = userService.getCurrentTrenchCoat();
//                if (userService.getCurrentListLength() == 0)
//                {
//                    std::cout << "There are no more trench coats with this size.\n";
//                    break;
//                }
//
//                else
//                    uiUserNext();
//            }
//            else if (consoleInput == "next")
//            {
//                if (userService.getCurrentListLength() == 0)
//                {
//                    std::cout << "There are no more trench coats with this size.\n";
//                    break;
//                }
//                else
//                    uiUserNext();
//            }
//            else if (consoleInput == "exit")
//                break;
//            else
//                std::cout << "Invalid option\n";
//        }
//    }
//}
//
//
//void UI::uiUserChangeFile()
//{
//    std::string file = "file", extensionFile;
//    std::cout << "Extension: ";
//    std::cin >> extensionFile;
//    //std::cout << "File name: ";
//    //std::getline(std::cin, consoleInput, '.');
//    //std::cout << consoleInput;
//    file += '.' + extensionFile;
//    //std::cout << file;
//    try {
//        service.changeFileExtension(file, extensionFile);
//    }
//    catch (std::exception& exception) {
//        std::cout << exception.what() << '\n';
//    }
//
//}
