#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h>
#include <WinUser.h>	/

#define MAXSTRLÅN 80

using namespace std;

void showCursor(bool flag)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	// info.dwSize = 20;
	info.bVisible = flag;
	SetConsoleCursorInfo(hOut, &info);
}

void setCursorPosition(short x, short y)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

COORD getCursorPosition(void)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	_CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(hOut, &info);
	return info.dwCursorPosition;
}
void InsertCh(char* str, int size, int& cursor, int& term, unsigned char symb)
{
	if (cursor == size - 1) return;
	if (term < size - 1) term++;

	for (int i = term - 1; i > cursor; i--)
		str[i] = str[i - 1];

	str[cursor++] = symb;
	str[term] = '\0';
}

void DeleteCh(char* str, int& cursor, int& term, bool bs = false)
{
	if (term < 1) return;
	if (bs)
	{
		if (cursor < 1) return;
		cursor--;
	}
	for (int i = cursor - 1; i < term; i++)
		str[i] = str[i + 1];

	str[term--] = ' ';
	str[term] = '\0';
}

inline void ClearLine(int x, int y, int cnt = MAXSTRLÅN)
{
	setCursorPosition(x, y);
	for (int i = 0; i < cnt; i++)
		cout << " ";
	setCursorPosition(x, y);
}

