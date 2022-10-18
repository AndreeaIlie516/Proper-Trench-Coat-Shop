#pragma once
#include "TrenchCoat.h"
#include <string>
#include <vector>

class ValidationException 
{
private:
	std::vector<std::string> errors;

public:
	ValidationException(std::vector<std::string> _errors);
	std::vector<std::string> getErrors() const;
};


class TrenchCoatValidator {
public:
	TrenchCoatValidator() {}
	static void validateTrenchCoat(const TrenchCoat& trenchCoat);
};