#include <iostream>
//#include <Windows.h>
#include <string>
#include "common.h"
#include "contact.h"
#include "contact_store.h"
#include "file_manager.h"
#include "ui_manager.h"
#include "ui_event_manager.h"

int main(void)
{
	//CreateDirectory(L".\\tests", NULL);
	
	UIEventManager::Option option = UIManager::PrintMenu();
	while (option != UIEventManager::Option::MENU_EXIT)
	{
		UIEventManager::menuFunctions[option]();
		std::getchar();

		option = UIManager::PrintMenu();
	}
	
	return 0;
}