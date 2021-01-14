#include "UpdateContentBox.hpp"
#include "__CurPosition__.hpp"
#include "color.hpp"
#include <iostream>
#include <iomanip>
#include "__AddEmployee__.hpp"
#include "Func.hpp"

void DrawButtonEmployeeChoise(int& chois, uint16_t& x, uint16_t& y, const char(*choisV)[11] , const uint16_t& sizeCase)
{
	ShowCursor(false);
	if (chois < sizeCase)
	{
		for (uint16_t iter(0), lenchois(0); iter < sizeCase; ++iter, lenchois += 11)
		{
			if (iter == chois)
			{
				SetCurPos(x + lenchois, y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG | FB | FR | BG);
				std::cout << choisV[iter];
			}
			else
			{
				SetCurPos(x + lenchois, y);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BBLACK | BG | BB | BR);
				std::cout << choisV[iter];
			}
		}
	}
	else
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		SetCurPos(x, y); while (chois != 0) { std::cout << ' '; --chois; }
	}

};

bool ChoisEmployee(ListItem*& Employee, const ModelOBJ* form, List* list, bool& flag)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); flag = 0;
	SetCurPos(form->border, form->coordXY.Y - (form->border >> 1)); std::cout << std::string(form->weightContent, ' ');
	const WCHAR* info = L"ÄÅÉÑÒÂÈÅ ÍÀÄ ÂÛÁÐÀÍÍÛÌ ÑÎÒÐÓÄÍÈÊÎÌ"; const uint16_t size(3);
	char choisV[size][11] = { " ÓÄÀËÈÒÜ! ", " ÈÇÌÅÍÈÒÜ ", " ÎÒÌÅÍÀ " };
	uint16_t x = form->border;
	uint16_t y = (form->coordXY.Y - (form->border >> 1)); SetCurPos(x, y);
	std::wcout << info; 
	int chois(0); x += (35) + form->border;
	while (true)
	{
		DrawButtonEmployeeChoise(chois, x, y, choisV, size);
		while (int key = _getch())
		{
			if (key > 99) continue;
			
			if (GetAsyncKeyState(VK_LEFT) != 0)
			{
				--chois; if (chois < 0) chois = 2;
				DrawButtonEmployeeChoise(chois, x, y, choisV, size);

				break;
			}
			else if (GetAsyncKeyState(VK_RIGHT) != 0)
			{
				++chois; if (chois == 3) chois = 0;
				DrawButtonEmployeeChoise(chois, x, y, choisV, size);
				break;
			}
			
			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				x = form->border;
				if (chois == 0)
				{
					DeleteEmploye(Employee, list, form, flag); chois = form->coordXY.X; list->flag = 1;
					ShowInfoParamEmployee(list->begin, form);
					DrawButtonEmployeeChoise(chois, x, y, choisV, size);
					return true;
				}
				else if(chois == 1)
				{
					EditEmploye(Employee, form); chois = form->coordXY.X;
					ShowInfoParamEmployee(list->begin, form);
					DrawButtonEmployeeChoise(chois, x, y, choisV, size);
					return false;
				}
				else if (chois == 2)
				{
					chois = form->coordXY.X;
					DrawButtonEmployeeChoise(chois, x, y, choisV, size);
					return false;
				}
			}
		}
	}
};

void CoutList(const ListItem* Employee, const ModelOBJ* form)
{
	
	setlocale(LC_ALL, ""); 
	const wchar_t gen[2][8] = { L"Ìóæñêîé", L"Æåíñêèé" };
	std::wcout << std::setw(form->minLenColumnSection[0] - 1) << std::left << Employee->EmployeeInfo.idPerson << L"|";

	std::wcout
		<< std::setw(form->minLenColumnSection[1] - 1) << std::left << Employee->EmployeeInfo.SNM << L"|"
		<< std::setw(form->minLenColumnSection[2] - 1) << std::left << Employee->EmployeeInfo.specialty << L"|"
		<< std::setw(form->minLenColumnSection[3] - 1) << std::left << Employee->EmployeeInfo.DOB << L"|";
	if (Employee->EmployeeInfo.gender)
		std::wcout << std::setw(form->minLenColumnSection[4] - 1) << std::left << gen[1] << L"|";
	else std::wcout << std::setw(form->minLenColumnSection[4] - 1) << std::left << gen[0] << L"|";
	std::wcout << std::setw(form->minLenColumnSection[5] - 1U) << std::left <<
		Employee->EmployeeInfo.infoWork.expervalue.experYear << L"|"
		<< std::setw(form->minLenColumnSection[6] - 1) << std::left << Employee->EmployeeInfo.infoWork.category << L"|"
		<< std::setw(form->minLenColumnSection[7] - 1) << std::left << Employee->EmployeeInfo.infoWork.idWorkshop << L"|"
		<< std::setw(form->minLenColumnSection[8] - 1) << std::left << Employee->EmployeeInfo.infoWork.idDepartment << L"|"
		<< std::setw(form->minLenColumnSection[9] - 1) << std::left << Employee->EmployeeInfo.salary;
	
};

void UpdateBoxContent(ListItem* Employee, const ModelOBJ* form, int& chois, List* listT, bool value, bool flag)
{
	uint16_t iter(0); ShowCursor(false);
	if (Employee)
	{
		if (value)
		{
			ListItem* tmp(nullptr);
			if(chois == form->heightContent) ReClearScreenContentBoxDraw(form);
			if ((chois == form->heightContent) && Employee->prev)
			{
				ListItem* tmp1 = Employee;
				chois = 0;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG | FB | FR | BG);
				SetCurPos(form->border + 1, form->coordXY.Y + (chois)-(form->heightContent + form->border));
				CoutList(Employee, form);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BBLACK | BG | BB | BR);
				while (tmp1->next && iter < form->heightContent - 1)
				{
					tmp1 = tmp1->next;
					SetCurPos(form->border + 1, form->coordXY.Y + (iter + 1)-(form->heightContent + form->border));
					CoutList(tmp1, form);
					++iter;		
				}
			}
			else if(chois >= 0)
			{

				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG | FB | FR | BG);
				SetCurPos(form->border + 1, form->coordXY.Y + (chois)-(form->heightContent + form->border));
				
				CoutList(Employee, form);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BBLACK | BG | BB | BR);
				if (Employee->prev && chois != 0) 
				{
					SetCurPos(form->border + 1, (form->coordXY.Y + (chois)-(form->heightContent + form->border)) - 1);
					CoutList(Employee->prev, form);
				}


				if (listT->flag) 
				{
					if (Employee->next && chois != form->heightContent - 1)
					{
						SetCurPos(form->border + 1, (form->coordXY.Y + (chois)-(form->heightContent + form->border)) + 1);
						tmp = Employee->next; int tnt = chois;
						while (tmp && tnt != form->heightContent - 1) {
							SetCurPos(form->border + 1, (++tnt) + form->border + form->headerHeight);
							CoutList(tmp, form);
							tmp = tmp->next;
						}
						while (tnt++ < form->heightContent - 1)
						{
							SetCurPos(form->border + 1, (tnt)+form->border + form->headerHeight);
							std::cout << std::string(form->weightContent - 2, ' ');
						}
						listT->flag = 0;
					}
						else if(chois < form->heightContent - 1)
						{
							SetCurPos(form->border + 1, (chois +1)+ form->border + form->headerHeight);
							
							std::cout << std::string(form->weightContent - 2, ' ');
						}
					
				}
				else
				{
					if (Employee->next && chois != form->heightContent - 1)
					{
						SetCurPos(form->border + 1, (form->coordXY.Y + (chois)-(form->heightContent + form->border)) + 1);
						CoutList(Employee->next, form);
					}
				}
			}
			else if (chois < 0)
			{

				while (Employee->prev)
					Employee = Employee->prev;
				ListItem* tmp1 = Employee;
				chois = 0;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG | FB | FR | BG);

				SetCurPos(form->border + 1, form->coordXY.Y + (chois)-(form->heightContent + form->border));
				CoutList(Employee, form);
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BBLACK | BG | BB | BR);
				while (tmp1->next && iter < form->heightContent - 1)
				{
					tmp1 = tmp1->next;
					SetCurPos(form->border + 1, form->coordXY.Y + (iter + 1) - (form->heightContent + form->border));
					CoutList(tmp1, form);
					++iter;
				}
				
			}	
		}
		

		else if (chois > form->heightContent)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BBLACK | BG | BB | BR);
			while (iter < form->heightContent && Employee)
			{
				SetCurPos(form->border + 1, form->coordXY.Y + (iter)-(form->heightContent + form->border));
				CoutList(Employee, form);
				++iter;

				Employee = Employee->next;
			}
			if (iter != (form->heightContent - 1))
			{
				for (iter; iter < form->heightContent; ++iter)
				{
					SetCurPos(form->border + 1, form->coordXY.Y + (iter)-(form->heightContent + form->border));
					std::wcout << std::wstring((form->weightContent - 2), ' ');
				}
			}
		}
		else
		{
			while (Employee->prev)
				Employee = Employee->prev;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BBLACK | BG | BB | BR);
			while (iter < form->heightContent && Employee)
			{
				SetCurPos(form->border + 1, form->coordXY.Y + (iter)-(form->heightContent + form->border));
				CoutList(Employee, form);
				++iter;

				Employee = Employee->next;
			}
			if (iter != (form->heightContent - 1))
			{
				for (iter; iter < form->heightContent; ++iter)
				{
					SetCurPos(form->border + 1, form->coordXY.Y + (iter)-(form->heightContent + form->border));
					std::wcout << std::wstring((form->weightContent - 2),' ');
				}
			}
			
		}
		
	}
	else { 
		ReClearScreenContentBoxDraw(form); 
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), form->consoleATR);
};

bool choisListContent(const ModelOBJ* form, List* listT)
{
	if (listT->begin)
	{
		int chois(0); ListItem* tmp = listT->begin; bool flag(0);
		while (true)
		{
			UpdateBoxContent(tmp, form, chois, listT, 1, listT->flag);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), form->consoleATR);
			while (int key = _getch())
			{
				if (key > 99) continue;
				if (GetAsyncKeyState(VK_UP) != 0)
				{
					--chois;
					if (chois < 0)
						tmp = listT->begin;
					else if (tmp->prev)
						tmp = tmp->prev;
					break;
				}
				else if (GetAsyncKeyState(VK_DOWN) != 0)
				{
					if (chois == 0 && !tmp->next) tmp = listT->begin;
					if (tmp && tmp->next)
					{
						tmp = tmp->next;
						if (tmp)
							++chois;
					}
					
					if (chois >= form->heightContent)
						chois = form->heightContent;
					break;
				}
				else if (GetAsyncKeyState(VK_RIGHT) != 0)
				{

					UpdateBoxContent(tmp, form, chois, 0);
					return 1;
				}

				else if (GetAsyncKeyState(VK_RETURN) != 0)
				{
					if (ChoisEmployee(tmp, form, listT, flag))
					{
						if (flag)
						{
							--chois;
						}
						
						break;
					}
					
				}
			}
		}
	}
};

