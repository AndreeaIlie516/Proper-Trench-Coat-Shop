#include "HTMLRepository.h"
#include <iostream>
#include <Windows.h>
#include <shellapi.h>

void HTMLRepository::writeBasketListToFile(std::vector<TrenchCoat> trenchCoatList, std::string trenchCoatFileName) {
    std::ofstream fileOutput(trenchCoatFileName);
    fileOutput << "<!DOCTYPE html>\n<html><head><title>Basket List</title></head><body>\n";
    fileOutput << "<table border=\"1\">\n";
    fileOutput
        << "<tr><td>ID</td><td>Size</td><td>Colour</td><td>Price</td><td>Photography Url</td></tr>\n";
    for (const TrenchCoat& trenchCoatUsed : trenchCoatList) {
        fileOutput << "<tr><td>" << trenchCoatUsed.getID() << "</td>"
            << "<td>" << trenchCoatUsed.getSize() << "</td>"
            << "<td>" << trenchCoatUsed.getColour() << "</td>"
            << "<td>" << trenchCoatUsed.getPrice() << "</td>"
            << "<td><a href=\"" << trenchCoatUsed.getPhotographyUrl() << "\">" << trenchCoatUsed.getPhotographyUrl() << "</a></td>" << '\n';
    }
    fileOutput << "</table></body></html>";
    //fileOutput << "<h2>Total sum:</h2>" << totalSum << "/br";
    fileOutput.close();
}

std::vector<TrenchCoat> HTMLRepository::getBasketList() {
    std::vector<TrenchCoat> trenchCoatList;
    std::vector<std::string> tokenizedInput;
    std::string textLineFromFile, replacedString;
    std::regex tags("<.*?>");
    std::ifstream fileInput(userFileName);
    getline(fileInput, textLineFromFile);
    if (textLineFromFile == "")
        return trenchCoatList;
    getline(fileInput, textLineFromFile);
    getline(fileInput, textLineFromFile);
    getline(fileInput, textLineFromFile);
    while (!fileInput.eof()) {
        getline(fileInput, textLineFromFile);
        std::regex_replace(std::back_inserter(replacedString), textLineFromFile.begin(), textLineFromFile.end(), tags, " ");
        textLineFromFile = replacedString;
        replacedString.clear();
        tokenizedInput = explode(textLineFromFile, " ");
        if (tokenizedInput.size() > 0) {
            TrenchCoat trenchCoatUsed = { stoi(tokenizedInput[0]), stoi(tokenizedInput[1]), tokenizedInput[2], stof(tokenizedInput[3]), 1, tokenizedInput[4] };
            trenchCoatList.push_back(trenchCoatUsed);
        }
    }
    return trenchCoatList;
}


int HTMLRepository::addTrenchCoatToBasketList(const TrenchCoat& trenchCoatToAdd)
{
    std::vector<TrenchCoat> basketListFromFile = getBasketList();

    std::vector<TrenchCoat> trenchCoatList = loadTrenchCoatsFromFile();
    auto iteratorWhereTrenchCoatIsFound = std::find(basketListFromFile.begin(), basketListFromFile.end(), trenchCoatToAdd);
   
    auto iteratorWhereTrenchCoatIsFoundInList = std::find(userBasketList.begin(), userBasketList.end(), trenchCoatToAdd);
    int quantity = trenchCoatToAdd.getQuantity();
    TrenchCoat trenchCoatToUpdateWith = trenchCoatToAdd;
    //basketListFromFile.push_back(trenchCoatToAdd);

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

int HTMLRepository::addTrenchCoatToBasketByID(const int& IDOfTheTrenchCoatToAdd)
{
    std::vector<TrenchCoat> trenchCoatList = loadTrenchCoatsFromFile();
    auto iteratorWhereTrenchCoatIsFound = std::find_if(trenchCoatList.begin(), trenchCoatList.end(), [&IDOfTheTrenchCoatToAdd](const TrenchCoat& trenchCoat) {return trenchCoat.getID() == IDOfTheTrenchCoatToAdd; });
    if (iteratorWhereTrenchCoatIsFound == trenchCoatList.end())
        throw RepositoryException(std::
            string("The trench coat with this ID  does not exist."));
    addTrenchCoatToBasketList(*iteratorWhereTrenchCoatIsFound);
    return 1;
}

void HTMLRepository::deleteTrenchCoatFromBasketlist(const TrenchCoat& TrenchCoatToDelete)
{
    std::vector<TrenchCoat> basketListFromFile = getBasketList();
    auto iteratorWhereTrenchCoatIsFound = std::find(basketListFromFile.begin(), basketListFromFile.end(), TrenchCoatToDelete);
    if (iteratorWhereTrenchCoatIsFound == basketListFromFile.end())
        throw RepositoryException(std::string("Trench coat not in the basket"));
    basketListFromFile.erase(iteratorWhereTrenchCoatIsFound);
    writeTrenchCoatsToFile(basketListFromFile, userFileName);
}

size_t HTMLRepository::getBasketListLength()
{
    std::vector<TrenchCoat>basketListFromFile = getBasketList();
    return basketListFromFile.size();
}
