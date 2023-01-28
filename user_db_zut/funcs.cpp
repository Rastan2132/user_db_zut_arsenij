#include "Header.h"
bool isalpha_r(unsigned char a)
{
	bool rez = ((a >= 'a' && a <= 'z') || (a >= 'A' && a <= 'Z') || a == '-');
	rez |= (a >= (unsigned char)'а' && a <= (unsigned char)'я') || (a >= (unsigned char)'А' && a <= (unsigned char)'Я');
	rez |= (strchr("ёЁіІїЇєЄ`", a) > 0);
	return rez;
}

bool isdigit_r(unsigned char a) { return (a >= '0' && a <= '9'); }


void show(Users_book* pb, short size)
{
	system("cls");
	cout << "----------------------------------------------------------------------------------------------------\n";
	cout << MENU << endl;
	cout << "----------------------------------------------------------------------------------------------------\n";
	cout << "				    ---=== USER BOOK ===---            your Users: " << size << endl;
	cout << "----------------------------------------------------------------------------------------------------\n";
	cout << stru << endl;
	cout << "----------------------------------------------------------------------------------------------------\n";
	for (short i = 0; i < size; i++)
	{
		// if (i < 9) cout << "0";
		cout << right << setw(3) << setfill('0') << i + 1 << setfill(' ') << " " << MANIP << pb[i].Name << " " << MANIP << pb[i].Surname << "  " << MANIP << pb[i].Year << MANIP << pb[i].piesel << MANIP << pb[i].sex << "\n";
	}
}

Users_book* add(Users_book* pb, short* size)
{

	pb = resize(pb, size, (*size) + 1);


	record(pb[(*size) - 1].Name, 2, " Name: ", false, false, false);
	cout << endl;
	record(pb[(*size) - 1].Surname, 3, " Surname: ", false, false, false);
	cout << endl;
	record(pb[(*size) - 1].Year, 4, " Year: ", false, 1, false);
	cout << endl;
	record(pb[(*size) - 1].piesel, 11, " Num pesilu: ", false, 1, false);
	cout << endl;
	record(pb[(*size) - 1].sex, 2, " Sex: ", false, false, false);
	cout << endl;
	return pb;
}

Users_book* del(Users_book* pb, short* size)
{

	bool work = 1;
	system("cls");

	cout << "Are you sure that you want to delete last user?" << endl;
	cout << "Press (y) if you sure, press (n) if you are not" << endl;

	do {
		switch (_getch()) {

		case(121)://YES 

			if (*size > 0)
			{
				pb = resize(pb, size, *size - 1, *size);
				cout << "User was successfully deleted" << endl;
				cout << "press to continue" << endl;
				system("pause");

				return pb;
			}
			else {
				error();
				work = 0;
			}


			break;

		case(110):// No

			work = 0;
			return pb;

			break;
		}




	} while (work);

}

Users_book* edit(Users_book* pb, short size, short index, bool menu)
{
	system("cls");

	if (size == 0 || index < 0 || index >= size)
	{
		error();
		return pb;
	}

	do
	{
		system("cls");
		cout << "Uzytkownik #" << index + 1 << endl << endl;
		cout << "Enter name: ";
		stredit(pb[index].Name, MAXLINE, 20, 2);

	} while (strlen(pb[index].Name) == 0);

	do
	{
		system("cls");
		cout << "Uzytkownik #" << index + 1 << endl << endl;
		cout << "Enter Year: ";
		stredit(pb[index].Year, MAXLINE, 20, 2);
	} while (strlen(pb[index].Year) == 0);

	do
	{
		system("cls");
		cout << "Uzytkownik #" << index + 1 << endl << endl;
		cout << "Enter Surname: ";
		stredit(pb[index].Surname, MAXLINE, 20, 2);

	} while (strlen(pb[index].Surname) == 0);
	do
	{
		system("cls");
		cout << "Uzytkownik #" << index + 1 << endl << endl;
		cout << "Enter Pesel: ";
		stredit(pb[index].piesel, MAXLINE, 20, 2);

	} while (strlen(pb[index].piesel) == 0);
	do
	{
		system("cls");
		cout << "Uzytkownik #" << index + 1 << endl << endl;
		cout << "Enter sex: ";
		stredit(pb[index].sex, MAXLINE, 20, 2);

	} while (strlen(pb[index].sex) == 0);

	system("cls");
	if (menu) cout << "Edited!" << endl;

	return pb;
}


void setCursorPosition(int x, int y)
{
	static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	std::cout.flush();
	COORD coord = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(hOut, coord);
}

Users_book* resize(Users_book* pb, short* size, short size_n, short num)
{
	Users_book* pbn;
	pbn = new Users_book[size_n];
	short min = *size;
	// if (size_n < min) min = size_n; // not need now
	for (int i = 0; i < min; i++)
		if (i != num - 1) {
			strcpy(pbn[i].Name, pb[i].Name);
			strcpy(pbn[i].Year, pb[i].Year);
			strcpy(pbn[i].Surname, pb[i].Surname);
			strcpy(pbn[i].sex, pb[i].sex);
			strcpy(pbn[i].piesel, pb[i].piesel);
		}
	*size = size_n;
	delete[] pb;
	return pbn;
}

bool record(char* p, unsigned short min, const char* prompt, bool chkAlpha, bool chkDigit, bool chkFirst)
{
	
	char s[MAXSTRLЕN] = "";
	size_t n, i;
	bool loop;
	cout << prompt;
	COORD start = getCursorPosition();
	do
	{
		Clear(start.X, start.Y, MAXLINE);
		loop = true;
		strncpy(s, p, MAXLINE - 1);
		stredit(s, MAXLINE, start.X, start.Y);		// cin >> s;
		if (strlen(s) < 1) return false;			// !!!
		strncpy(p, s, MAXLINE - 1);
		p[MAXLINE - 1] = '\0';
		n = strlen(p);
		for (i = 0; i < n; i++)
			if (chkAlpha || (chkDigit && !isdigit_r(p[i])))	//  isdigit((unsigned char)p[i])
				break;
		if (i != n || n < min || (chkFirst && isdigit_r(p[0])))
		{
			Beep(BEEP_TONE, BEEP_DURATION);
			Sleep(50);
		}
		else loop = false;
	} while (loop);
	
	return true;
}
int select(Users_book* pb, short size)
{
	if (size == 0) return -1;
	if (size == 1) return 0;

	int index = 0;
	do
	{
		show(pb, size);
		cout << "Numer uzytkownik: ";
		if (cin >> index)
		{
			if (index >= 1 && index <= size) break;
		}
		else
		{
			cin.clear();
			while (cin.get() != '\n');
		}
	} while (true);

	return index - 1;
}
void bookSwap(Users_book* a, Users_book* b) // ?
{
	Users_book* tmp;

	tmp = a;
	a = b;
	b = tmp;
}
Users_book* init(Users_book* pb, short* size)
{
	ifstream in;
	int i = 0;
	in.open("Users_book.txt", ios::in);
	if (!in.is_open())
	{
		*size = -1;	// if error *size = -1;
		return pb;
	}

	while (!in.eof())
	{
		pb = resize(pb, size, (*size) + 1);
		i = *size - 1;
		in >> pb[i].Name >> pb[i].Surname >> pb[i].Year >> pb[i].piesel >> pb[i].sex;
	}

	in.close();
	return pb;
}
bool save(Users_book* pb, short* size)
{
	ofstream out;

	out.open("Users_book.txt", ios::out);
	if (!out.is_open())
		return false;

	for (int i = 0; i < *size; i++)
	{
		out << pb[i].Name << " " << pb[i].Surname << " " << pb[i].Year << " " << pb[i].piesel << " " << pb[i].sex;
		if (i < *size - 1) out << endl;
	}

	out.close();
	return true;
}
void error()
{
	Beep(880, 150);
	cout << "ERROR!" << endl << endl;
	system("pause");
}
Users_book* sort(Users_book* pb, short size)
{



	char v;
	cout << endl << "Wybiesz:\n1 - posortowac za Name\n2 - posortowac za Year\n3 - posortowac za Surname\n - posortowac za pesel\n3 - posortowac za Sex\nQ - Wyjść\n"; v = _getch();
	cout << endl;
	switch (v)
	{
	case '1':
		for (short i = 0; i < size; i++) {
			for (short j = i + 1; j < size; j++) {
				if (strcmp(pb[i].Name, pb[j].Name) > 0) {
					swap(pb[i].Name, pb[j].Name);
					swap(pb[i].Surname, pb[j].Surname);
					swap(pb[i].Year, pb[j].Year);
					swap(pb[i].sex, pb[j].sex);
					swap(pb[i].piesel, pb[j].piesel);

				}
			}
		}
		cout << endl << "Sorted" << endl;
		system("pause");
		break;
	case '2':
		for (short i = 0; i < size; i++) {
			for (short j = i + 1; j < size; j++) {
				if (strcmp(pb[i].Year, pb[j].Year) > 0) {
					swap(pb[i].Name, pb[j].Name);
					swap(pb[i].Surname, pb[j].Surname);
					swap(pb[i].Year, pb[j].Year);
					swap(pb[i].sex, pb[j].sex);
					swap(pb[i].piesel, pb[j].piesel);
				}
			}
		}
		cout << endl << "Sorted" << endl;
		system("pause");
		break;
	case '3':
		for (short i = 0; i < size; i++) {
			for (short j = i + 1; j < size; j++) {
				if (strcmp(pb[i].Surname, pb[j].Surname) > 0) {
					swap(pb[i].Name, pb[j].Name);
					swap(pb[i].Surname, pb[j].Surname);
					swap(pb[i].Year, pb[j].Year);
					swap(pb[i].sex, pb[j].sex);
					swap(pb[i].piesel, pb[j].piesel);
				}
			}
		}
	case '4':
		for (short i = 0; i < size; i++) {
			for (short j = i + 1; j < size; j++) {
				if (strcmp(pb[i].piesel, pb[j].piesel) > 0) {
					swap(pb[i].Name, pb[j].Name);
					swap(pb[i].Surname, pb[j].Surname);
					swap(pb[i].Year, pb[j].Year);
					swap(pb[i].sex, pb[j].sex);
					swap(pb[i].piesel, pb[j].piesel);
				}
			}
		}
	case '5':
		for (short i = 0; i < size; i++) {
			for (short j = i + 1; j < size; j++) {
				if (strcmp(pb[i].sex, pb[j].sex) > 0) {
					swap(pb[i].Name, pb[j].Name);
					swap(pb[i].Surname, pb[j].Surname);
					swap(pb[i].Year, pb[j].Year);
					swap(pb[i].sex, pb[j].sex);
					swap(pb[i].piesel, pb[j].piesel);
				}
			}
		}
		cout << endl << "Sorted" << endl;
		system("pause");
		break;
	case 'q':
	case 'Q':
	case 'й':
	case 'Й':
		break;
	default:
	{
		cout << endl << "Paush 1, 2, 3 or Q " << endl;
		system("pause");
	}
	}
	return pb;

}

void find(Users_book* pb, short size)
{
	if (pb == nullptr || size == 0)
	{
		error();
		return;
	}

	char* keyword = new char[MAXLINE]; keyword[0] = '\0';

	COORD enter, hat;

	system("cls");
	cout << " Esc - Wejscie" << endl << endl;
	cout << "Szukaj: ";
	enter = getCursorPosition();

	cout << endl << stru << endl;
	hat = getCursorPosition();

	COORD temp_pos;
	short len = 0;

	do
	{
		//Вводим ключевое слово для поиска.
		{
			int i = 0;
			do
			{

				if (!stredit(keyword, MAXLINE, enter.X, enter.Y, len, false)) return;
				len = (short)strlen(keyword);

				for (i = 0; i < len; i++)
				{
					if (!(isdigit_r(keyword[i]) || isalpha_r(keyword[i]))) break;
				}

			} while (i != len || len == 0);
		}

		/* Выводим результаты. */

		setCursorPosition(hat.X, hat.Y);

		//Очищаем предыдущие результаты поиска.
		for (int i = 0; i < size; i++)
		{
			temp_pos = getCursorPosition();
			Clear(temp_pos.X, temp_pos.Y + i);
		}
		setCursorPosition(hat.X, hat.Y);

		//Выводим новые результаты поиска
		for (int i = 0; i < size; i++)
		{
			if (strstr_lower(pb[i].Name, keyword)
				|| strstr_lower(pb[i].Surname, keyword)
				|| strstr_lower(pb[i].sex, keyword)
				|| strstr_lower(pb[i].piesel, keyword)
				|| strstr_lower(pb[i].Year, keyword))
			{
				cout << left << setw(3) << i + 1 << "  ";
				print_find(pb[i].Name, MAXLINE, keyword, MAXLINE, Red);
				print_find(pb[i].Surname, MAXLINE, keyword, MAXLINE, Red);
				print_find(pb[i].Year, MAXLINE, keyword, MAXLINE, Red);
				print_find(pb[i].sex, MAXLINE, keyword, MAXLINE, Red);
				print_find(pb[i].piesel, MAXLINE, keyword, MAXLINE, Red);

				cout << endl;
			}
		}

	} while (true); //Пока не нажата клавиша Escape.

	delete[] keyword; keyword = nullptr;
}
void print_find(char* str, short str_size, char* keyword, short key_size, int text, int back)
{
	if (str == nullptr || keyword == nullptr) return;

	int str_len = strlen(str);
	int key_len = strlen(keyword);

	if (str_len > str_size || str_len < 0 || key_len > key_size || key_len < 0) return;

	COORD start, cursor;

	start = getCursorPosition();
	cout << left << setw(str_size) << str;
	cursor = getCursorPosition();
	showcursor(false);

	COLOR DefColor = GetColor();
	COLOR FindColor;

	FindColor.text = (text == -1) ? DefColor.text : text;
	FindColor.back = (back == -1) ? DefColor.back : back;

	char* ptr = strstr_lower(str, keyword);
	short index = 0;

	while (ptr != nullptr)
	{
		index = (int)(ptr - str);                    //Считаем позицию слова в строке и 
		setCursorPosition(start.X + index, start.Y); //переходим к позиции слова.

													 // Выводим слово с форматом цвета.
		SetColor(FindColor);
		for (int j = 0; j < key_len; j++) cout << str[index + j];
		SetColor(DefColor);

		//Ищем далее.
		ptr = strstr_lower(ptr + key_len, keyword);
	}

	setCursorPosition(cursor.X, cursor.Y);
	showcursor(true);
}
char* strstr_lower(char* str_a, char* str_b)
{
	/*Поиск подстроки в строке без учета регистра.*/

	if (str_a == nullptr || str_b == nullptr)
		return nullptr;

	for (int i = 0;; i++)
	{
		if (str_a[i] == '\0') return nullptr;

		for (int j = 0, k = i;; j++, k++)
		{
			if (str_b[j] == '\0') return (str_a + i);
			if (tolower(str_a[k]) != tolower(str_b[j])) break;
		}
	}
}


void SetColor(COLOR Color)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, (WORD)(Color.back << 4 | Color.text));
}
COLOR GetColor()
{
	COLOR Color;
	WORD word = GetColorWord();
	Color.back = (int)(word >> 4);
	Color.text = (int)word - (Color.back << 4);
	return Color;
}
WORD GetColorWord()
{
	WORD text_atribute;
	CONSOLE_SCREEN_BUFFER_INFO info;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOut, &info);
	text_atribute = info.wAttributes;
	return text_atribute;
}

void InsertCh(char* str, int buffer_size, int& cursor, int& term, char symb)
{
	if (cursor == buffer_size - 1) return;
	if (term != buffer_size - 1) term++;
	for (int i = term - 1; i > cursor; i--)
		str[i] = str[i - 1];



	str[cursor++] = symb;
	str[term] = '\0';
}
void DeleteCh(char* str, int& cursor, int& term)
{
	if (cursor < 1) return;



	for (int i = cursor-- - 1; i < term; i++)
		str[i] = str[i + 1];



	str[term--] = ' ';
}
void Clear(int x, int y, long cnt)
{
	showcursor(false);
	setCursorPosition(x, y);
	for (int i = 0; i < cnt; i++)
		std::cout << " ";
	setCursorPosition(x, y);
	showcursor(true);
}



bool stredit(char* str, int buffer_size, int x, int y, int cursor, bool clear_after)
{
	/*Функция возвращает true в случае успеха редактиования, иначе - false.*/
	/*
	str - строка для редактирования.
	buffer_size - размер буфера строки.
	x, y = координаты редактора в консоли.
	cursor - начальное смещение курсора.
	clear_after - очищать ли строку после редактирования?
	*/
	if (buffer_size <= 0) return false;
	if (cursor >= buffer_size) return false;



	COORD size = getConsoleSize();
	if (x < 0 || x >= size.X || y < 0 || y >= size.Y)
	{
		COORD pos = getCursorPosition();
		x = pos.X;
		y = pos.Y;
	}
	int term = 0;
	while (str[term] != '\0') //Поиск терминатора
	{
		if (++term >= buffer_size) //Если в строке нет терминатора, ставим его по умолчанию
		{
			term = 0;
			str[term] = '\0';
		}
	}
	if (cursor > term) cursor = term;
	//Сохраняем строку до редактирования.
	char* backup = new char[buffer_size];
	strcpy(backup, str);
	unsigned press;
	bool edit;
	bool sucess; //Возвращаемое значение. True - строка изменена. False - строка не изменена. 
	do
	{
		showcursor(false);
		setCursorPosition(x + term, y); cout << ' ';
		showcursor(true);
		setCursorPosition(x, y); cout << str;
		setCursorPosition(x + cursor, y);
		edit = true;
		press = _getch();
		switch (press)
		{
		case Esc:
			strcpy(str, backup);
			sucess = false;    //Строка  не отредактированна.
			edit = false;
			break;
		case Enter:
			sucess = true;  //Строка отредактированна.
			edit = false;
			break;
		case Backspace:
			DeleteCh(str, cursor, term);
			break;
		case 0:
		case 224:
			//Для специальных клавиш передается два кода - 224 (или 0) и код клавиши, но буква 'a' тоже имеет код 224
			if (_kbhit()) //Если дальше следует код, то это специальная клавиша. Иначе это буква 'а' русская
			{
				press = _getch();
				switch (press)
				{
				case Left:
					if (cursor > 0) cursor--;
					break;
				case Right:
					if (cursor < term) cursor++;
					break;
				case End:
					cursor = term;
					break;
				case Del:
					backup[0] = '\0';
					strcpy(str, backup);
					Clear(x, y, buffer_size);
					term = 0;
				case Home:
					cursor = 0;
					break;
				}
				break;
			}
		default:
			InsertCh(str, buffer_size, cursor, term, char(press));
			break;
		}
	} while (edit);



	if (clear_after) Clear(x, y, buffer_size);
	press = cursor = term = edit = 0;



	if (backup != nullptr)
	{
		delete[] backup;
		backup = nullptr;
	}



	return sucess;
}

COORD getConsoleSize()
{
	COORD size;
	_CONSOLE_SCREEN_BUFFER_INFO info;
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOut, &info);
	size.X = info.srWindow.Right - info.srWindow.Left + 1;
	size.Y = info.srWindow.Bottom - info.srWindow.Top + 1;
	return size;
}
void showcursor(bool flag)
{
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	GetConsoleCursorInfo(hOut, &info);
	// info.dwSize = 20;
	info.bVisible = flag;
	SetConsoleCursorInfo(hOut, &info);
}