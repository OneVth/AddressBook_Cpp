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
};