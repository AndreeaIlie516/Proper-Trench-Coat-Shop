#pragma once
#include "Repository.h"
#include "FileBasket.h"
#include "TrenchCoatValidator.h"
#include <memory>

class Service
{
private:
	Repository repository;
	FileBasket* basket;
	TrenchCoatValidator validator;

public:

	Service(const Repository& repository, FileBasket* basket, TrenchCoatValidator validator) : repository{ repository }, basket{ basket }, validator{ validator } {}

	Repository getRepository() const { return this->repository; }
	FileBasket* getBasket() { return this->basket; }
	
	void addTrenchCoatToRepository(int ID, int size,const std::string& colour, double price, int quantity,const std::string& photographUrl);
	void removeTrenchCoatFromRepository(int ID);
	void updateTrenchCoatToRepository(int ID, int size,const std::string& colour, double price, int quantity, const std::string& photographUrl);
	int checkStock();

	std::vector<TrenchCoat> getTrenchCoatsList();
	size_t getTrenchCoatListLength() const { return this->repository.getTrenchCoatListLength(); }

	Repository filterTrenchCoatsBySize(const int& size);

	void addTrenchCoatToBasket(const TrenchCoat& trenchCoat);

	void startShop();
	void nextTrenchCoatShop();

	void saveBasket(const std::string& filename);

	void openBasket() const;
};

