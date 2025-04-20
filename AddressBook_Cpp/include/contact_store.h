#pragma once

#include <iostream>
#include <map>
#include "contact.h"


class ContactStore
{
private:
	std::map<std::string, Contact> contacts;

public:
	ContactStore() = default;
	~ContactStore() = default;

	bool Insert(const Contact& contact);

	// for debugging
	void Print(void);
};