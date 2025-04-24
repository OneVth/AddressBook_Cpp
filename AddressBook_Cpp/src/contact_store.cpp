#include "contact_store.h"

bool ContactStore::Insert(const Contact& contact)
{
	auto result = contacts.insert({ contact.GetPhone(), contact });
	return result.second;
}

void ContactStore::forEach(const std::function<void(const Contact&)>& callback) const
{
	for (const auto& pair : contacts)
	{
		callback(pair.second);
	}
}