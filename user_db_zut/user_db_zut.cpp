#include "Header.h"

#define _CRT_SECURE_NO_WARNINGS


int main()
{
	setlocale(0, "Rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	system("mode con cols=100 lines=40");
	system("color 3F");

	char cmd;
	short size = 0;

	Users_book* pb = nullptr;
	bool work = true;

	pb = init(pb, &size);
	if (size < 0)
	{
		error();
		size = 0;
	}

	do
	{
		show(pb, size);
		cmd = _getch();
		switch (cmd)
		{
		case (113):
			work = false;
			break;
		case (97):
			pb = add(pb, &size);
			break;
		case (100):
			pb = del(pb, &size);
			break;
		case (101):
			pb = edit(pb, size, select(pb, size), true);
			break;
		case (115):
			sort(pb, size);
			break;
		case (121):
			find(pb, size);
			break;
		case (102):
			if (!_kbhit())
			{
				break;
			}
		default:
			if (_kbhit()) _getch();
			break;
		}
	} while (work);
	if (!(work = save(pb, &size)))	// save
		error();

	delete[] pb;

	cout << endl << endl;
	return !(work);
}
