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

	//FileManager fileManager;

	// Serialize a contact
	Contact* contact = new Contact(10, "Alice", "010-0000-1111");
	const char* buffer = contact->Serialize();
	
	HANDLE hFile = CreateFile(
		L".\\tests\\test.dat",
		GENERIC_WRITE,
		0,
		NULL,
		CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cout << "Failed to create file." << std::endl;
		return 1;
	}

	DWORD dwWritten = 0;
	BOOL bResult = FALSE;

	bResult = WriteFile(hFile, buffer, (DWORD)contact->GetSize(), &dwWritten, NULL);
	if (!bResult)
	{
		std::cout << "Failed to write to file." << std::endl;
		CloseHandle(hFile);
		return 1;
	}

	std::cout << "Contact written to file successfully." << std::endl;

	delete buffer;
	delete contact;
	CloseHandle(hFile);

	// Deserialize the contact
	char readBuffer[1024] = { 0 };

	HANDLE hFileRead = CreateFile(
		L".\\tests\\test.dat",
		GENERIC_READ,
		0,
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
	bResult = FALSE;

	bResult = ReadFile(hFileRead, readBuffer, 1024, &dwRead, NULL);
	if (!bResult || dwRead == 0)
	{
		std::cout << "Failed to read from file." << std::endl;
		CloseHandle(hFileRead);
		return 1;
	}

	std::cout << "Contact read from file successfully." << std::endl;

	CloseHandle(hFileRead);

	Contact* deserializedContact = new Contact();
	deserializedContact->Deserialize(readBuffer);
	std::cout << "Deserialized Contact:\n" << 
		"Age: " << deserializedContact->GetAge() << "\n"
		<< "Name: " << deserializedContact->GetName() << "\n"
		<< "Phone: " << deserializedContact->GetPhone() << std::endl;
	delete deserializedContact;

	/*ContactStore* contacts = new ContactStore(d);
	contacts->Insert(Contact(10, "Alice", "010-0000-1111"));*/

	//contacts->Insert(Contact(20, "Bob", "010-0000-2222"));
	//contacts->Insert(Contact(30, "Charlie", "010-0000-3333"));
	//contacts->Insert(Contact(40, "Denial", "010-0000-4444"));
	//contacts->Insert(Contact(50, "Evan", "010-0000-5555"));

	//const wchar_t* filePath = L".\\tests\\test.json";
	//if (!fileManager.SaveToFile(filePath, *contacts))
	//{
	//	std::cerr << "Failed to save contacts to file" << std::endl;
	//	delete contacts;
	//	return 1;
	//}
	//std::cout << "Contacts saved to file successfully." << std::endl;

	//// Deserialize the contact from JSON
	//ContactStore* detected = new ContactStore();
	//IORESULT result = fileManager.LoadRecordFromFileByPhone(filePath, "010-0000-1111", *detected);

	//std::cout << "LoadRecordFromFileByPhone result: " << result << std::endl;

	//detected->forEach([](const Contact& contact) {
	//		std::cout << "Age: " << contact.GetAge() << std::endl;
	//		std::cout << "Name: " << contact.GetName() << std::endl;
	//		std::cout << "Phone: " << contact.GetPhone() << std::endl;
	//	});

	//delete contacts;
	//delete detected;
	return 0;
}