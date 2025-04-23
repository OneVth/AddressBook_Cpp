#include <iostream>
#include "common.h"
#include "contact.h"
#include "contact_store.h"
#include "json.hpp"

int main(void)
{
	Contact contact(10, "Alice", "010-0000-1111");

	nlohmann::json j;

	j["age"] = contact.GetAge();
	j["name"] = contact.GetName();
	j["phone"] = contact.GetPhone();

	std::cout << "Serialized JSON: " << j.dump(4) << std::endl;
	return 0;
}