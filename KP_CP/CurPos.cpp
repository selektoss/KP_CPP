#include "__CurPosition__.hpp"
#include <Windows.h>
#include "MenuTitle.hpp"
#include <iostream>

void SetCurPos(const uint16_t& x, const uint16_t& y)
{
	COORD positionXY;
	positionXY.X = x; positionXY.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), positionXY);
};

void ReClearScreenContentBoxDraw(ModelOBJ& form)
{
	for (uint16_t iter = 0; iter < form.heightContent; ++iter)
	{
		SetCurPos(form.border + 1, form.coordXY.Y + iter - (form.heightContent + form.border));
		std::cout << std::string(form.weightContent - 1, '\xDB');
	}
};