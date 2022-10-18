#include "Service.h"
#include "FileBasket.h"
#include "RepositoryExceptions.h"
#include <algorithm>

//AdminService::AdminService(FileRepository* newRepository, int generate) {
//	this->repository = newRepository;
//	if (generate == 1)
//	{
//		adminAddTrenchCoat(1, 34, "black", 1050, 2, "https://ro.pinterest.com/pin/1030128114739714411/");
//		adminAddTrenchCoat(2, 42, "black", 955, 40, "https://ro.pinterest.com/pin/46443439896666696/");
//		adminAddTrenchCoat(3, 38, "blue", 750, 32, "https://ro.pinterest.com/pin/4996249574499481/");
//		adminAddTrenchCoat(4, 34, "green", 840, 60, "https://ro.pinterest.com/pin/842595411541546478/");
//		adminAddTrenchCoat(5, 36, "red", 1000, 25, "https://ro.pinterest.com/pin/68743044028/");
//		adminAddTrenchCoat(6, 38, "cream", 955.55, 10, "https://ro.pinterest.com/pin/563018694221612/");
//		adminAddTrenchCoat(7, 40, "blue", 875, 42, "https://ro.pinterest.com/pin/132856257747125782/");
//		adminAddTrenchCoat(8, 44, "black", 1540, 32, "https://ro.pinterest.com/pin/10203536646546593/");
//		adminAddTrenchCoat(9, 36, "cream", 930, 35, "https://ro.pinterest.com/pin/16958936088814138/");
//		adminAddTrenchCoat(10, 34, "black", 895, 63, "https://ro.pinterest.com/pin/1015350678462263022/");
//
//	}
//}

/*
* Method for adding a trench coat
*/
void Service::addTrenchCoatToRepository(int ID, int size, const std::string& colour, double price, int quantity, const std::string& photographyUrl)
{
	TrenchCoat trenchCoat{ ID,size,colour,price,quantity,photographyUrl };
	this->validator.validateTrenchCoat(trenchCoat);
	this->repository.addTrenchCoat(trenchCoat);
}

/*
* Method for removing a trench
*/
void Service::removeTrenchCoatFromRepository(int ID)
{
	TrenchCoat trenchCoat = this->repository.findTrenchCoatByID(ID);
	this->repository.removeTrenchCoat(trenchCoat);
}

/*
* Method for updating a trench
*/
void Service::updateTrenchCoatToRepository(int ID, int size,const std::string& colour, double price, int quantity,const std::string& photographyUrl)
{
	TrenchCoat oldTrenchCoat = this->repository.findTrenchCoatByID(ID);
	TrenchCoat newTrenchCoat{ ID,size,colour,price,quantity,photographyUrl };
	this->validator.validateTrenchCoat(newTrenchCoat);
	this->repository.updateTrenchCoat(oldTrenchCoat, newTrenchCoat);
}

/*
* Method for getting the list containg all the trench coats
*/
std::vector<TrenchCoat> Service::getTrenchCoatsList()
{
	return this->repository.getAllTrenchCoats();
}

Repository Service::filterTrenchCoatsBySize(const int& size)
{
	Repository newRepo;

	for (const TrenchCoat& trenchCoat : this->getRepository().getAllTrenchCoats())
	{
		if (trenchCoat.getSize() == size)
			newRepo.addTrenchCoat(trenchCoat);
	}

	return newRepo;
}


int Service::checkStock()
{
	std::vector<TrenchCoat> listOfTrenchCoats = this->repository.getAllTrenchCoats();
	for (auto trenchCoat : listOfTrenchCoats)
	{
		if (trenchCoat.getQuantity() == 0)
		{
			removeTrenchCoatFromRepository(trenchCoat.getID());
		}
	}
	return 1;
}

void Service::addTrenchCoatToBasket(const TrenchCoat& trenchCoat)
{
	if (this->basket == nullptr)
		return;
	this->basket->add(trenchCoat);
}

void Service::startShop()
{
	if (this->basket == nullptr)
		return;
	this->basket->shop();
}

void Service::nextTrenchCoatShop()
{
	if (this->basket == nullptr)
		return;
	this->basket->next();
}

void Service::saveBasket(const std::string& fileName)
{
	if (this->basket == nullptr)
		return;

	this->basket->setFileName(fileName);
	this->basket->writeToFile();
}

void Service::openBasket() const
{
	if (this->basket == nullptr)
		return;

	this->basket->displayBasket();
}