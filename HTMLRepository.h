#pragma once
#include "FileRepository.h"
#include <fstream>
#include <regex>

class HTMLRepository: public FileRepository {
public:
	HTMLRepository(std::string fileName = "", std::string trenchCoatFileName = "") { this->userFileName = fileName; this->trenchCoatFileName = trenchCoatFileName; };
	
	void writeBasketListToFile(std::vector<TrenchCoat> trenchCoatList, std::string trenchCoatFileName) override;
	
	int addTrenchCoatToBasketList(const TrenchCoat& trenchCoatToAdd) override;
	int addTrenchCoatToBasketByID(const int& IDOfTheTrenchCoatToAdd) override;
	void deleteTrenchCoatFromBasketlist(const TrenchCoat& TrenchCoatToDelete) override;
	
	size_t getBasketListLength() override;
	std::vector<TrenchCoat> getBasketList() override;
};


