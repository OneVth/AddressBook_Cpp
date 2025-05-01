#define NOMINMAX
#include <iostream>
#include <Windows.h>
#include <string>
#include "ui_event_manager.h"
#include "ui_manager.h"
#include "file_manager.h"
#include "contact_store.h"
#include "common.h"

UIEventManager::MenuFunction UIEventManager::menuFunctions[UIEventManager::Option::UI_FUNC_COUNT] = {
	UIEventManager::Exit,
	UIEventManager::PrintAll,
	UIEventManager::InsertNode,
	UIEventManager::DeleteNode,
	UIEventManager::SearchNode,
	UIEventManager::EditNode
};

void UIEventManager::PrintAll(LPCWSTR path)
{
	std::cout << "Print All Records" << '\n' << std::endl;
	ContactStore store;
	FileManager::LoadFromFile(path, store);

	store.forEach([](const Contact& contact) {
		std::cout <<
			"Age: " << contact.GetAge() << '\n' <<
			"Name: " << contact.GetName() << '\n' <<
			"Phone: " << contact.GetPhone() << '\n' << std::endl;
		});
}

void UIEventManager::InsertNode(LPCWSTR path)
{
	std::cout << "Insert New Contact" << std::endl;
	
	ContactStore store;

	do
	{
		int age = 0;
		std::string name;
		std::string phone;

		if (!UIManager::GetUserInfo(name, age, phone))
		{
			std::cout << "Invalid input. Please try again." << std::endl;
			return;
		}

		ContactStore storeForCheck;
		if (FileManager::LoadRecordFromFileByPhone(path, phone, storeForCheck) == IO_SUCCESS)
		{
			std::cout << "Phone number already exists. Please try again." << std::endl;
		}
		else
		{
			Contact contact(age, name, phone);
			store.Insert(contact);
		}

		char ch = 0;
		std::cout << "Press any key to continue (or 'q' to exit) : ";
		std::cin >> ch;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
		if (ch == 'q' || ch == 'Q')
			break;
	} while (true);

	if (FileManager::SaveToFile(path, store) == IO_SUCCESS)
		std::cout << "Data saved successfully." << std::endl;
	else
		std::cout << "Failed to save data." << std::endl;
}

void UIEventManager::DeleteNode(LPCWSTR path)
{
	do
	{
		std::system("cls");
		std::cout << "Delete Record" << std::endl;
		std::cout << "Need the phone number to delete" << std::endl;

		std::string phone;
		UIManager::GetUserPhone(phone);

		IORESULT result = FileManager::DeleteRecordFromFileByPhone(path, phone);

		if (result == IO_SUCCESS)
			std::cout << "Record deleted successfully." << std::endl;
		else if (result == IO_FILE_NOT_FOUND)
			std::cout << "No matching record found." << std::endl;
		else
			std::cout << "Error occurred while deleting the record." << std::endl;

		char ch = 0;
		printf("Press any key to continue (or 'q' to exit) : ");
		std::cin >> ch;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
		if (ch == 'q' || ch == 'Q')
			break;
	} while (true);
}

void UIEventManager::SearchNode(LPCWSTR path)
{
	std::cout << "Search Contact" << std::endl;
	std::cout << "You can use \"AND\" or \"OR\" to search.\n" << std::endl;

	std::string input;
	std::cout << "Enter search query: ";
	std::getline(std::cin, input);

	ContactStore result;
	if (FileManager::SearchRecordsFromFile(path, input, result) == IO_SUCCESS)
	{
		std::cout << "Searched:\n" << std::endl;

		result.forEach([](const Contact contact) {
			std::cout <<
				"Age: " << contact.GetAge() << '\n' <<
				"Name: " << contact.GetName() << '\n' <<
				"Phone: " << contact.GetPhone() << '\n' << std::endl;
			});
	}
	else
		std::cout << "Failed to search" << std::endl;
}

void UIEventManager::EditNode(LPCWSTR path)
{
	do
	{
		std::system("cls");
		std::cout << "Edit Record" << std::endl;
		std::cout << "Need the phone number to edit" << std::endl;

		std::string phone;
		UIManager::GetUserPhone(phone);

		ContactStore store;
		if (FileManager::LoadRecordFromFileByPhone(path, phone, store) == IO_SUCCESS)
		{
			Contact target;
			store.forEach([&target](const Contact& contact) {
				target.SetAge(contact.GetAge());
				target.SetName(contact.GetName());
				target.SetPhone(contact.GetPhone());

				std::cout <<
					"\n[Target Record]\n" <<
					"Age: " << target.GetAge() << " | " <<
					"Name: " << target.GetName() << " | " <<
					"Phone: " << target.GetPhone() << '\n' << std::endl;
				});

			char input = 0;
			std::cout <<
				"Edit: [1] Age [2] Name [3] Phone [0] Exit\n" <<
				"Choose an option: ";
			std::cin >> input;
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

			int newAge = 0;
			std::string newName;
			std::string newPhone;

			int option = input - '0';
			if (option <= 3 && option >= 0)
			{
				IORESULT result = IO_FAIL;
				switch (option)
				{
				case 0:
					std::cout << "Return to menu" << std::endl;
					return;
				case 1:
					UIManager::GetUserAge(newAge);
					result = FileManager::EditRecordAgeFromFile(path, target, newAge);
					break;
				case 2:
					UIManager::GetUserName(newName);
					result = FileManager::EditRecordNameFromFile(path, target, newName);
					break;
				case 3:
					UIManager::GetUserPhone(newPhone);
					result = FileManager::EditRecordPhoneFromFile(path, target, newPhone);
					break;
				default:
					break;
				}

				if (result == IO_SUCCESS)
					std::cout << "Success editing record" << std::endl;
				else
					std::cout << "Failed to edit the record" << std::endl;
			}
			else
			{
				std::cout << "Invalid value. Please enter 0-3" << std::endl;
			}
		}
		else
		{
			std::cout << "Cannot find record." << std::endl;
		}
		
		char ch = 0;
		printf("Press any key to continue (or 'q' to exit) : ");
		std::cin >> ch;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer
		if (ch == 'q' || ch == 'Q')
			break;
	} while (true);
}

void UIEventManager::Exit(LPCWSTR path)
{
	std::cout << "Exiting..." << std::endl;
}

void UIEventManager::RunEventLoop(LPCWSTR path)
{
	Option option = UIManager::PrintMenu();
	while (option != MENU_EXIT)
	{
		menuFunctions[option](path);
		std::cout << "Press any key to continue..." << std::endl;
		std::getchar();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		option = UIManager::PrintMenu();
	}
}