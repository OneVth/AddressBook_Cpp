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
	static const std::wstring testFilePath;

public:
	FileManager() = default;
	~FileManager() = default;

	static std::wstring GetTestFilePath(void);

	static IORESULT SaveToFile(const std::wstring& fileName, ContactStore& store);

	static IORESULT LoadFromFile(const std::wstring& fileName, ContactStore& store);

	static IORESULT LoadRecordFromFileByPhone(
		const std::wstring& fileName,
		const std::string& phone,
		ContactStore& store
	);
};