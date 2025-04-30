#include <iostream>
#include <Windows.h>
#include <string>
#include "common.h"
#include "contact.h"
#include "contact_store.h"
#include "file_manager.h"
#include "ui_manager.h"
#include "ui_event_manager.h"

int main(void)
{
	CreateDirectory(L".\\tests", NULL);

	ContactStore store;
	FileManager::LoadFromFile(FileManager::GetTestFilePath(), store);

	store.forEach([](const Contact& contact) {
		std::cout <<
			"Age: " << contact.GetAge() << '\n' <<
			"Name: " << contact.GetName() << '\n' <<
			"Phone: " << contact.GetPhone() << std::endl;
		});
	
	return 0;
}