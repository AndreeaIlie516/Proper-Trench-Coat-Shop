#pragma once
#include <string>

class RepositoryException : public std::exception {
private:
	std::string messageOfException;
	std::string errorGenerated;

public:
	RepositoryException(std::string messageOfException = "");
	const char* what() const noexcept;
};