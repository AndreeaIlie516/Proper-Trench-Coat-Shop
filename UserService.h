#pragma once
#include "FileRepository.h"
#include "CSVRepository.h"
#include "HTMLRepository.h"
#include "ValidationException.h"


/*
* UserService class, containing repository <Repository>, currentTrenchCoatBySize <TrenchCoat>, currentTrenchCoatPosition <int>
*/
class UserService
{
private:
	FileRepository *repository;
	std::vector<TrenchCoat> currentTrenchCoatsBySize;
	int currentTrenchCoatPosition;
    std::string repositoryType;
    std::string fileName;

public:
    UserService(FileRepository *repository, int currentTrenchCoatPosition = 0, std::string fileName = "",
        std::string repositoryType = "txt");
    
    std::vector<TrenchCoat> userGetTrenchCoatList();
    std::vector<TrenchCoat> userGetBasketList();
    
    int listTrenchCoatsBySize(const int givenSize);
    int addTrenchCoatToBasketList();
    int addTrenchCoatToBasketListByID(const int ID);
    
    void goToNextTrenchCoatBySize();
    TrenchCoat getCurrentTrenchCoat();
    size_t getCurrentListLength() const { return currentTrenchCoatsBySize.size(); };
    size_t getBasketListLength() const { return repository->getBasketListLength(); };

    //const std::vector<std::string> explode(const std::string& stringToExplode, const char& separatorUsed);
    double getTotalSumOfProducts();
    int deleteTrenchCoatFromList();

    int changeRepositoryFileName(const std::string& nameOfTheFileUsed, const std::string& extensionToChange);

    bool isRepositoryCSV() const;

    bool isRepositoryHTML() const;

    std::string getFileName() const;

    void updateRepositoryType(bool csvOrHTML, std::string fileName, std::string movieFileName);

    void filterTrenchCoatsBySize(const int& size);

    FileRepository* getRepo() { return repository; }
};


