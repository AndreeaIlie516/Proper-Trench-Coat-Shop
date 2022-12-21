#pragma once

#include "TrenchCoat.h"
#include "RepositoryException.h"
#include <vector>
#include <algorithm>

class FileRepository
{
protected:
	std::vector<TrenchCoat> userBasketList;
	std::string trenchCoatFileName;
	std::string userFileName;
	std::string repositoryType;

public:
	FileRepository(const std::string& nameOfTheFileUsed = "", std::string repositoryType = "txt");
	~FileRepository();

	std::vector<TrenchCoat> loadTrenchCoatsFromFile();
	void writeTrenchCoatsToFile(std::vector<TrenchCoat> trenchCoatList, std::string trenchCoatFileName);
	virtual void writeBasketListToFile(std::vector<TrenchCoat> trenchCoatList, std::string trenchCoatFileName);


	int addTrenchCoat(const TrenchCoat& trenchCoatToAdd);
	TrenchCoat findTrenchCoat(const int& ID);
	int removeTrenchCoat(const TrenchCoat& trenchCoatToRemove);
	int updateTrenchCoat(const TrenchCoat& trenchCoatToUpdate, const TrenchCoat& trenchCoatToUpdateWith);
	
	size_t getTrenchCoatListLength();
	TrenchCoat getTrenchCoatAtPosition(int positionOfTrenchCoat);
	std::vector<TrenchCoat> getAllTrenchCoats();
	std::vector<TrenchCoat> getTrenchCoatsBySize(const int givenSize);
	virtual std::vector<TrenchCoat> getBasketList();
	
	virtual int addTrenchCoatToBasketList(const TrenchCoat& trenchCoatToAdd);
	virtual int addTrenchCoatToBasketByID(const int& IDOfTheTrenchCoatToAdd);
	virtual void deleteTrenchCoatFromBasketlist(const TrenchCoat& TrenchCoatToDelete);
	
	virtual size_t getBasketListLength() { return userBasketList.size(); };



	void changeFileName(const std::string& nameOfTheFileUsed = "");
	void changeUserFileName(const std::string& nameOfTheFileUsed = "");
	void changeRepositoryType(std::string repositoryTypeGiven);
	std::string getUserFileName();
	std::string getTrenchCoatFileName();

	const std::vector<std::string>explode(const std::string& stringToExplode, const std::string& separatorsUsed);

	void filterTrenchCoatsBySize(const int& size);
};

