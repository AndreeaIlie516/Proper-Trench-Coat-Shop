#include "TrenchCoat.h"
#include "Utils.h"
#include <Windows.h>
#include <shellapi.h>
#include <iostream>
#include <vector>

/*
* Class for TrenchCoat entity, containing ID <int>, size <int>, colour <string>, price <double>, quantity <int> and photography url <string>
*/
TrenchCoat::TrenchCoat(const int& ID, const int& size, const std::string& colour, const double& price, const int& quantity, const std::string& photographyUrl)
	:ID{ ID }, size{ size }, colour{ colour }, price{ price }, quantity{ quantity }, photographyUrl{ photographyUrl }{}

bool TrenchCoat::operator==(const TrenchCoat& trenchCoatToCheck) const
{
	return ID == trenchCoatToCheck.ID;
}

void TrenchCoat::operator=(const TrenchCoat& trenchCoatToGetValuesFrom)
{
	ID = trenchCoatToGetValuesFrom.getID();
	size = trenchCoatToGetValuesFrom.getSize();
	colour = trenchCoatToGetValuesFrom.getColour();
	price = trenchCoatToGetValuesFrom.getPrice();
	quantity = trenchCoatToGetValuesFrom.getQuantity();
	photographyUrl = trenchCoatToGetValuesFrom.getPhotographyUrl();
}

bool TrenchCoat::operator!=(const TrenchCoat& trenchCoatToCheck) const
{
	return !(trenchCoatToCheck == *this);
}

void TrenchCoat::view()
{
	ShellExecuteA(NULL, NULL, "chrome.exe", this->getPhotographyUrl().c_str(), NULL, SW_SHOWMAXIMIZED);
}

std::ostream& operator<<(std::ostream& outStream, const TrenchCoat& trenchCoatToOutput)
{
	outStream << trenchCoatToOutput.getOutputForm();
	return outStream;
}

std::istream& operator>> (std::istream& inStream, TrenchCoat& trenchCoat) {
	std::string trenchCoatString;
	std::getline(inStream, trenchCoatString);
	std::vector <std::string> tokens;
	int ok = 1;
	if (trenchCoatString == "") {
		return inStream;
	}

	if (tokens.size() != 6) 
		return inStream;

	tokens = tokenize(trenchCoatString, ',');
	std::string ID = tokens[0].substr(1);
	for (auto character : ID)
	{
		if (isdigit(character) == 0)
			ok = 0;
	}
	if (ok == 1)
		trenchCoat.ID = std::stoi(ID);
	std::string size = tokens[1].substr(1);
	for (auto character : size)
	{
		if (isdigit(character) == 0)
			ok = 0;
	}
	if (ok == 1)
		trenchCoat.size = std::stoi(size);

	trenchCoat.colour = tokens[2].substr(1);

	std::string price = tokens[3].substr(1);
	for (auto character : price)
	{
		if (isdigit(character) == 0 || character == '.')
			ok = 0;
	}
	if (ok == 1)
		trenchCoat.price = std::stof(price);

	std::string quantity = tokens[4].substr(1);
	for (auto character : quantity)
	{
		if (isdigit(character) == 0)
			ok = 0;
	}
	if (ok == 1)
		trenchCoat.quantity = std::stoi(quantity);

	trenchCoat.photographyUrl = tokens[5].substr(1);
	return inStream;
}

std::string TrenchCoat::getOutputForm() const
{
	std::string finalOutputForm = std::to_string(ID) + "," + std::to_string(size) + "," + colour + "," + std::to_string(int(price)) + "," + std::to_string(quantity) + "," + photographyUrl + '\n';
	return finalOutputForm;
}