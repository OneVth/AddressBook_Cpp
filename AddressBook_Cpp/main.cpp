#include <iostream>
#include "common.h"

int main(void)
{
	std::cout << "IsAllAlpha(): " <<
		(Validator::IsAllAlpha("abc") ? "pass" : "fail") <<
		std::endl;

	std::cout << "IsAllDigit(): " <<
		(Validator::IsAllDigit("123") ? "pass" : "fail") <<
		std::endl;

	std::cout << "IsPhoneFormat(): " << 
		(Validator::IsPhoneFormat("010-0000-0000") ? "pass" : "fail") <<
		std::endl;
	return 0;
}