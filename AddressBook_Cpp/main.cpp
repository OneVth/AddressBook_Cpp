#include <iostream>
#include "common.h"
#include "contact.h"

int main(void)
{
	Contact* c = new Contact(10, "A", "010-0000-1111");

	std::cout << "Age: " << c->GetAge() <<
		"\nName: " << c->GetName() <<
		"\nPhone: " << c->GetPhone() << std::endl;
	return 0;
}