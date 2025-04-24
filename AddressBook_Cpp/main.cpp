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

	const wchar_t* filePath = L".\\tests\\test.json";
	if (!fileManager.SaveToFile(filePath, *contacts))
	{
		std::cerr << "Failed to save contacts to file" << std::endl;
		delete contacts;
		return 1;
	}
	std::cout << "Contacts saved to file successfully." << std::endl;

	// Deserialize the contact from JSON
	HANDLE hFile = CreateFile(
		filePath,
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		std::cerr << "Failed to open file" << std::endl;
		return 1;
	}

	DWORD dwFileSize = GetFileSize(hFile, NULL);
	if (dwFileSize == INVALID_FILE_SIZE)
	{
		std::cerr << "Failed to get file size" << std::endl;
		CloseHandle(hFile);
		return 1;
	}

	char* buffer = new char[dwFileSize + 1];
	DWORD dwReadSize = 0;
	BOOL bResult = FALSE;

	bResult = ReadFile(hFile, buffer, dwFileSize, &dwReadSize, NULL);
	if (!bResult || dwReadSize == 0)
	{
		std::cerr << "Failed to read from file" << std::endl;
		delete[] buffer;
		CloseHandle(hFile);
		return 1;
	}

	buffer[dwReadSize] = '\0';

	nlohmann::json j;
	try {
		j = nlohmann::json::parse(buffer);
		std::cout << "Read JSON: " << j.dump(4) << std::endl;
	}
	catch (const nlohmann::json::parse_error& e) {
		std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
		delete[] buffer;
		CloseHandle(hFile);
		return 1;
	}

	delete[] buffer;
	CloseHandle(hFile);

	for (const auto& item : j)
	{
		Contact contact;
		from_json(item, contact);
		contacts->Insert(contact);
	}

	contacts->forEach([](const Contact& contact) {
			std::cout << "Age: " << contact.GetAge() << std::endl;
			std::cout << "Name: " << contact.GetName() << std::endl;
			std::cout << "Phone: " << contact.GetPhone() << std::endl;
		});

	delete contacts;
	return 0;
}