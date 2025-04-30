#define NOMINMAX
#include <iostream>
#include <Windows.h>
#include "ui_event_manager.h"
#include "ui_manager.h"
#include "file_manager.h"
#include "contact_store.h"

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
}

void UIEventManager::DeleteNode(LPCWSTR path)
{
	std::cout << "Delete Contact" << std::endl;
}

void UIEventManager::SearchNode(LPCWSTR path)
{
	std::cout << "Search Contact" << std::endl;
}

void UIEventManager::EditNode(LPCWSTR path)
{
	std::cout << "Edit Contact" << std::endl;
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