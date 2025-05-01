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
	
	std::wstring path = FileManager::GetTestFilePath();

	ContactStore store;
	store.Insert(Contact(10, "Alice", "010-0000-1111"));
	store.Insert(Contact(20, "Bob", "010-0000-2222"));
	store.Insert(Contact(30, "Charlie", "010-0000-3333"));
	store.Insert(Contact(40, "David", "010-0000-4444"));
	store.Insert(Contact(50, "Eve", "010-0000-5555"));
	FileManager::SaveToFile(path, store);
	
	Contact contact(10, "Alice", "010-0000-1111");
	IORESULT result = FileManager::EditRecordAgeFromFile(path, contact, 90);
	std::cout << "EditRecordAgeFromFile: " << result << std::endl;

	/*ContactStore store;
	FileManager::LoadFromFile(FileManager::GetTestFilePath(), store);

	store.forEach([](const Contact& contact) {
		std::cout <<
			"Age: " << contact.GetAge() << '\n' <<
			"Name: " << contact.GetName() << '\n' <<
			"Phone: " << contact.GetPhone() << std::endl;
		});*/
	
	return 0;
}