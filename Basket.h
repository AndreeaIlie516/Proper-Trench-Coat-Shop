#pragma once
#include "TrenchCoat.h"
#include <vector>

class Basket
{
protected:
	std::vector<TrenchCoat> trenchCoatListBySize;
	int current;
	//std::string fileName = "file";

public:
	Basket();

	void add(const TrenchCoat& trenchCoat);

	TrenchCoat getCurrentTrenchCoat();

	void shop();

	void next();

	bool isEmpty();

	size_t getSize() const { return static_cast<int>(this->trenchCoatListBySize.size()); };

	virtual ~Basket() = default;
};

