#include <iostream>
#include <Windows.h>
#include "common.h"
#include "contact.h"
#include "contact_store.h"
#include "file_manager.h"
#include "ui_manager.h"

int main(void)
{
	CreateDirectory(L".\\tests", NULL);
	
	std::string name;
	std::string phone;
	int age;

	while (UIManager::GetUserInfo(name, age, phone))
	{
		std::cout << "\nage: " << age << std::endl;
		std::cout << "name: " << name << std::endl;
		std::cout << "phone: " << phone << std::endl;
		std::getchar(); // Wait for user input
	}
	
	return 0;
}