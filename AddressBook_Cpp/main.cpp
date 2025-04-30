#include <iostream>
#include <Windows.h>
#include <string>
#include "common.h"
#include "contact.h"
#include "contact_store.h"
#include "file_manager.h"
#include "ui_manager.h"
#include "ui_event_manager.h"

int main(void)
{
	CreateDirectory(L".\\tests", NULL);

	UIEventManager::PrintAll(FileManager::GetTestFilePath().c_str());
	
	return 0;
}