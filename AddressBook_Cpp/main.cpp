#include <iostream>
#include <Windows.h>
#include "common.h"
#include "contact.h"
#include "contact_store.h"
#include "file_manager.h"
#include "json.hpp"

int main(void)
{
	CreateDirectory(L".\\tests", NULL);

	FileManager fileManager;

	ContactStore* contacts = new ContactStore();
	contacts->Insert(Contact(10, "Alice", "010-0000-1111"));
	contacts->Insert(Contact(20, "Bob", "010-0000-2222"));
	contacts->Insert(Contact(30, "Charlie", "010-0000-3333"));
	contacts->Insert(Contact(40, "Denial", "010-0000-4444"));
	contacts->Insert(Contact(50, "Evan", "010-0000-5555"));

	const wchar_t* filePath = L".\\tests\\test.json";
	if (!fileManager.SaveToFile(filePath, *contacts))
	{
		std::cerr << "Failed to save contacts to file" << std::endl;
		delete contacts;
		return 1;
	}
	std::cout << "Contacts saved to file successfully." << std::endl;

	// Deserialize the contact from JSON
	ContactStore* detected = new ContactStore();
	IORESULT result = fileManager.LoadRecordFromFileByPhone(filePath, "010-0000-1111", *detected);

	std::cout << "LoadRecordFromFileByPhone result: " << result << std::endl;

	detected->forEach([](const Contact& contact) {
			std::cout << "Age: " << contact.GetAge() << std::endl;
			std::cout << "Name: " << contact.GetName() << std::endl;
			std::cout << "Phone: " << contact.GetPhone() << std::endl;
		});

	delete contacts;
	delete detected;
	return 0;
}