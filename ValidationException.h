#pragma once
#include <string>

class ValidationException: public std::exception {
private:
	std::string messageOfException;
	std::string errorGenerated;

public:
	ValidationException(std::string messageOfException = "");
	const char* what() const noexcept;
};

