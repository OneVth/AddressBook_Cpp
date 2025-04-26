#include <iostream>
#include <Windows.h>
#include "contact_store.h"
#include "file_manager.h"

IORESULT FileManager::SaveToFile(const std::wstring& fileName, ContactStore& store)
{
	if (store.IsEmpty())
		return IO_FAIL;

	HANDLE hFile = CreateFile(
		fileName.c_str(),
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
		return IO_FAIL;
	
	SetFilePointer(hFile, 0, NULL, FILE_END);
	
	BOOL bResult = FALSE;
	store.forEach([&hFile, &bResult](const Contact& contact) {
		const char* buffer = contact.Serialize();

		DWORD dwWritten = 0;

		bResult = WriteFile(hFile, buffer, (DWORD)contact.GetSize(), &dwWritten, NULL);
		if (!bResult)
			return;
	});

	CloseHandle(hFile);

	if (!bResult)
		return IO_FILE_WRITE_ERROR;
	return IO_SUCCESS;
}

IORESULT FileManager::LoadRecordFromFileByPhone(
	const std::wstring& fileName,
	const std::string& phone,
	ContactStore& store)
{
	// Checking validation of the phone number is necessary
	// at the UI level.

	HANDLE hFile = CreateFile(
		fileName.c_str(),
		GENERIC_READ,
		FILE_SHARE_READ,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFile == INVALID_HANDLE_VALUE)
		return IO_FAIL;

	ContactStore* loadedStore = new ContactStore();

	DWORD dwReadSize = 0;
	BOOL bResult = TRUE;

	char* readBuffer = new char[1024];
	while (bResult)
	{
		memset(readBuffer, 0, 1024);

		bResult = ReadFile(hFile, readBuffer, 1024, &dwReadSize, NULL);
		if (!bResult || dwReadSize == 0)
		{
			delete[] readBuffer;
			CloseHandle(hFile);
			return IO_FILE_READ_ERROR;
		}

		Contact* deserializedContact = new Contact();
		int contactSize = deserializedContact->GetSize();
		if (dwReadSize % contactSize != 0)
		{
			delete deserializedContact;
			CloseHandle(hFile);
			return IO_FILE_READ_ERROR;
		}

		for (int i = 0; i < ((int)dwReadSize / contactSize); i++)
		{
			deserializedContact->Deserialize(readBuffer + i * contactSize);
			if (deserializedContact->GetPhone() == phone)
			{
				store.Insert(*deserializedContact);
				delete[] readBuffer;
				delete deserializedContact;
				CloseHandle(hFile);
				return IO_SUCCESS;
			}
		}
	}
		
	delete[] readBuffer;
	CloseHandle(hFile);
	return IO_FILE_NOT_FOUND;
}