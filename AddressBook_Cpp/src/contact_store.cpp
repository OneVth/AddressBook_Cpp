#include "contact_store.h"

bool ContactStore::Insert(const Contact& contact)
{
	auto result = contacts.insert({ contact.GetPhone(), contact });
	return result.second;
}

void ContactStore::Print(void)
{
	if (contacts.empty())
	{
		std::cout << "No contacts available" << std::endl;
		return;
	}

	for (const auto& entry : contacts)
	{
		const Contact& contact = entry.second;
		std::cout <<
			"Age: " << contact.GetAge() <<
			"\nName: " << contact.GetName() <<
			"\nPhone: " << contact.GetPhone() << std::endl;
	}
}