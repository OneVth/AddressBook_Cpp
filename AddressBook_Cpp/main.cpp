#include <iostream>
#include <Windows.h>
#include <string>
#include <sstream>
#include "common.h"
#include "contact.h"
#include "contact_store.h"
#include "file_manager.h"
#include "ui_manager.h"
#include "ui_event_manager.h"

static IORESULT CreateTestFile()
{
	std::wstring path = FileManager::GetTestFilePath();

	ContactStore store;
	store.Insert(Contact(10, "Alice", "010-0000-1111"));
	store.Insert(Contact(20, "Bob", "010-0000-2222"));
	store.Insert(Contact(30, "Charlie", "010-0000-3333"));
	store.Insert(Contact(40, "David", "010-0000-4444"));
	store.Insert(Contact(40, "Dean", "010-4444-4444"));
	store.Insert(Contact(50, "Eve", "010-0000-5555"));
	store.Insert(Contact(50, "Eve", "010-5555-5555"));

	HANDLE hFile = CreateFile(
		path.c_str(),
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
		return IO_FAIL;

	BOOL bResult = FALSE;
	store.forEach([&hFile, &bResult](const Contact& contact) {
		const char* buffer = contact.Serialize();

		DWORD dwWritten = 0;

		bResult = WriteFile(hFile, buffer, (DWORD)Contact::GetContactSize(), &dwWritten, NULL);
		if (!bResult)
			return;
		});

	CloseHandle(hFile);
	return IO_SUCCESS;
}

int main(void)
{
	CreateDirectory(L".\\tests", NULL);
	
	CreateTestFile();

	UIEventManager::SearchNode(FileManager::GetTestFilePath().c_str());

	return 0;
}