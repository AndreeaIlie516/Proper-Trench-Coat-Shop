#include "CSVRepository.h"
#include <iostream>

void CSVRepository::writeBasketListToFile(std::vector<TrenchCoat> trenchCoatList, std::string trenchCoatFileName) {
    std::ofstream fileOutput(trenchCoatFileName);
   // fileOutput << "ID, Size, Colour, Price, PhotographyUrl\n";
    if (trenchCoatList.empty())
        return;
    for (const TrenchCoat& trenchCoatUsed : trenchCoatList) {
        fileOutput << '"' << trenchCoatUsed.getID() << "\","
            << '"' << trenchCoatUsed.getSize() << "\","
            << '"' << trenchCoatUsed.getColour() << "\","
            << '"' << trenchCoatUsed.getPrice() << "\","
            << '"' << trenchCoatUsed.getPhotographyUrl() << '"' << '\n';
    }
   // fileOutput << "Total sum: " << totalSum << "\n";
    fileOutput.close();
}

std::vector<TrenchCoat> CSVRepository::getBasketList() {
    std::vector<TrenchCoat> trenchCoatList;
    std::vector<std::string> tokenizedInput;
    std::string textLineFromFile, replaceString;
    std::ifstream fileInput(userFileName);
    while (!fileInput.eof()) {
        getline(fileInput, textLineFromFile);
        tokenizedInput = explode(textLineFromFile, "\"");
        //std::cout << tokenizedInput[0] << ' ' << tokenizedInput[1] << ' ' << tokenizedInput[2] << ' ' << tokenizedInput[3] << ' ';
        if (tokenizedInput.size() > 0) {
            TrenchCoat trenchCoatUsed = { stoi(tokenizedInput[0]), stoi(tokenizedInput[2]), tokenizedInput[4], stof(tokenizedInput[6]), 1 , tokenizedInput[8] };
            trenchCoatList.push_back(trenchCoatUsed);
        }
    }
    return trenchCoatList;
}

int CSVRepository::addTrenchCoatToBasketList(const TrenchCoat& trenchCoatToAdd)
{
    std::vector<TrenchCoat> basketListFromFile = getBasketList();

    std::vector<TrenchCoat> trenchCoatList = loadTrenchCoatsFromFile();
    auto iteratorWhereTrenchCoatIsFound = std::find(basketListFromFile.begin(), basketListFromFile.end(), trenchCoatToAdd);
    auto iteratorWhereTrenchCoatIsFoundInList = std::find(userBasketList.begin(), userBasketList.end(), trenchCoatToAdd);
    int quantity = trenchCoatToAdd.getQuantity();
    TrenchCoat trenchCoatToUpdateWith = trenchCoatToAdd;

    if (iteratorWhereTrenchCoatIsFoundInList != userBasketList.end())
    {
        int quantity = trenchCoatToAdd.getQuantity();
        TrenchCoat trenchCoatToUpdateWith = trenchCoatToAdd;
        if (quantity >= 1)
        {
            trenchCoatToUpdateWith.setQuantity(quantity - 1);
            updateTrenchCoat(trenchCoatToAdd, trenchCoatToUpdateWith);
            basketListFromFile.push_back(trenchCoatToAdd);
            return 0;
        }
    }
    else {
        int quantity = trenchCoatToAdd.getQuantity();
        TrenchCoat trenchCoatToUpdateWith = trenchCoatToAdd;
        if (quantity >= 1)
        {
            trenchCoatToUpdateWith.setQuantity(quantity - 1);
            updateTrenchCoat(trenchCoatToAdd, trenchCoatToUpdateWith);
            basketListFromFile.push_back(trenchCoatToAdd);
        }
    }

    writeBasketListToFile(basketListFromFile, userFileName);
    return 1;
}

void CSVRepository::deleteTrenchCoatFromBasketlist(const TrenchCoat& TrenchCoatToDelete)
{
    std::vector<TrenchCoat> basketListFromFile = getBasketList();
    auto iteratorWhereTrenchCoatIsFound = std::find(basketListFromFile.begin(), basketListFromFile.end(), TrenchCoatToDelete);
    if (iteratorWhereTrenchCoatIsFound == basketListFromFile.end())
        throw RepositoryException(std::string("Trench coat not in the basket"));
    basketListFromFile.erase(iteratorWhereTrenchCoatIsFound);
    writeTrenchCoatsToFile(basketListFromFile, userFileName);
}

size_t CSVRepository::getBasketListLength()
{
    std::vector<TrenchCoat>basketListFromFile = getBasketList();
    return basketListFromFile.size();
}

int CSVRepository::addTrenchCoatToBasketByID(const int& IDOfTheTrenchCoatToAdd)
{
    std::vector<TrenchCoat> trenchCoatList = loadTrenchCoatsFromFile();
    auto iteratorWhereTrenchCoatIsFound = std::find_if(trenchCoatList.begin(), trenchCoatList.end(), [&IDOfTheTrenchCoatToAdd](const TrenchCoat& trenchCoat) {return trenchCoat.getID() == IDOfTheTrenchCoatToAdd; });
    if (iteratorWhereTrenchCoatIsFound == trenchCoatList.end())
        throw RepositoryException(std::
            string("The trench coat with this ID  does not exist."));
    addTrenchCoatToBasketList(*iteratorWhereTrenchCoatIsFound);
    return 1;
}
