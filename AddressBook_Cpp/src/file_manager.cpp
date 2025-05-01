#include <iostream>
#include <Windows.h>
#include "contact.h"
#include "contact_store.h"
#include "file_manager.h"

const std::wstring FileManager::testFilePath = L".\\tests\\test.dat";

std::wstring FileManager::GetTestFilePath(void)
{
	return testFilePath;
}

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

		bResult = WriteFile(hFile, buffer, (DWORD)Contact::GetContactSize(), &dwWritten, NULL);
		if (!bResult)
			return;
		});

	CloseHandle(hFile);

	if (!bResult)
		return IO_FILE_WRITE_ERROR;
	return IO_SUCCESS;
}

IORESULT FileManager::LoadFromFile(const std::wstring& fileName, ContactStore& store)
{
	if (!store.IsEmpty())
		return IO_FAIL;

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

	DWORD dwReadSize = 0;
	BOOL bResult = TRUE;

	char readBuffer[1024] = { 0 };
	while (bResult)
	{
		memset(readBuffer, 0, 1024);

		bResult = ReadFile(hFile, readBuffer, 1024, &dwReadSize, NULL);
		if (!bResult)
		{
			CloseHandle(hFile);
			return IO_FILE_READ_ERROR;
		}

		if (dwReadSize == 0)
		{
			if (store.IsEmpty() == true)
			{
				// File is empty
				CloseHandle(hFile);
				return IO_FILE_EMPTY;
			}
			else
			{
				// The file is not empty, but no more data to read
				break;
			}
		}

		int contactSize = Contact::GetContactSize();
		if (dwReadSize % contactSize != 0)
		{
			// Invalid data size
			CloseHandle(hFile);
			return IO_FILE_READ_ERROR;
		}

		int numberOfRecords = (int)dwReadSize / contactSize;
		for (int i = 0; i < numberOfRecords; i++)
		{
			Contact* deserializedContact = new Contact();
			deserializedContact->Deserialize(readBuffer + i * contactSize);
			store.Insert(*deserializedContact);
			delete deserializedContact;
		}
	}

	CloseHandle(hFile);
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
		int contactSize = Contact::GetContactSize();
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

IORESULT FileManager::DeleteRecordFromFileByPhone(
	const std::wstring& fileName,
	const std::string& phone
)
{
	// Checking validation and existence in the file of the phone number 
	// is necessary at the UI level.

	DWORD dwRead = 0, dwWritten = 0;
	BOOL bResult = TRUE;

	HANDLE hFileSource = CreateFile(
		fileName.c_str(),
		GENERIC_READ,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFileSource == INVALID_HANDLE_VALUE)
		return IO_FAIL;

	std::wstring tempPath = fileName;
	std::wstring::size_type pos = tempPath.find_last_of(L"\\");
	if (pos != std::wstring::npos)
	{
		tempPath = tempPath.substr(0, pos);
		tempPath += L"\\temp.dat";
	}

	HANDLE hFileTemp = CreateFile(
		tempPath.c_str(),
		GENERIC_WRITE,
		0,
		NULL,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		NULL
	);
	if (hFileTemp == INVALID_HANDLE_VALUE)
	{
		CloseHandle(hFileSource);
		return IO_FAIL;
	}

	char readBuffer[1024] = { 0 };
	while (bResult)
	{
		memset(readBuffer, 0, 1024);

		bResult = ReadFile(hFileSource, readBuffer, 1024, &dwRead, NULL);
		if (bResult && dwRead == 0)
		{
			// Reached end of file
			break;
		}
		else if (!bResult)
		{
			CloseHandle(hFileSource);
			CloseHandle(hFileTemp);
			return IO_FILE_READ_ERROR;
		}

		// Check whether the chunk has phone number
		bool isFound = false;
		int numberOfRecords = (int)dwRead / Contact::GetContactSize();
		for (int i = 0; i < numberOfRecords; i++)
		{
			char* phonePos = readBuffer + i * Contact::GetContactSize() + sizeof(int) + Contact::GetMaxNameLength();
			if (strcmp(phonePos, phone.c_str()) == 0)
			{
				// when the phone number is found,
				// copy the records before and after the phone number
				isFound = true;
				char* targetPos = phonePos - sizeof(int) - Contact::GetMaxNameLength();
				DWORD beforeSize = (DWORD)(targetPos - readBuffer);
				bResult = WriteFile(hFileTemp, readBuffer, beforeSize, &dwWritten, NULL);
				if (!bResult || beforeSize != dwWritten)
				{
					CloseHandle(hFileSource);
					CloseHandle(hFileTemp);
					return IO_FILE_WRITE_ERROR;
				}

				char* targetEnd = phonePos + Contact::GetContactSize();
				DWORD afterSize = dwRead - beforeSize - Contact::GetContactSize();
				bResult = WriteFile(hFileTemp, targetEnd, afterSize, &dwWritten, NULL);
				if (!bResult || afterSize != dwWritten)
				{
					CloseHandle(hFileSource);
					CloseHandle(hFileTemp);
					return IO_FILE_WRITE_ERROR;
				}
				break;
			}
		}

		if (!isFound)
		{
			// if the phone number is not found, write the whole chunk
			bResult = WriteFile(hFileTemp, readBuffer, dwRead, &dwWritten, NULL);
			if (!bResult)
			{
				CloseHandle(hFileSource);
				CloseHandle(hFileTemp);
				return IO_FILE_WRITE_ERROR;
			}
		}
	}

	CloseHandle(hFileSource);
	CloseHandle(hFileTemp);

	if (DeleteFile(fileName.c_str()) != TRUE)
		return IO_FAIL;
	if (MoveFile(tempPath.c_str(), fileName.c_str()) != TRUE)
		return IO_FAIL;
	return IO_SUCCESS;
}