#pragma once
#include <iostream>

class Validator {
public:
	static bool IsAllDigit(const std::string& str);
	static bool IsAllAlpha(const std::string& str);
	static bool IsPhoneFormat(const std::string& str);
};