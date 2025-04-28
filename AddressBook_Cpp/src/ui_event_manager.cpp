#include <iostream>
#include "ui_event_manager.h"

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
	std::cout << "Running Event Loop" << std::endl;
}