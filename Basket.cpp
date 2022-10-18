#include "Basket.h"

Basket::Basket()
{
	this->current = 0;
}

void Basket::add(const TrenchCoat& trenchCoat)
{
	this->trenchCoatListBySize.push_back(trenchCoat);
}

void Basket::remove(const TrenchCoat& trenchCoat)
{
}

TrenchCoat Basket::getCurrentTrenchCoat()
{
	if (this->current == this->trenchCoatListBySize.size())
		this->current = 0;
	return this->trenchCoatListBySize[this->current];
	return TrenchCoat{};
}

void Basket::shop()
{
	if (this->trenchCoatListBySize.size() == 0)
		return;
	this->current = 0;
	TrenchCoat currentTrenchCoat = this->getCurrentTrenchCoat();
	currentTrenchCoat.view();
}

void Basket::next()
{
	if (this->trenchCoatListBySize.size() == 0)
		return;
	this->current++;
	TrenchCoat currentTrenchCoat = this->getCurrentTrenchCoat();
	currentTrenchCoat.view();
}

bool Basket::isEmpty()
{
	return this->trenchCoatListBySize.size() == 0;
}
