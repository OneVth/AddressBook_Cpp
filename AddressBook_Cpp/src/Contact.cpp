#include <iostream>
#include "common.h"
#include "contact.h"
#include "json.hpp"

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

void to_json(nlohmann::json& j, const Contact& c)
{
	j = nlohmann::json{
		{"age", c.age},
		{"name", c.name},
		{"phone", c.phone}
	};
}

void from_json(const nlohmann::json& j, Contact& c)
{
	j.at("age").get_to(c.age);
	j.at("name").get_to(c.name);
	j.at("phone").get_to(c.phone);
}