#include <iostream>
#include "common.h"

bool Validator::IsAllDigit(const std::string& str)
{
	for (char c : str)
	{
		if (!std::isdigit(static_cast<unsigned char>(c)))
			return false;
	}
	return true;
}

bool Validator::IsAllAlpha(const std::string& str)
{
	for (char c : str)
	{
		if (!std::isalpha(static_cast<unsigned char>(c)))
			return false;
	}
	return true;
}
