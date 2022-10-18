#pragma once
#include "FileBasket.h"
#include <string>

class HTMLBasket : public FileBasket
{
private:
	std::string extension = ".html";

public:
	HTMLBasket() = default;

	void writeToFile() override;

	void displayBasket() override;
};


