#include "Repository.h"
#include <iostream>
#include <fstream>
#include "Utils.h"
#include "RepositoryExceptions.h"

Repository::Repository(const bool& init, const std::string& fileName)
{
	std::vector<TrenchCoat>{};
	this->fileName = fileName;
	this->readFromFile();

}

//Repository::~Repository()
//{
//	this->writeToFile();
//}

/*
* Method for adding a trench
*/
void Repository::addTrenchCoat(const TrenchCoat& trenchCoatToAdd)
{
	auto it = std::find(trenchCoatList.begin(), trenchCoatList.end(), trenchCoatToAdd);
	if (it != trenchCoatList.end() && trenchCoatList.size() != 0)
	{
		int quantity, newQuantity, ID, size;
		std::string colour, photographyUrl;
		double price;
		quantity = it->getQuantity();
		newQuantity = quantity + trenchCoatToAdd.getQuantity();
		ID = it->getID();
		size = it->getSize();
		colour = it->getColour();
		price = it->getPrice();
		photographyUrl = it->getPhotographyUrl();
		
		TrenchCoat oldTrenchCoat{ ID, size, colour, price, quantity, photographyUrl };

		TrenchCoat newTrenchCoat{ ID, size, colour, price, newQuantity, photographyUrl };
		this->updateTrenchCoat(oldTrenchCoat, newTrenchCoat);

	}
	else
		trenchCoatList.push_back(trenchCoatToAdd);
	this->writeToFile();
}

/*
* Method for removing a trench
*/
void Repository::removeTrenchCoat(const TrenchCoat& trenchCoatToRemove)
{
	auto it = std::find(trenchCoatList.begin(), trenchCoatList.end(), trenchCoatToRemove);
	if (it == trenchCoatList.end())
		throw InexistentTrenchCoatException{};
	this->trenchCoatList.erase(it);
	this->writeToFile();
}

/*
* Method for updating a trench
*/
void Repository::updateTrenchCoat(const TrenchCoat& trenchCoatToUpdate, const TrenchCoat& trenchCoatToUpdateWith)
{
	auto it = std::find(trenchCoatList.begin(), trenchCoatList.end(), trenchCoatToUpdate);
	if (it == trenchCoatList.end())
		throw InexistentTrenchCoatException{};
	*it = trenchCoatToUpdateWith;
	this->writeToFile();
}

TrenchCoat Repository::findTrenchCoatByID(int ID) const
{
	auto it = std::find_if(trenchCoatList.begin(), trenchCoatList.end(), [&ID](const TrenchCoat& trenchCoat) {return trenchCoat.getID() == ID; });

	if (it == trenchCoatList.end())
		throw InexistentTrenchCoatException{};
	return *it;
}

TrenchCoat Repository::getTrenchCoatAtPosition(int positionOfTrenchCoat)
{
	if (positionOfTrenchCoat < 0 || positionOfTrenchCoat >= trenchCoatList.size())
		throw InvalidPositionException{};
	return trenchCoatList[positionOfTrenchCoat];
}

/*
* Method for getting the list containg all the trench coats
*/
std::vector<TrenchCoat> Repository::getAllTrenchCoats()
{
	return trenchCoatList;
}

/*
* Method for getting the list containg the trench coats with a given size
*/
std::vector<TrenchCoat> Repository::getTrenchCoatsBySize(const int& givenSize)
{
	std::vector<TrenchCoat> trenchCoatsBySize;
	if (givenSize == 0)
		return trenchCoatList;
	std::copy_if(trenchCoatList.begin(), trenchCoatList.end(), std::back_inserter(trenchCoatsBySize), [&givenSize](const TrenchCoat& trenchCoat) { return trenchCoat.getSize() == givenSize; });
	return trenchCoatsBySize;
}


void Repository::readFromFile()
{
	std::ifstream fin(this->fileName);
	
	if (!fin.is_open())
		throw FileException("The file could not be opened!");
	
	TrenchCoat trenchCoat;
	while (fin >> trenchCoat) {
		if (std::find(trenchCoatList.begin(), trenchCoatList.end(), trenchCoat) == trenchCoatList.end())
			this->trenchCoatList.push_back(trenchCoat);
	}
	fin.close();
}


void Repository::writeToFile()
{

	std::ofstream fout(this->fileName);
	if (!fout.is_open())
		throw FileException("The file could not be opened!");
	for (auto trenchCoatToWrite : this->trenchCoatList) {
		fout << trenchCoatToWrite;
	}
	fout.close();
}
