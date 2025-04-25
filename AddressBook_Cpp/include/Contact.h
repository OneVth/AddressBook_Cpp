#pragma once

class Contact {
private:
	int age;
	std::string name;
	std::string phone;

	static const int MAX_AGE = 120;			// 4 bytes
	static const int MAX_NAME_LENGTH = 32;	// 32 bytes
	static const int MAX_PHONE_LENGTH = 14;	// 14 bytes
	static const int PADDING = 14;			// padding for matching 64 bytes	
	static const int CONTACT_SIZE = 64;		// 4 + 32 + 14  + 14 = 64 bytes
public:
	Contact() = default;
	Contact(const int age, const std::string& name, const std::string& phone);

	~Contact() = default;

	int GetAge(void) const;
	const std::string& GetName(void) const;
	const std::string& GetPhone(void) const;
	const int GetSize(void) const;	// return size of contact to be used in serialization

	bool SetAge(const int newAge);
	bool SetName(const std::string& newName);
	bool SetPhone(const std::string& newPhone);

	// Serialization
	
};