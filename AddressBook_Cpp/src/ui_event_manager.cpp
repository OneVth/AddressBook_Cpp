#include <iostream>
#include "ui_event_manager.h"
#include "ui_manager.h"

UIEventManager::MenuFunction UIEventManager::menuFunctions[UIEventManager::Option::UI_FUNC_COUNT] = {
	UIEventManager::Exit,
	UIEventManager::PrintAll,
	UIEventManager::InsertNode,
	UIEventManager::DeleteNode,
	UIEventManager::SearchNode,
	UIEventManager::EditNode
};

void UIEventManager::PrintAll()
{
	std::cout << "Print All Contacts" << std::endl;
}

void UIEventManager::InsertNode()
{
	std::cout << "Insert New Contact" << std::endl;
}

void UIEventManager::DeleteNode()
{
	std::cout << "Delete Contact" << std::endl;
}

void UIEventManager::SearchNode()
{
	std::cout << "Search Contact" << std::endl;
}

void UIEventManager::EditNode()
{
	std::cout << "Edit Contact" << std::endl;
}

void UIEventManager::Exit()
{
	std::cout << "Exiting..." << std::endl;
}

void UIEventManager::RunEventLoop()
{
	Option option = UIManager::PrintMenu();
	while (option != MENU_EXIT)
	{
		menuFunctions[option]();
		std::cout << "Press any key to continue..." << std::endl;
		std::getchar();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		option = UIManager::PrintMenu();
	}
}