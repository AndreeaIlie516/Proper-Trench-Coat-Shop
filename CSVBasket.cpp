#include "CSVBasket.h"
#include <fstream>
#include <Windows.h>
#include "RepositoryExceptions.h"

void CSVBasket::writeToFile()
{
	std::ofstream fout(this->fileName);

	if (!fout.is_open())
		throw FileException("The file could not be opened!");

	for (auto trenchCoat : this->trenchCoatListBySize)
		fout << trenchCoat;

	fout.close();
}

void CSVBasket::displayBasket()
{
	std::string command = "notepad ";
	system(command.append(this->fileName + this->extension).c_str());
}