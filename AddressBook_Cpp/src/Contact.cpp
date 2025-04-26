#include <iostream>
#include <vector>
#include "common.h"
#include "contact.h"

Contact::Contact(const int age, const std::string& name, const std::string& phone)
	: age(age), name(name), phone(phone) {}

int Contact::GetAge(void) const
{
	return age;
}

const std::string& Contact::GetName(void) const
{
	return name;
}

const std::string& Contact::GetPhone(void) const
{
	return phone;
}

const int Contact::GetSize(void) const
{
	return CONTACT_SIZE;
}

bool Contact::SetAge(const int newAge)
{
	if (newAge < 0 || newAge > MAX_AGE)
		return false;
	age = newAge;
	return true;
}

bool Contact::SetName(const std::string& newName)
{
	if (newName.length() >= MAX_NAME_LENGTH || !Validator::IsAllAlpha(newName))
		return false;
	name = newName;
	return true;
}

bool Contact::SetPhone(const std::string& newPhone)
{
	if (!Validator::IsPhoneFormat(newPhone))
		return false;
	phone = newPhone;
	return true;
}

const char* Contact::Serialize() const
{
	char* buffer = new char[CONTACT_SIZE];
	memset(buffer, 0, CONTACT_SIZE);

	memcpy(buffer, &age, sizeof(age));
	memcpy(buffer + sizeof(age), name.c_str(), name.size());
	memcpy(buffer + sizeof(age) + MAX_NAME_LENGTH, phone.c_str(), phone.size());

	return buffer;
}

void Contact::Deserialize(const char* buffer) 
{
	if (buffer == nullptr) return;

	memcpy(&this->age, buffer, sizeof(this->age));

	name.assign(buffer + sizeof(age), MAX_NAME_LENGTH);
	name.erase(name.find('\0'), std::string::npos);

	phone.assign(buffer + sizeof(age) + MAX_NAME_LENGTH, MAX_PHONE_LENGTH);
	phone.erase(phone.find('\0'), std::string::npos);
}
