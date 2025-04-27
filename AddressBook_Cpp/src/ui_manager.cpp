#include <iostream>
#include <string>
#include "ui_manager.h"
#include "common.h"

bool UIManager::GetUserInfo(std::string& name, int& age, std::string& phone)
{
	while (true)
	{
		std::system("cls");
		std::cout << "Enter new data: need [Name] [Age] [Phone number]" << std::endl;

		if (GetUserName(name) && GetUserAge(age) && GetUserPhone(phone))
			return true;
		else
		{
			char ch = 0;
			std::cout << "\nPress any key to retry (or 'q' to exit) : ";
			std::cin >> ch;
			
			if (ch == 'q' || ch == 'Q')
				break;
		}

		// Clear input buffer
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	}
	return false;
}

bool UIManager::GetUserAge(int& age)
{
	std::string temp;
	std::cout << "\n[Age]" << std::endl;
	std::cout << "Enter age: ";
	std::getline(std::cin, temp);
	if (temp.empty())
	{
		std::cout << "Age cannot be empty." << std::endl;
		return false;
	}
	else if (!Validator::IsAllDigit(temp))
	{
		std::cout << "Age must be a number." << std::endl;
		return false;
	}
	else if (std::stoi(temp) < 0)	// check for negative numbers
	{
		std::cout << "Age cannot be negative." << std::endl;
		return false;
	}
	else if (std::stoi(temp) >= 120)	// check for age greater than 120(MAX_AGE)
	{
		std::cout << "Age cannot be greater than " << 120 << std::endl;
		return false;
	}

	age = std::stoi(temp);
	return true;
}

bool UIManager::GetUserName(std::string& name)
{
	std::cout << "\n[Name]" << std::endl;
	std::cout << "Enter name: ";
	std::getline(std::cin, name);
	if (name.empty())
	{
		std::cout << "Name cannot be empty." << std::endl;
		return false;
	}
	else if (name.length() >= 32)	// check for name length
	{
		std::cout << "Name cannot be longer than " << 32 << std::endl;
		return false;
	}
	else if (!Validator::IsAllAlpha(name))
	{
		std::cout << "Name must contain only alphabets." << std::endl;
		return false;
	}

	return true;
}

bool UIManager::GetUserPhone(std::string& phone)
{
	std::cout << "\n[Phone]" << std::endl;
	std::cout << "Enter phone number: ";
	std::getline(std::cin, phone);
	if (phone.empty())
	{
		std::cout << "Phone number cannot be empty." << std::endl;
		return false;
	}
	else if (!Validator::IsPhoneFormat(phone))
	{
		std::cout << "Phone number must be in format: XXX-XXXX-XXXX" << std::endl;
		return false;
	}

	return true;
}