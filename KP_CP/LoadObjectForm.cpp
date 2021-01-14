#include "__GetData__.hpp"
#include "__Get_SetSizeConsole__.hpp"
#include "__MainForm__.hpp"
#include "__CurPosition__.hpp"
#include <iostream>
#include "UpdateContentBox.hpp"

#define  FG FOREGROUND_GREEN
#define  FR FOREGROUND_RED
#define  FB FOREGROUND_BLUE

#define  BG BACKGROUND_GREEN
#define  BR BACKGROUND_RED
#define  BB BACKGROUND_BLUE

#define BBLACK 0x000

ModelOBJ*& LoadObjectForm(char*& keyDataBinHeader)
						
{
	ShowCursor(false); 
	ModelOBJ* form(new ModelOBJ); 
	form->coordXY = ConsoleSize();
	wchar_t* titleContent(nullptr);
	keyDataBinHeader = GetDataResourceMenu(form, titleContent, form->nameSection);
	DrawMenuBox(form->coordXY, form->sizeMenu, form->border, form->ArrLenTitleMenu, form->MenuWeight, form->Menu);
	DrawHelpTextBox(form);
	DrawContentDataBox(form, titleContent, form->nameSection);
	return form;
};

void UpdateMenu(const ModelOBJ* form, const int& chois)
{
	static short int check(0);
	uint16_t XYtemp[2] = { static_cast<uint16_t>(form->coordXY.X - (form->border + (form->MenuWeight))),
	static_cast<uint16_t>(form->coordXY.Y - (form->border + form->sizeMenu)) };

	SetCurPos(*XYtemp, *(XYtemp + 1));
	using namespace std;

	for (int iter(0); iter < form->sizeMenu; ++iter)
	{
		if (iter == chois)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG | BG | BB | BR);
			SetCurPos(*XYtemp, (*(XYtemp + 1)) + iter);
			cout << string(form->MenuWeight, ' ');
			SetCurPos(((form->coordXY.X - (form->border + (form->MenuWeight >> 1))) - ((*(form->ArrLenTitleMenu + iter)) >> 1)),
				*(XYtemp + 1) + iter);
			wcout << form->Menu[iter].nameButton;

			if (check)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FB | FG | FR | BG);
				if ((iter - 1) >= 0)
				{
					SetCurPos(*XYtemp, (*(XYtemp + 1)) + (iter - 1));
					cout << string(form->MenuWeight, ' ');
					SetCurPos(((form->coordXY.X - (form->border + (form->MenuWeight >> 1))) - ((*(form->ArrLenTitleMenu + (iter - 1))) >> 1)),
						(*(XYtemp + 1)) + (iter - 1));
					wcout << form->Menu[iter - 1].nameButton;
					if (iter == 7)
					{
						SetCurPos(*XYtemp, (*(XYtemp + 1)));
						cout << string(form->MenuWeight, ' ');
						SetCurPos(((form->coordXY.X - (form->border + (form->MenuWeight >> 1))) - ((*(form->ArrLenTitleMenu)) >> 1)),
							*(XYtemp + 1));
						wcout << form->Menu[0].nameButton;
					}	
				}
				if (iter < form->sizeMenu - 1)
					{
						SetCurPos(*XYtemp, (*(XYtemp + 1)) + (iter + 1));
						cout << string(form->MenuWeight, ' ');
						SetCurPos(((form->coordXY.X - (form->border + (form->MenuWeight >> 1))) - ((*(form->ArrLenTitleMenu + (iter + 1))) >> 1)),
							(*(XYtemp + 1)) + (iter + 1));
						wcout << form->Menu[iter + 1].nameButton;

						if (!iter)
						{
							SetCurPos(*XYtemp, (*(XYtemp + 1)) + ((form->sizeMenu - 1)));
							cout << string(form->MenuWeight, ' ');
							SetCurPos(((form->coordXY.X - (form->border + (form->MenuWeight >> 1))) - ((*(form->ArrLenTitleMenu + (form->sizeMenu - 1))) >> 1)),
								(*(XYtemp + 1)) + (form->sizeMenu - 1));
							wcout << form->Menu[(form->sizeMenu - 1)].nameButton;				
						}
				}
			}
			uint16_t lenghtStrHelpTxt = static_cast<uint16_t>(form->Menu[iter].txtHelp.length());
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FB | FG | FR | BBLACK);

			for (uint16_t iterV(0), nextPosition(0); iterV < form->lineCountTextHelp - 1; ++iterV,
				nextPosition += (form->MenuWeight - 2))
			{
				SetCurPos((*XYtemp) + 1,
					(form->coordXY.Y - ((form->border + 3) + form->sizeMenu + (form->lineCountTextHelp - 1) - iterV)));
				cout << string((form->MenuWeight - 2), '\x20');
				if (nextPosition < lenghtStrHelpTxt)
				{
					SetCurPos(form->coordXY.X - (form->border + (form->MenuWeight - 1)),
						(form->coordXY.Y - ((form->border + 3) + form->sizeMenu + (form->lineCountTextHelp - 1) - iterV)));
					wcout << form->Menu[iter].txtHelp.substr(nextPosition, (form->MenuWeight - 2));
				}
			}
			if(!(check < form->sizeMenu))break;
		}
		else if (check < form->sizeMenu)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FB | FG | FR | BG);
			SetCurPos(*XYtemp, (*(XYtemp + 1)) + iter);
			cout << string(form->MenuWeight, '\x20');
			SetCurPos(((form->coordXY.X - (form->border + (form->MenuWeight >> 1))) - ((*(form->ArrLenTitleMenu + iter)) >> 1)),
				(*(XYtemp + 1)) + iter);
			wcout << form->Menu[iter].nameButton;
			++check;
		}
	}
};

int ChoisMenu(ModelOBJ*& form, List* Employee)
{
	static int chois(0);

	while (true && form)
	{
		UpdateMenu(form, chois);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), form->consoleATR);
		while (int key = _getch())
		{
			if (key > 90) continue;
			if (GetAsyncKeyState(VK_UP) != 0)
			{
				chois -= 1; if (chois < 0) chois = (form->sizeMenu - 1);
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{
				++chois; if (chois == form->sizeMenu) chois = 0;
				break;
			}
			else if (GetAsyncKeyState(VK_LEFT) != 0)
			{
				if(choisListContent(form, Employee))
				break;
			}
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				if (chois == (form->sizeMenu - 1))
				{
					DeleteObjModel(form);
				}	
				return chois;
			}
		}
	}
};
