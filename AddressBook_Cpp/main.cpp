#include <iostream>
#include "common.h"
#include "contact.h"
#include "contact_store.h"

int main(void)
{
	Contact* c1 = new Contact(10, "A", "010-0000-1111");
	Contact c2(20, "B", "010-0000-2222");

	std::cout << "Age: " << c1->GetAge() <<
		"\nName: " << c1->GetName() <<
		"\nPhone: " << c1->GetPhone() << std::endl;

	ContactStore* store = new ContactStore();
	store->Insert(*c1);
	store->Insert(c2);

	store->Print();

	delete c1;
	delete store;
	return 0;
}