#include <iostream>
#include <Windows.h>
#include "contact_store.h"
#include "file_manager.h"
#include "json.hpp"

BOOL FileManager::SaveToFile(const std::wstring& fileName, ContactStore& store)
{
	/*if (store.IsEmpty())
		return FALSE;

	nlohmann::json j;

	store.forEach([&j](const Contact& contact) {
		nlohmann::json contactJson;
		to_json(contactJson, contact);
		j.push_back(contactJson);
		});

	std::string jsonStr = j.dump(4);

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
		return FALSE;
	
	

	int flag = 0;
	if (SetFilePointer(hFile, 0, NULL, FILE_END) > 0)
		flag = 1;
	
	DWORD dwWritten = 0;
	BOOL bResult = FALSE;
	bResult = WriteFile(
		hFile, 
		jsonStr.c_str(), 
		(DWORD)jsonStr.size(), 
		&dwWritten, 
		NULL
	);
	if (!bResult)
	{
		CloseHandle(hFile);
		return FALSE;
	}

	if (flag)
	{
		SetFilePointer(hFile, -(LONG)dwWritten - 2, NULL, FILE_END);
		bResult = WriteFile(
			hFile,
			",\n ",
			3,
			&dwWritten,
			NULL
		);
	}

	CloseHandle(hFile);*/
	return TRUE;
}

IORESULT FileManager::LoadRecordFromFileByPhone(
	const std::wstring& fileName,
	const std::string& phone,
	ContactStore& store)
{
	// Checking validation of the phone number is necessary
	// at the UI level.

	//HANDLE hFile = CreateFile(
	//	fileName.c_str(),
	//	GENERIC_READ,
	//	FILE_SHARE_READ,
	//	NULL,
	//	OPEN_EXISTING,
	//	FILE_ATTRIBUTE_NORMAL,
	//	NULL
	//);
	//if (hFile == INVALID_HANDLE_VALUE)
	//	return IO_FAIL;

	//DWORD dwFileSize = GetFileSize(hFile, NULL);
	//if (dwFileSize == INVALID_FILE_SIZE)
	//{
	//	CloseHandle(hFile);
	//	return IO_FAIL;
	//}

	//char* buffer = new char[dwFileSize + 1];
	//DWORD dwReadSize = 0;
	//BOOL bResult = FALSE;

	//bResult = ReadFile(hFile, buffer, dwFileSize, &dwReadSize, NULL);
	//if (!bResult || dwReadSize == 0)
	//{
	//	delete[] buffer;
	//	CloseHandle(hFile);
	//	return IO_FILE_READ_ERROR;
	//}

	//buffer[dwReadSize] = '\0';

	//nlohmann::json j;
	//try {
	//	j = nlohmann::json::parse(buffer);
	//}
	//catch (const nlohmann::json::parse_error& /*e*/) {
	//	delete[] buffer;
	//	CloseHandle(hFile);
	//	return IO_FAIL;
	//}

	//for (const auto& item : j)
	//{
	//	Contact contact;
	//	from_json(item, contact);

	//	if (contact.GetPhone() == phone)
	//	{
	//		store.Insert(contact);
	//		delete[] buffer;
	//		CloseHandle(hFile);
	//		return IO_SUCCESS;
	//	}
	//}

	//delete[] buffer;
	//CloseHandle(hFile);
	return IO_FILE_NOT_FOUND;
}