#include "AdminService.h"
#include "ActionFilter.h"
#include <iostream>
#include <fstream>
/*
* Method for generating entities
*/
//AdminService::AdminService(Repository& repository, int generate): repository{repository}{
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
//		adminAddTrenchCoat(9,36, "cream", 930, 35, "https://ro.pinterest.com/pin/16958936088814138/");
//		adminAddTrenchCoat(10, 34, "black", 895, 63, "https://ro.pinterest.com/pin/1015350678462263022/");
//
//	}
//}
//}

AdminService::AdminService(FileRepository* newRepository){
	this->repository = newRepository;
	this->inUndoRedo = 0;
}

/*
* Method for adding a trench coat
*/
int AdminService::adminAddTrenchCoat(int ID, int size, std::string colour, double price, int quantity, std::string photographyUrl)
{
	TrenchCoat trenchCoat{ ID,size,colour,price,quantity,photographyUrl };
	TrenchCoatValidator::validateTrenchCoat(trenchCoat);
	std::unique_ptr<Action> addAction = std::make_unique<ActionAdd>(repository, trenchCoat);
	undoSteps.push_back(move(addAction));
	if (!inUndoRedo) {
		emptyRedo();
	}
	return repository->addTrenchCoat(trenchCoat);
}

/*
* Method for removing a trench coat, by its ID
*/
int AdminService::adminRemoveTrenchCoat(int ID)
{
	TrenchCoat trenchCoat{ ID, 30, "FillColour", 100, 10, "Url" };
	TrenchCoat trenchCoatFound = repository->findTrenchCoat(ID);
	std::unique_ptr<Action> deleteAction = std::make_unique<ActionRemove>(repository, trenchCoatFound);
	undoSteps.push_back(move(deleteAction));
	if (!inUndoRedo) {
		emptyRedo();
	}
	return repository->removeTrenchCoat(trenchCoat);
}

/*
* Method for updating a trench
*/
int AdminService::adminUpdateTrenchCoat(int ID, int size, std::string colour, double price, int quantity, std::string photographyUrl)
{
	std::vector<TrenchCoat> listOfTrenchCoats = adminGetTrenchCoatsList();
	/*TrenchCoat trenchCoat1;
	for (int i = 0; i < listOfTrenchCoats.size(); i++)
	{
		if (listOfTrenchCoats[i].getID() == ID)
		{
			trenchCoat1 = listOfTrenchCoats[i];
		}
	}*/
	/*auto iteratorWhereTrenchCoatFound = std::find_if(listOfTrenchCoats.begin(), listOfTrenchCoats.end(), [&ID](const TrenchCoat& trenchCoat) {return trenchCoat.getID() == ID; });
	if (iteratorWhereTrenchCoatFound == listOfTrenchCoats.end())
		return -1;
	TrenchCoat trenchCoat2{ ID,size,colour,price,quantity,photographyUrl };
	TrenchCoatValidator::validateTrenchCoat(trenchCoat2);
	return repository->updateTrenchCoat(*iteratorWhereTrenchCoatFound, trenchCoat2);
	*/
	TrenchCoat trenchCoatUsed{ ID,size,colour,price,quantity,photographyUrl };
	TrenchCoatValidator::validateTrenchCoat(trenchCoatUsed);
	TrenchCoat trenchCoatFound = repository->findTrenchCoat(ID);
	std::unique_ptr<Action> updateAction = std::make_unique<ActionUpdate>(repository, trenchCoatFound, trenchCoatUsed);
	undoSteps.push_back(move(updateAction));
	if (!inUndoRedo) {
		emptyRedo();
	}
	return repository->updateTrenchCoat(trenchCoatFound, trenchCoatUsed);
}

/*
* Method for getting the list containg all the trench coats
*/
std::vector<TrenchCoat> AdminService::adminGetTrenchCoatsList()
{
	return repository->getAllTrenchCoats();
}

//int AdminService::checkStock()
//{
//	std::vector<TrenchCoat> listOfTrenchCoats = adminGetTrenchCoatsList();
//	for (const TrenchCoat& trenchCoatUsed : listOfTrenchCoats)
//	{
//		if (trenchCoatUsed.getQuantity() == 0)
//		{
//			return adminRemoveTrenchCoat(trenchCoatUsed.getID());
//		}
//	}
//	return 1;
//}

void AdminService::filterTrenchCoatsBySize(const int& size) {
	std::vector<TrenchCoat> listOfTrenchCoats = this->adminGetTrenchCoatsList();
	std::vector<TrenchCoat> deletedTrenchCoats;
	for (int i = 0; i < listOfTrenchCoats.size(); ++i)
		if (listOfTrenchCoats[i].getSize() != size)
			deletedTrenchCoats.push_back(listOfTrenchCoats[i]);
	std::unique_ptr<Action> filterAction = std::make_unique<ActionFilter>(repository, deletedTrenchCoats);
	undoSteps.push_back(move(filterAction));
	if (!inUndoRedo) {
		emptyRedo();
	}
	repository->filterTrenchCoatsBySize(size);
}


int AdminService::changeRepositoryFileName(const std::string& nameOfTheFileUsed)
{
	repository->changeFileName(nameOfTheFileUsed);
	return 1;
}

const std::vector<std::string> AdminService::explode(const std::string& stringToExplode, const char& separatorUsed)
{
	std::string partialStringObtained{ "" };
	std::vector<std::string> explodedString;

	for (auto iterator : stringToExplode)
	{
		if (iterator != separatorUsed)
			partialStringObtained += iterator;
		else
			if (iterator == separatorUsed && partialStringObtained != "") {
				explodedString.push_back(partialStringObtained);
				partialStringObtained = "";
			}
	}
	if (partialStringObtained != "")
		explodedString.push_back(partialStringObtained);
	return explodedString;
}

void AdminService::undo() {
	if (undoSteps.size() == 0)
		throw ValidationException("No more undos!\n");
	inUndoRedo = 1;
	undoSteps[undoSteps.size() - 1]->executeUndo();
	redoSteps.push_back(move(undoSteps[undoSteps.size() - 1]));
	undoSteps.pop_back();
	inUndoRedo = 0;
}

void AdminService::redo() {
	if (redoSteps.size() == 0)
		throw ValidationException("No more redos!\n");
	inUndoRedo = 1;
	redoSteps[redoSteps.size() - 1]->executeRedo();
	undoSteps.push_back(move(redoSteps[redoSteps.size() - 1]));
	redoSteps.pop_back();
	inUndoRedo = 0;
}

void AdminService::emptyRedo() {
	redoSteps.clear();
}

