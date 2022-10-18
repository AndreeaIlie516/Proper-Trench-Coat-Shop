#include "HTMLBasket.h"
#include <fstream>
#include <Windows.h>
#include "RepositoryExceptions.h"

void HTMLBasket::writeToFile()
{
	std::ofstream fout(this->fileName + this->extension);
	if (!fout.is_open())
		throw FileException("The file could not be opened!");

	fout << "<!DOCTYPE html><html><head><title>Adoption List</title></head><body><table border=\"1\" cellpadding=\"5\" cellspacing=\"5\">";
	fout << "<tr>";
	fout << "<th>ID</th>";
	fout << "<th>Size</th>";
	fout << "<th>Colour</th>";
	fout << "<th>Price</th>";
	fout << "<th>Quantity</th>";
	fout << "<th>Photography Url</th>";
	fout << "</tr>";

	for (auto trenchCoat : this->trenchCoatListBySize)
	{
		fout << "<tr>";
		fout << "<td>" + std::to_string(trenchCoat.getID()) + "</td>";
		fout << "<td>" + std::to_string(trenchCoat.getSize()) + "</td>";
		fout << "<td>" + trenchCoat.getColour() + "</td>";
		fout << "<td>" + std::to_string(trenchCoat.getPrice()) + "</td>";
		fout << "<td>" + std::to_string(trenchCoat.getQuantity()) + "</td>";
		fout << "<td><a href=\"" + trenchCoat.getPhotographyUrl() + "\">link</a></td>";
		fout << "</tr>";
	}

	fout << "</table></body></html>";
	fout.close();
}

void HTMLBasket::displayBasket()
{
	std::string command = "start ";

	try
	{
		system(command.append(this->fileName + this->extension).c_str());
	}
	catch (std::exception&)
	{
		throw RepositoryException("Invalid link!");
	}
}