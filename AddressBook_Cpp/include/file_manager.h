#pragma once

#include <iostream>
#include "contact_store.h"

class FileManager 
{
private:

public:
	FileManager() = default;
	~FileManager() = default;

	int SaveToFile(const std::wstring& fileName, ContactStore& store);
};