#include "__CurPosition__.hpp"
#include <Windows.h>

void SetCurPos(const uint16_t& x, const uint16_t& y)
{
	COORD positionXY;
	positionXY.X = x; positionXY.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), positionXY);
};
void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	csbi.dwSize.X = 12; csbi.dwSize.Y = 10;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR)' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;

	
	SetConsoleCursorPosition(hStdOut, homeCoords);
};