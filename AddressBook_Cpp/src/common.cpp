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

bool Validator::IsPhoneFormat(const std::string& str)
{
	if (str.empty())
		return false;

	if (str.length() != 13)
		return false;

	for (int i = 0; i < 13; i++)
	{
		if ((i == 3 || i == 8) && str[i] != '-')
			return false;

		if ((i != 3 && i != 8) && !std::isdigit(str[i]))
			return false;
	}

	return true;
}
