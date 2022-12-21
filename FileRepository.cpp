#include "FileRepository.h"
#include <iostream>
#include <fstream>

FileRepository::FileRepository(const std::string& nameOfTheFileUsed, std::string repositoryType)
{
	trenchCoatFileName = nameOfTheFileUsed;
	repositoryType = repositoryType;
}


FileRepository::~FileRepository()
{
}


std::vector<TrenchCoat> FileRepository::loadTrenchCoatsFromFile()
{
	std::vector<TrenchCoat> trenchCoatList = {};
	if (trenchCoatFileName == "")
		throw RepositoryException(std::string("Invalid file name"));
	TrenchCoat trenchCoatLoadedFromFile;
	std::ifstream fin(trenchCoatFileName);
	while (fin >> trenchCoatLoadedFromFile) {
		if (std::find(trenchCoatList.begin(), trenchCoatList.end(), trenchCoatLoadedFromFile) == trenchCoatList.end())
			trenchCoatList.push_back(trenchCoatLoadedFromFile);
	}
	fin.close();
	return trenchCoatList;
}



void FileRepository::writeTrenchCoatsToFile(std::vector<TrenchCoat> trenchCoatList, std::string trenchCoatFileName)
{
	if (trenchCoatFileName == "")
		throw RepositoryException(std::string("Invalid file name"));
	std::ofstream fout(trenchCoatFileName);
	for (const TrenchCoat& trenchCoatToWrite : trenchCoatList) {
		fout << trenchCoatToWrite << '\n';
	}
	fout.close();
}

void FileRepository::writeBasketListToFile(std::vector<TrenchCoat> trenchCoatList, std::string trenchCoatFileName)
{
	if (trenchCoatFileName == "")
		throw RepositoryException(std::string("Invalid file name"));
	std::ofstream fout(trenchCoatFileName);
	for (const TrenchCoat& trenchCoatToWrite : trenchCoatList) {
		fout << trenchCoatToWrite << '\n';
	}
	//fout << "\nTotal sum: " << totalSum << "\n";
	fout.close();
}


/*
* Method for adding a trench
*/
int FileRepository::addTrenchCoat(const TrenchCoat& trenchCoatToAdd)
{
	//return this->trenchList.add(trenchToAdd);
	/*if (this->trenchList.searchElementInList(trenchToAdd) == -1 && this->trenchList.checkExistanceInListByPhotographySizeColour(trenchToAdd) == -1)
	{
		this->trenchList = this->trenchList + trenchToAdd;
		return 1;
	}
	return -1;*/
	std::vector<TrenchCoat> trenchCoatList = loadTrenchCoatsFromFile();
	auto iteratorWhereTrenchIsFound = std::find(trenchCoatList.begin(), trenchCoatList.end(), trenchCoatToAdd);
	if (iteratorWhereTrenchIsFound != trenchCoatList.end() && trenchCoatList.size() != 0)
		throw RepositoryException(std::string("Trench coat already in the list"));
	trenchCoatList.push_back(trenchCoatToAdd);
	writeTrenchCoatsToFile(trenchCoatList, trenchCoatFileName);
	return 1;
}

/*
* Method for removing a trench
*/
int FileRepository::removeTrenchCoat(const TrenchCoat& trenchCoatToRemove)
{
	std::vector<TrenchCoat> trenchCoatList = loadTrenchCoatsFromFile();
	auto iteratorWhereTrenchIsFound = std::find(trenchCoatList.begin(), trenchCoatList.end(), trenchCoatToRemove);
	if (iteratorWhereTrenchIsFound == trenchCoatList.end())
		throw RepositoryException(std::string("Trench coat not in the list"));
	trenchCoatList.erase(iteratorWhereTrenchIsFound);
	writeTrenchCoatsToFile(trenchCoatList, trenchCoatFileName);
	return 1;
}

/*
* Method for updating a trench
*/
int FileRepository::updateTrenchCoat(const TrenchCoat& trenchCoatToUpdate, const TrenchCoat& trenchCoatToUpdateWith)
{
	std::vector<TrenchCoat> trenchCoatList = loadTrenchCoatsFromFile();
	auto iteratorWhereTrenchCoatIsFound = std::find(trenchCoatList.begin(), trenchCoatList.end(), trenchCoatToUpdate);
	if (iteratorWhereTrenchCoatIsFound == trenchCoatList.end())
		throw RepositoryException(std::string("Trench coat not in the list"));
	*iteratorWhereTrenchCoatIsFound = trenchCoatToUpdateWith;
	writeTrenchCoatsToFile(trenchCoatList, trenchCoatFileName);
	return 1;
}

size_t FileRepository::getTrenchCoatListLength()
{
	std::vector<TrenchCoat> movieList = loadTrenchCoatsFromFile();
	return movieList.size();
}

TrenchCoat FileRepository::getTrenchCoatAtPosition(int positionOfTrenchCoat)
{
	std::vector<TrenchCoat> trenchCoatList = loadTrenchCoatsFromFile();
	if (positionOfTrenchCoat < 0 || positionOfTrenchCoat >= trenchCoatList.size())
		throw RepositoryException(std::string("Invalid position"));
	return trenchCoatList[positionOfTrenchCoat];
}

/*
* Method for getting the list containg all the trench coats
*/
std::vector<TrenchCoat> FileRepository::getAllTrenchCoats()
{
	std::vector<TrenchCoat> trenchCoatList = loadTrenchCoatsFromFile();
	return trenchCoatList;
}

/*
* Method for getting the list containg the trench coats with a given size
*/
std::vector<TrenchCoat> FileRepository::getTrenchCoatsBySize(const int givenSize)
{
	std::vector<TrenchCoat> trenchCoatList = loadTrenchCoatsFromFile();
	std::vector<TrenchCoat> trenchCoatsBySize = {};
	if (givenSize == 0)
		return trenchCoatList;
	std::copy_if(trenchCoatList.begin(), trenchCoatList.end(), std::back_inserter(trenchCoatsBySize), [&givenSize](const TrenchCoat& trenchCoat) { return trenchCoat.getSize() == givenSize; });
	return trenchCoatsBySize;
}

/*
* Method for getting the basket list
*/
std::vector<TrenchCoat> FileRepository::getBasketList()
{
	return userBasketList;
}

/*
* Method for adding a trench coat into the basket list
*/
int FileRepository::addTrenchCoatToBasketList(const TrenchCoat& trenchCoatToAdd)
{
	std::vector<TrenchCoat> trenchCoatList = loadTrenchCoatsFromFile();
	auto iteratorWhereTrenchCoatIsFound = std::find(userBasketList.begin(), userBasketList.end(), trenchCoatToAdd);
	int quantity = trenchCoatToAdd.getQuantity();
	TrenchCoat trenchCoatToUpdateWith = trenchCoatToAdd;
	if (iteratorWhereTrenchCoatIsFound != userBasketList.end())
	{
		int quantity = trenchCoatToAdd.getQuantity();
		TrenchCoat trenchCoatToUpdateWith = trenchCoatToAdd;
		if (quantity >= 1)
		{
			trenchCoatToUpdateWith.setQuantity(quantity - 1);
			updateTrenchCoat(trenchCoatToAdd, trenchCoatToUpdateWith);
			userBasketList.push_back(trenchCoatToAdd);
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
			userBasketList.push_back(trenchCoatToAdd);
		}
	}
	writeBasketListToFile(userBasketList, userFileName);
	return 1;
}

int FileRepository::addTrenchCoatToBasketByID(const int& IDOfTheTrenchCoatToAdd)
{
	std::vector<TrenchCoat> trenchCoatList = loadTrenchCoatsFromFile();

	auto iteratorWhereTrenchCoatIsFound = std::find_if(trenchCoatList.begin(), trenchCoatList.end(), [&IDOfTheTrenchCoatToAdd](const TrenchCoat& trenchCoat) {return trenchCoat.getID() == IDOfTheTrenchCoatToAdd; });
	if (iteratorWhereTrenchCoatIsFound == trenchCoatList.end())
		throw RepositoryException(std::
			string("The trench coat with this ID does not exist."));
	addTrenchCoatToBasketList(*iteratorWhereTrenchCoatIsFound);
}

void FileRepository::deleteTrenchCoatFromBasketlist(const TrenchCoat& TrenchCoatToDelete)
{
	auto iteratorWhereTrenchCoatIsFound = std::find(userBasketList.begin(), userBasketList.end(), TrenchCoatToDelete);
	if (iteratorWhereTrenchCoatIsFound != userBasketList.end())
		throw RepositoryException(std::string("Trench Coat not in the basket list"));
	userBasketList.erase(iteratorWhereTrenchCoatIsFound);
	writeBasketListToFile(userBasketList, userFileName);
}


void FileRepository::changeFileName(const std::string& nameOfTheFileUsed)
{
	std::vector<TrenchCoat> trenchCoatList = loadTrenchCoatsFromFile();
	trenchCoatFileName = nameOfTheFileUsed;
	writeTrenchCoatsToFile(trenchCoatList, trenchCoatFileName);
}

void FileRepository::changeUserFileName(const std::string& nameOfTheFileUsed) {
	userFileName = nameOfTheFileUsed;
}

void FileRepository::changeRepositoryType(std::string repositoryTypeGiven) {
	repositoryType = repositoryTypeGiven;
}


std::string FileRepository::getUserFileName() {
	if (userFileName != "")
		return userFileName;
	return " ";
}

std::string FileRepository::getTrenchCoatFileName() {
	if (trenchCoatFileName != "")
		return trenchCoatFileName;
	return " ";
}

TrenchCoat FileRepository::findTrenchCoat(const int& ID)
{
	std::vector<TrenchCoat> trenchCoatList = loadTrenchCoatsFromFile();
	auto iteratorWhereTrenchCoatFound = std::find_if(trenchCoatList.begin(), trenchCoatList.end(), [&ID](const TrenchCoat& trenchCoat) {return trenchCoat.getID() == ID; });

	if (iteratorWhereTrenchCoatFound == trenchCoatList.end())
		throw std::runtime_error("Invalid ID");
	return *iteratorWhereTrenchCoatFound;
}

const std::vector<std::string>FileRepository::explode(const std::string& stringToExplode, const std::string& separatorsUsed)
{
	std::vector<std::string>trashValues = { "ID", " Size", " Colour", " Price", " Quantity", " Photography Url"};
	std::string partialStringObtained{ "" };
	std::vector<std::string> explodedString;

	for (auto iterator : stringToExplode)
	{
		if (iterator != separatorsUsed[0] && iterator != separatorsUsed[1])
			partialStringObtained += iterator;
		else
			if ((iterator == separatorsUsed[0] || iterator == separatorsUsed[1]) && partialStringObtained != "") {
				if (find(trashValues.begin(), trashValues.end(), partialStringObtained) == trashValues.end()) {
					explodedString.push_back(partialStringObtained);
				}
				partialStringObtained = "";
			}
	}
	if (partialStringObtained != "")
		explodedString.push_back(partialStringObtained);
	return explodedString;
}

void FileRepository::filterTrenchCoatsBySize(const int& size)
{
	std::vector<TrenchCoat> trenchCoatList = getTrenchCoatsBySize(size);
	writeTrenchCoatsToFile(trenchCoatList, trenchCoatFileName);
}
