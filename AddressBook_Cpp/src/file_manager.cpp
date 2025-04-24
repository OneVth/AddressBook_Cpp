#include <iostream>
#include <Windows.h>
#include "contact_store.h"
#include "file_manager.h"
#include "json.hpp"

BOOL FileManager::SaveToFile(const std::wstring& fileName, ContactStore& store)
{
	if (store.IsEmpty())
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

	SetFilePointer(hFile, 0, NULL, FILE_END);
	
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

	CloseHandle(hFile);
	return TRUE;
}