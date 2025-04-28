#include <iostream>
#include <Windows.h>
#include "common.h"
#include "contact.h"
#include "contact_store.h"
#include "file_manager.h"
#include "ui_manager.h"
#include "ui_event_manager.h"

int main(void)
{
	CreateDirectory(L".\\tests", NULL);
	
	UIManager::PrintMenu();
	
	return 0;
}