#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <fstream>
#include <ctype.h>
#include <windows.h>
#define MANIP setw(MAXLINE) <<  left 

#define MENU "| q-Zamkac |  a-ADD uzytkownika  |  d-Usuwanie uzytkownika |  e-Redaktor |  s-Sortowac |  y-Szukaj |" 
#define stru "¹   Name                           Surname		           Year"
#define MAXLINE 20
#define BEEP_TONE 880
#define BEEP_DURATION 100
#define MAXSTRLÅN 80

using namespace std;

struct Users_book
{
	char Name[MAXLINE] = "";
	char Surname[MAXLINE] = "";
	char Year[MAXLINE] = "";
	char piesel[MAXLINE] = "";
	char sex[MAXLINE] = "";
};
struct COLOR
{
	short text;
	short back;
};
enum ConsoleColor
{
	Black = 0, Blue, Green, Cyan, Red, Magenta, Brown, LightGray, DarkGray,
	LightBlue, LightGreen, LightCyan, LightRed, LightMagenta, Yellow, White
};

COORD getConsoleSize();


void SetColor(COLOR Color);
WORD GetColorWord();
COLOR GetColor();
void Clear(int x, int y, long cnt = 100);
bool stredit(char* str, int buffer_size, int x, int y, int cursor = 0, bool clear_after = true);
char* strstr_lower(char* str_a, char* str_b);
void print_find(char* str, short str_size, char* keyword, short key_size, int text = -1, int back = -1);
void setCursorPosition(int x, int y);
COORD getCursorPosition(void);
void showcursor(bool flag);
enum Keys { Enter = 13, Backspace = 8 };
enum SpecialKeys { Left = 75, Right = 77, End = 79, Home = 71, Esc = 27, Del = 83 };
void show(Users_book*, short);
Users_book* add(Users_book*, short* size);
Users_book* del(Users_book* pb, short* size);
Users_book* edit(Users_book* pb, short size, short index, bool menu);
void find(Users_book* pb, short size);
Users_book* sort(Users_book* pb, short size);
Users_book* resize(Users_book* pb, short* size, short, short num = 0);
bool record(char* p, unsigned short min, const char* prompt, bool chkAlpha, bool chkDigit, bool chkFirst);
void bookSwap(Users_book*, Users_book*);	// ?
void error();
void InsertCh(char* str, int buffer_size, int& cursor, int& term, char symb);
void DeleteCh(char* str, int& cursor, int& term);
int select(Users_book* pb, short size);
Users_book* init(Users_book* pb, short* size);
bool save(Users_book* pb, short* size);
