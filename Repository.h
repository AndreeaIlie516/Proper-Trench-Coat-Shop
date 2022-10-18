#pragma once
#include <vector>
#include <algorithm>
#include "TrenchCoat.h"

class Repository
{
protected:
	std::vector<TrenchCoat> trenchCoatList;
	std::string fileName;

public:
	Repository(const bool& generate=false, const std::string& fileName="inputFile.txt");
	//~Repository();
	
	void addTrenchCoat(const TrenchCoat& trenchCoatToAdd);
	void removeTrenchCoat(const TrenchCoat& trenchCoatToRemove);
	void updateTrenchCoat(const TrenchCoat& trenchCoatToUpdate, const TrenchCoat& trenchCoatToUpdateWith);
	
	TrenchCoat findTrenchCoatByID(int ID) const;
	
	size_t getTrenchCoatListLength() const { return trenchCoatList.size(); }
	TrenchCoat getTrenchCoatAtPosition(int positionOfTrenchCoat);
	std::vector<TrenchCoat> getAllTrenchCoats();
	std::vector<TrenchCoat> getTrenchCoatsBySize(const int& givenSize);

	TrenchCoat& operator[](const int& index) { return this->trenchCoatList[index]; };

	int size() const { return static_cast<int>(this->trenchCoatList.size()); };

	
private:
	void readFromFile();
	void writeToFile();
};


