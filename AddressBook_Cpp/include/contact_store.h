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

	bool IsEmpty() const;

	bool Insert(const Contact& contact);

	//void forEach(const std::function<void(const Contact&)>& callback) const;
};