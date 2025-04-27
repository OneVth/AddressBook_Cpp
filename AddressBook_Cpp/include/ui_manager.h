#pragma once

#include <iostream>

class UIManager
{
private:

public:
	UIManager() = default;
	~UIManager() = default;

	static bool GetUserInfo(std::string& name, int& age, std::string& phone);

	static bool GetUserAge(int& age);
	static bool GetUserName(std::string& name);
	static bool GetUserPhone(std::string& phone);
};