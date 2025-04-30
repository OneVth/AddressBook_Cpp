#pragma once

#include <Windows.h>
#include <queue>
#include <functional>

class UIEventManager
{
private:
	std::queue<std::function<void()>> eventQueue;
public:
	enum Option
	{
		MENU_EXIT = 0,
		MENU_PRINT_ALL,
		MENU_INSERT,
		MENU_DELETE,
		MENU_SEARCH,
		MENU_EDIT,
		UI_FUNC_COUNT
	};

	UIEventManager() = default;
	~UIEventManager() = default;

	static void PrintAll(LPCWSTR path);
	static void InsertNode(LPCWSTR path);
	static void DeleteNode(LPCWSTR path);
	static void SearchNode(LPCWSTR path);
	static void EditNode(LPCWSTR path);
	static void Exit(LPCWSTR path);

	typedef void (*MenuFunction)(LPCWSTR);
	static MenuFunction menuFunctions[UI_FUNC_COUNT];

	static void RunEventLoop(LPCWSTR path);
};