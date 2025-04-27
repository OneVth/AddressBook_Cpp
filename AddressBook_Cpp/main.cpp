#include <iostream>
#include <Windows.h>
#include "common.h"
#include "contact.h"
#include "contact_store.h"
#include "file_manager.h"

int main(void)
{
	CreateDirectory(L".\\tests", NULL);
	
	// Serialize a contact
	ContactStore* store = new ContactStore();

	Contact* c1 = new Contact(10, "Alice", "010-0000-1111");
	Contact* c2 = new Contact(20, "Bob", "010-0000-2222");
	Contact* c3 = new Contact(30, "Charlie", "010-0000-3333");
	store->Insert(*c1);
	store->Insert(*c2);
	store->Insert(*c3);

	if (FileManager::SaveToFile(L".\\tests\\test.dat", *store) == IO_SUCCESS)
	{
		std::cout << "File saved successfully." << std::endl;
	}
	else
	{
		std::cout << "Failed to save file." << std::endl;
	}

	delete c1;
	delete c2;
	delete c3;
	delete store;
	
	ContactStore* searchStore = new ContactStore();
	FileManager::LoadRecordFromFileByPhone(
		L".\\tests\\test.dat",
		"010-0000-1111",
		*searchStore
	);

	searchStore->forEach([](const Contact& contact) {
		std::cout << "Contact:\n" <<
			"Age: " << contact.GetAge() << "\n"
			<< "Name: " << contact.GetName() << "\n"
			<< "Phone: " << contact.GetPhone() << std::endl;
		}
	);

	// Deserialize the contact
	/*ContactStore* loadedStore = new ContactStore();
	char readBuffer[1024] = { 0 };

	HANDLE hFileRead = CreateFile(
		L".\\tests\\test.dat",
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFileRead == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed to open file for reading." << std::endl;
		return 1;
	}

	DWORD dwRead = 0;
	BOOL bResult = FALSE;

	bResult = ReadFile(hFileRead, readBuffer, 1024, &dwRead, NULL);
	if (!bResult || dwRead == 0)
	{
		std::cout << "Failed to read from file." << std::endl;
		CloseHandle(hFileRead);
		return 1;
	}

	Contact* deserializedContact = new Contact();
	int contactSize = deserializedContact->GetSize();
	if(dwRead % contactSize != 0)
	{
		std::cout << "File size is not a multiple of contact size." << std::endl;
		delete deserializedContact;
		CloseHandle(hFileRead);
		return 1;
	}

	for (int i = 0; i < ((int)dwRead / contactSize); i++)
	{
		deserializedContact->Deserialize(readBuffer + i * contactSize);
		loadedStore->Insert(*deserializedContact);
	}
	std::cout << "Contact read from file successfully." << std::endl;

	CloseHandle(hFileRead);

	loadedStore->forEach([](const Contact& contact) {
		std::cout << "Contact:\n" <<
			"Age: " << contact.GetAge() << "\n"
			<< "Name: " << contact.GetName() << "\n"
			<< "Phone: " << contact.GetPhone() << std::endl;
		});
	
	delete deserializedContact;
	delete loadedStore;*/
	return 0;
}