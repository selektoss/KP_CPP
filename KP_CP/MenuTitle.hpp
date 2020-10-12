#pragma once
#include <string>
#include <Windows.h>
#include <conio.h>

typedef struct LoBject
{
	typedef struct menuList
	{
		std::wstring nameButton;
		std::wstring txtHelp;
	}button;

	const uint16_t headerHeight = 4, border = 5;
	uint16_t MenuWeight, lineCountTextHelp, sizeMenu, heightContent, weightContent, countColumnTitle;
	uint16_t* ArrLenTitleMenu; uint16_t* minLenColumnSection;
	button* Menu; wchar_t** nameSection;
	COORD  coordXY; WORD consoleATR; wchar_t** infoAddDelete;

	LoBject(void);
	
	
}ModelOBJ;