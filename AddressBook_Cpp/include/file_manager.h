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
	static const size_t READ_BUFFER_SIZE;

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

	static IORESULT LoadRecordsFromFileByAge(
		const std::wstring& fileName,
		const int& age,
		ContactStore& store);

	static IORESULT LoadRecordsFromFileByName(
		const std::wstring& fileName,
		const std::string& name,
		ContactStore& store);

	static IORESULT SearchRecordsFromFile(
		const std::wstring& fileName,
		const std::string& input,
		ContactStore& result
	);

	static IORESULT DeleteRecordFromFileByPhone(
		const std::wstring& fileName,
		const std::string& phone
	);

	static IORESULT EditRecordAgeFromFile(
		const std::wstring& fileName,
		Contact& contact,
		const int& newAge
	);

	static IORESULT EditRecordNameFromFile(
		const std::wstring& fileName,
		Contact& contact,
		const std::string& newName
	);

	static IORESULT EditRecordPhoneFromFile(
		const std::wstring& fileName,
		Contact& contact,
		const std::string& newPhone
	);
};