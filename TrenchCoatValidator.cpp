#include "TrenchCoatValidator.h"

void TrenchCoatValidator::validateTrenchCoat(const TrenchCoat& trenchCoatUsed) {
	int ID = trenchCoatUsed.getID();
	int size = trenchCoatUsed.getSize();
	std::string colour = trenchCoatUsed.getColour();
	double price = trenchCoatUsed.getPrice();
	int quantity = trenchCoatUsed.getQuantity();
	std::string photographyUrl = trenchCoatUsed.getPhotographyUrl();
	std::string errorList = "";
	if (size < 30 || size > 60) {
		if (size % 2 == 1)
			errorList = "Invalid size ";
	}
	if (colour.size() < 2)
		errorList += "Invalid colour ";
	if (price < 20 || price > 100000)
		errorList += "Invalid price ";
	if (quantity < 0)
		errorList += "Invalid quantity ";
	/*if (photographyUrl.find("www.") == 0)
		errorList += "Invalid photography url ";*/
	if (errorList != "")
		throw ValidationException(errorList);
}