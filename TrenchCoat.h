#pragma once

#include <string>
#include <vector>

/*
* TrenchCoat class, containing ID <int>, size <int>, colour <string>, price <double>, quantity <int> and photography url <string>
*/
class TrenchCoat
{
private:
	int ID;
	int size;
	std::string colour;
	double price;
	int quantity;
	std::string photographyUrl;

public:
	TrenchCoat() : ID{ 0 }, size{ 0 }, colour(""), price{ 0.0 }, quantity{ 0 }, photographyUrl{ "" }{}
	TrenchCoat(const int& ID, const int& size, const std::string& colour, const double& price, const int& quantity, const std::string& photographyUrl);
	
	int getID() const { return this->ID; }
	int getSize() const { return this->size; }
	std::string getColour() const { return this->colour; }
	double getPrice() const { return this->price; }
	int getQuantity() const { return this->quantity; }
	std::string getPhotographyUrl() const { return this->photographyUrl; }
	
	void setID(const int& ID) { this->ID = ID; }
	void setSize(const int& size) { this->size = size; }
	void setColour(const std::string& colour) { this->colour = colour; }
	void setPrice(const double& price) { this->price = price; }
	void setQuantity(const int& quantity) { this->quantity = quantity; }
	void setPhotographyUrl(const std::string& photographyUrl) { this->photographyUrl = photographyUrl; }
	
	bool operator==(const TrenchCoat& trenchToCheck) const;
	void operator=(const TrenchCoat& trenchToGetValuesFrom);
	bool operator!=(const TrenchCoat& trenchToCheck) const;
	
	std::string getOutputForm() const;
	
	friend std::ostream& operator<< (std::ostream& outStream, const TrenchCoat& trenchCoatToOutput);
	friend std::istream& operator>> (std::istream& inStream, TrenchCoat& trenchCoat);
	const std::vector<std::string> explode(const std::string& stringToExplode, const std::string& separatorsUsed);
};	
 
