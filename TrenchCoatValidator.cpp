#include "TrenchCoatValidator.h"

ValidationException::ValidationException(std::vector<std::string> _errors) : errors{ _errors }
{
}

std::vector<std::string> ValidationException::getErrors() const
{
	return this->errors;
}

void TrenchCoatValidator::validateTrenchCoat(const TrenchCoat& trenchCoatUsed) {
	int ID = trenchCoatUsed.getID();
	int size = trenchCoatUsed.getSize();
	std::string colour = trenchCoatUsed.getColour();
	double price = trenchCoatUsed.getPrice();
	int quantity = trenchCoatUsed.getQuantity();
	std::string photographyUrl = trenchCoatUsed.getPhotographyUrl();
	std::vector<std::string> errorList;
	if (size < 30 || size > 60) {
		if (size % 2 == 1)
			errorList.push_back(std::string("Invalid size!\n"));
	}
	if (colour.size() < 2)
		errorList.push_back(std::string("Invalid colour!\n"));
	if (price < 20 || price > 100000)
		errorList.push_back(std::string("Invalid price!\n"));
	if (quantity < 0)
		errorList.push_back(std::string("Invalid quantity\n"));
	if (photographyUrl.find("https://") != 0 && photographyUrl.find("www.") != 0)
		errorList.push_back(std::string("Invalid photography url!\n"));
	if (errorList.size() > 0)
		throw ValidationException(errorList);
}