#include "RepositoryExceptions.h"

FileException::FileException(const std::string& msg) : message(msg)
{
}

const char* FileException::what()
{
	return message.c_str();
}

RepositoryException::RepositoryException() : exception{}, message{ "" }
{
}

RepositoryException::RepositoryException(const std::string& msg) : message{ msg }
{
}

const char* RepositoryException::what()
{
	return this->message.c_str();
}

const char* InexistentTrenchCoatException::what()
{
	return "There are no trench coats with the given ID!";
}

const char* InvalidPositionException::what()
{
	return "There are no trench coat on the given position!";
}

