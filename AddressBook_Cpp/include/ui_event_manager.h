#pragma once
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

	static void PrintAll();
	static void InsertNode();
	static void DeleteNode();
	static void SearchNode();
	static void EditNode();
	static void Exit();

	typedef void (*MenuFunction)(void);
	static MenuFunction menuFunctions[UI_FUNC_COUNT];

	static void RunEventLoop();
};