#pragma once

#include <iostream>
#include "contact_store.h"

enum IORESULT
{
	IO_FILE_WRITE_ERROR = -4,
	IO_FILE_READ_ERROR,
	IO_FILE_EMPTY,
	IO_FILE_NOT_FOUND,
	IO_FAIL,
	IO_SUCCESS,
};

class FileManager 
{
private:

public:
	FileManager() = default;
	~FileManager() = default;

	static IORESULT SaveToFile(const std::wstring& fileName, ContactStore& store);

	IORESULT LoadRecordFromFileByPhone(
		const std::wstring& fileName,
		const std::string& phone,
		ContactStore& store
	);
};