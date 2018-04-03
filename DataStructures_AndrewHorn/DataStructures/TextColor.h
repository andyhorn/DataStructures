/*
FOREGROUND_BLUE	Text color contains blue.
FOREGROUND_GREEN	Text color contains green.
FOREGROUND_RED	Text color contains red.
FOREGROUND_INTENSITY	Text color is intensified.
BACKGROUND_BLUE	Background color contains blue.
BACKGROUND_GREEN	Background color contains green.
BACKGROUND_RED	Background color contains red.
BACKGROUND_INTENSITY	Background color is intensified.
COMMON_LVB_LEADING_BYTE	Leading byte.
COMMON_LVB_TRAILING_BYTE	Trailing byte.
COMMON_LVB_GRID_HORIZONTAL	Top horizontal.
COMMON_LVB_GRID_LVERTICAL	Left vertical.
COMMON_LVB_GRID_RVERTICAL	Right vertical.
COMMON_LVB_REVERSE_VIDEO	Reverse foreground and background attributes.
COMMON_LVB_UNDERSCORE	Underscore.

https://docs.microsoft.com/en-us/windows/console/console-screen-buffers#_win32_character_attributes
*/


#pragma once

#include <iostream>
#include <Windows.h>

using std::ostream;

inline ostream& redOnBlack(ostream &stream)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_INTENSITY);

	return stream;
}

inline ostream& whiteOnBlack(ostream &stream)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	return stream;
}

inline ostream& greenOnBlack(ostream &stream)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	return stream;
}

inline ostream& blueOnBlack(ostream &stream)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	return stream;
}

inline ostream& yellowOnBlack(ostream &stream)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	return stream;
}

inline ostream& cyanOnBlack(ostream &stream)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);

	return stream;
}

inline ostream& magentaOnBlack(ostream &stream)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	return stream;
}

inline ostream& blackOnWhite(ostream &stream)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);

	return stream;
}

inline ostream& redOnWhite(ostream &stream)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
		| FOREGROUND_RED | FOREGROUND_INTENSITY);

	return stream;
}

inline ostream& blueOnWhite(ostream &stream)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE |
		FOREGROUND_BLUE | FOREGROUND_INTENSITY);

	return stream;
}