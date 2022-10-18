#pragma once
#include "Basket.h"

class FileBasket: public Basket
{
protected:
	std::string fileName = "file";

public:
	FileBasket() = default;
	virtual ~FileBasket() = default;

	void setFileName(const std::string& fileName);
	virtual void writeToFile() = 0;
	virtual void displayBasket() {};

};

