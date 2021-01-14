#include "__CurPosition__.hpp"
#include <Windows.h>
#include "MenuTitle.hpp"
#include <iostream>
#include "color.hpp"

void ShowCursor(bool value)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = value;
	SetConsoleCursorInfo(out, &cursorInfo);
}

void SetCurPos(const uint16_t& x, const uint16_t& y)
{
	COORD positionXY;
	positionXY.X = x; positionXY.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), positionXY);
};

void ReClearScreenContentBoxDraw(const ModelOBJ* form)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BBLACK | BG | BB | BR );
	for (uint16_t iter = 0; iter < form->heightContent; ++iter)
	{
		SetCurPos(form->border + 1, form->coordXY.Y + iter - (form->heightContent + form->border));
		std::cout << std::string(form->weightContent - 2, ' ');
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), form->consoleATR);
	setlocale(LC_ALL, "");
};