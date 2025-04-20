#pragma once

class Contact {
private:
	int age;
	std::string name;
	std::string phone;

	static const int MAX_AGE = 120;
	static const int MAX_NAME_LENGTH = 32;
public:
	Contact(const int age, const std::string& name, const std::string& phone);

	~Contact() = default;

	int GetAge(void) const;
	const std::string& GetName(void) const;
	const std::string& GetPhone(void) const;

	bool SetAge(const int newAge);
	bool SetName(const std::string& newName);
	bool SetPhone(const std::string& newPhone);
};