#include "TrenchCoat.h"
#include <iostream>

/*
* Class for TrenchCoat entity, containing ID <int>, size <int>, colour <string>, price <double>, quantity <int> and photography url <string>
*/
TrenchCoat::TrenchCoat(const int& ID, const int& size, const std::string& colour, const double& price, const int& quantity, const std::string& photographyUrl)
	:ID{ ID }, size{ size }, colour{ colour }, price{ price }, quantity{ quantity }, photographyUrl{ photographyUrl }{}

bool TrenchCoat::operator==(const TrenchCoat& trenchToCheck) const
{
	return ID == trenchToCheck.ID;
}

void TrenchCoat::operator=(const TrenchCoat& trenchToGetValuesFrom)
{
	ID = trenchToGetValuesFrom.getID();
	size = trenchToGetValuesFrom.getSize();
	colour = trenchToGetValuesFrom.getColour();
	price = trenchToGetValuesFrom.getPrice();
	quantity = trenchToGetValuesFrom.getQuantity();
	photographyUrl = trenchToGetValuesFrom.getPhotographyUrl();
}

bool TrenchCoat::operator!=(const TrenchCoat& trenchToCheck) const
{
	return !(trenchToCheck == *this);
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

	tokens = trenchCoat.explode(trenchCoatString, ",:");
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

const std::vector<std::string>TrenchCoat::explode(const std::string& stringToExplode, const std::string& separatorsUsed)
{
	std::vector<std::string>trashValues = {"ID", " Size", " Colour", " Price", " Quantity", " PhotographyUrl" };
	std::string partialStringObtained{ "" };
	std::vector<std::string> explodedString;

	for (auto iterator : stringToExplode)
	{
		if (iterator != separatorsUsed[0] && iterator != separatorsUsed[1])
			partialStringObtained += iterator;
		else
			if ((iterator == separatorsUsed[0] || iterator == separatorsUsed[1]) && partialStringObtained != "") {
				if (find(trashValues.begin(), trashValues.end(), partialStringObtained) == trashValues.end()) {
					explodedString.push_back(partialStringObtained);
				}
				partialStringObtained = "";
			}
	}
	if (partialStringObtained != "")
		explodedString.push_back(partialStringObtained);
	return explodedString;
}

std::string TrenchCoat::getOutputForm() const
{
	std::string finalOutputForm = "ID: " + std::to_string(ID) + ", Size: " + std::to_string(size) + ", Colour: " + colour + ", Price: " + std::to_string(int(price)) + ", Quantity: " + std::to_string(quantity) + ", PhotographyUrl: " + photographyUrl;
	return finalOutputForm;
}