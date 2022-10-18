#pragma once
#include "FileBasket.h"
#include <string>

class CSVBasket : public FileBasket
{
private:
	std::string extension = ".csv";

public:
	CSVBasket() = default;

	void writeToFile() override;

	void displayBasket() override;
};


