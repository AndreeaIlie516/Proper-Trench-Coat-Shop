#pragma once

#include <string>
#include <vector>
#include "FileRepository.h"
#include <vector>
#include <fstream>
#include "ValidationException.h"
#include "TrenchCoatValidator.h"
#include <memory>
#include "Action.h"
#include "ActionAdd.h"
#include "ActionUpdate.h"
#include "ActionRemove.h"
#include <memory>

/*
* AdminService class, containing repository <Repository>
*/
class AdminService
{
private:
	std::vector<std::unique_ptr<Action>> undoSteps;
	std::vector<std::unique_ptr<Action>> redoSteps;
	FileRepository* repository;
	bool inUndoRedo;

public:
	//AdminService(Repository& repository);
	AdminService(FileRepository* repository);
	int adminAddTrenchCoat(int ID, int size, std::string colour, double price, int quantity, std::string photographUrl);
	int adminRemoveTrenchCoat(int ID);
	int adminUpdateTrenchCoat(int ID, int size, std::string colour, double price, int quantity, std::string photographUrl);
	//int checkStock();
	
	std::vector<TrenchCoat> adminGetTrenchCoatsList();
	size_t getTrenchCoatListLength() const { return repository->getTrenchCoatListLength(); }
	
	int changeRepositoryFileName(const std::string& nameOfTheFileUsed);
	const std::vector<std::string> explode(const std::string& stringToExplode, const char& separatorUsed);

	std::string getFileName() { return this->repository->getTrenchCoatFileName(); };
	void undo();
	void redo();
	void emptyRedo();

	void filterTrenchCoatsBySize(const int& size);
};

