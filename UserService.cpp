#include "UserService.h"
#include <iostream>

UserService::UserService(FileRepository *repository, int currentTrenchCoatPosition, std::string fileName, std::string repositoryType) :  currentTrenchCoatPosition{ currentTrenchCoatPosition }, currentTrenchCoatsBySize{ repository->getAllTrenchCoats() }, repositoryType{ repositoryType }{
    this->repository = repository;
    repository->changeRepositoryType(repositoryType);
}

/*
* Methid for getting the list with all the trench coats in user mode
*/
std::vector<TrenchCoat> UserService::userGetTrenchCoatList()
{
    return repository->getAllTrenchCoats();
}

/*
* Methid for getting the basket list in user mode
*/
std::vector<TrenchCoat> UserService::userGetBasketList()
{
    return repository->getBasketList();
}

/*
* Method for getting the list containg the trench coats with a given size
*/
int UserService::listTrenchCoatsBySize(const int size)
{
    currentTrenchCoatsBySize = repository->getTrenchCoatsBySize(size);
    if (currentTrenchCoatsBySize.size() == 0)
        throw ValidationException("No trench coat with this size");
    currentTrenchCoatPosition = 0;
    return 1;
}

/*
* Method for deleting a trench coat from the list after is added to the basket list
*/
int UserService::deleteTrenchCoatFromList()
{
	auto iteratorWhereTrenchIsFound = std::find(currentTrenchCoatsBySize.begin(), currentTrenchCoatsBySize.end(), currentTrenchCoatsBySize[currentTrenchCoatPosition]);
	/*if (iteratorWhereTrenchIsFound == currentTrenchCoatsBySize.end())
		return -1;*/
	currentTrenchCoatsBySize.erase(iteratorWhereTrenchIsFound);
	currentTrenchCoatPosition--;
	return 1;
}

/*
* Method for adding a trench coat into the basket list
*/
int UserService::addTrenchCoatToBasketList()
{
    //std::cout << currentTrenchCoatsBySize[currentTrenchCoatPosition];
    //if(currentTrenchCoatPosition < currentTrenchCoatsBySize.size())
    return repository->addTrenchCoatToBasketList(currentTrenchCoatsBySize[currentTrenchCoatPosition]);
}

int UserService::addTrenchCoatToBasketListByID(const int ID)
{
    return repository->addTrenchCoatToBasketByID(ID);
}

/*
* Method for going to the next trench coat in the list
*/
void UserService::goToNextTrenchCoatBySize()
{
    currentTrenchCoatPosition++;
    if (currentTrenchCoatPosition == currentTrenchCoatsBySize.size())
        currentTrenchCoatPosition = 0;
}

/*
* Method for getting the current trench coat
*/
TrenchCoat UserService::getCurrentTrenchCoat()
{
    return currentTrenchCoatsBySize[currentTrenchCoatPosition];
}

//const std::vector<std::string> UserService::explode(const std::string& stringToExplode, const char& separatorUsed)
//{
//	std::string partialStringObtained{ "" };
//	std::vector<std::string> explodedString;
//
//	for (auto iterator : stringToExplode)
//	{
//		if (iterator != separatorUsed)
//			partialStringObtained += iterator;
//		else
//			if (iterator == separatorUsed && partialStringObtained != "") {
//				explodedString.push_back(partialStringObtained);
//				partialStringObtained = "";
//			}
//	}
//	if (partialStringObtained != "")
//		explodedString.push_back(partialStringObtained);
//	return explodedString;
//}

/*
* Method for getting the total price of the products in the basket list
*/
double UserService::getTotalSumOfProducts()
{
	double totalSum = 0;
	std::vector<TrenchCoat>basketList = userGetBasketList();
	for (int i = 0; i < basketList.size(); i++)
		totalSum += basketList[i].getPrice();
	return totalSum;
}

int UserService::changeRepositoryFileName(const std::string& nameOfTheFileUsed, const std::string& extensionToChangeWith)
{
    if (extensionToChangeWith != "txt" && extensionToChangeWith != "html" && extensionToChangeWith != "csv")
        throw ValidationException("Invalid extension provided");
    repositoryType = extensionToChangeWith;
    repository->changeUserFileName(nameOfTheFileUsed);
    repository->changeRepositoryType(extensionToChangeWith);
    updateRepositoryType(repositoryType == "csv", nameOfTheFileUsed, repository->getTrenchCoatFileName());
    return 1;
}


bool UserService::isRepositoryCSV() const {
    return repositoryType == "csv";
}

bool UserService::isRepositoryHTML() const {
    return repositoryType == "html";
}

std::string UserService::getFileName() const {
    return repository->getUserFileName();
}

void UserService::updateRepositoryType(bool csvOrHTML, std::string fileName, std::string trenchCoatFileName) {
    std::vector<TrenchCoat> basketList = repository->getBasketList();
    FileRepository* correctRepository;
    delete this->repository;
    if (csvOrHTML == 1)
        correctRepository = new CSVRepository{ fileName, trenchCoatFileName };
    else
        correctRepository = new HTMLRepository{ fileName, trenchCoatFileName };
    this->repository = correctRepository;
    for (const TrenchCoat& trenchCoatUsed : basketList) {
        repository->addTrenchCoatToBasketList(trenchCoatUsed);
    }

};

void UserService::filterTrenchCoatsBySize(const int& size) {
    repository->filterTrenchCoatsBySize(size);
}
