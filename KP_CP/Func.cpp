#include "Func.hpp"
#include <fstream>
#include <iostream>
#include <codecvt>
#include "__LoadObjectForm__.hpp"
#include "__SaveReadLocalFileData__.hpp"
#include <regex>

void ExchangeList(ListItem* Left, ListItem* Right, List* last)
{
	if (Right == last->end)
		last->end = Left;

	if (!Left->prev) {

		last->begin = Right; Right->prev = 0; Left->prev = Right; Left->next = Right->next;

		if (Right->next)
			Right->next->prev = Left;

		Right->next = Left;
	}
	else {
		Right->prev = Left->prev; Left->prev->next = Right;

		if (Right->next)
			Right->next->prev = Left;

		Left->next = Right->next; Right->next = Left; Left->prev = Right;
	}
};


bool SelectParamSort(const int& chois, ListItem*& EmployeeItem, List* lisT,
	const uint32_t& valueEqual, const uint32_t& valueEqualNext, const uint16_t& countColumnTable, int& countEmployee)
{
	static uint16_t FlagsSort[10] = { 0 };
	if (!*(FlagsSort + chois))
	{
		while (countEmployee >= 0)
		{

			while (EmployeeItem && EmployeeItem->next)
			{
				if (valueEqual > valueEqualNext)
					ExchangeList(EmployeeItem, EmployeeItem->next, lisT);
				else EmployeeItem = EmployeeItem->next;
				if (!EmployeeItem->next) { EmployeeItem = lisT->begin; --countEmployee; }
				return 1;
			}
			--countEmployee; return 1;
		}
		for (uint16_t iter(0); iter < countColumnTable; ++iter)
			*(FlagsSort + iter) = 0;

		*(FlagsSort + chois) = 1;
		return 0;
	}
	else
	{
		Reverse(lisT);
		return 0;
	}
};

void SortParamList(List* lisT, const int& chois, const uint16_t countColumnTable)
{
	if (lisT->begin && lisT->begin->next)
	{
		ListItem* EmployeeItem = lisT->begin; int countEmployee(lisT->countItemList);

		switch (chois)
		{
		case 0:
		{
			while (SelectParamSort(chois, EmployeeItem, lisT, EmployeeItem->EmployeeInfo.idPerson,
				EmployeeItem->next->EmployeeInfo.idPerson, countColumnTable, countEmployee));
		} break;

		case 1:
		{
			while (SelectParamSort(chois, EmployeeItem, lisT, *(EmployeeItem->EmployeeInfo.SNM) - NULL,
				*(EmployeeItem->next->EmployeeInfo.SNM) - NULL, countColumnTable, countEmployee));
		} break;

		case 2:
		{
			while (SelectParamSort(chois, EmployeeItem, lisT, *(EmployeeItem->EmployeeInfo.specialty) - NULL,
				*(EmployeeItem->next->EmployeeInfo.specialty) - NULL, countColumnTable, countEmployee));
		} break;

		case 3:
		{
			while (SelectParamSort(chois, EmployeeItem, lisT, _wtoi(&EmployeeItem->EmployeeInfo.DOB[6]),
				_wtoi(&EmployeeItem->next->EmployeeInfo.DOB[6]), countColumnTable, countEmployee));
		} break;

		case 4:
		{
			while (SelectParamSort(chois, EmployeeItem, lisT, EmployeeItem->EmployeeInfo.gender,
				EmployeeItem->next->EmployeeInfo.gender, countColumnTable, countEmployee));
		} break;

		case 5:
		{
			while (SelectParamSort(chois, EmployeeItem, lisT, EmployeeItem->EmployeeInfo.infoWork.expervalue.experYear,
				EmployeeItem->next->EmployeeInfo.infoWork.expervalue.experYear, countColumnTable, countEmployee));
		} break;

		case 6:
		{
			while (SelectParamSort(chois, EmployeeItem, lisT, EmployeeItem->EmployeeInfo.infoWork.category,
				EmployeeItem->next->EmployeeInfo.infoWork.category, countColumnTable, countEmployee));
		} break;

		case 7:
		{
			while (SelectParamSort(chois, EmployeeItem, lisT, EmployeeItem->EmployeeInfo.infoWork.idWorkshop,
				EmployeeItem->next->EmployeeInfo.infoWork.idWorkshop, countColumnTable, countEmployee));
		} break;

		case 8:
		{
			while (SelectParamSort(chois, EmployeeItem, lisT, EmployeeItem->EmployeeInfo.infoWork.idDepartment,
				EmployeeItem->next->EmployeeInfo.infoWork.idDepartment, countColumnTable, countEmployee));
		} break;

		case 9:
		{
			while (SelectParamSort(chois, EmployeeItem, lisT, EmployeeItem->EmployeeInfo.salary,
				EmployeeItem->next->EmployeeInfo.salary, countColumnTable, countEmployee));

		} break;
		}
	}
};

void SelectChoiseColumn(const int& chois, ModelOBJ* Form)
{
	uint16_t Summ(0);
	for (uint16_t iter(0); iter < Form->countColumnTitle; ++iter)
	{
		Summ += *(Form->minLenColumnSection + iter);

		if (iter == chois)
		{
			SetCurPos(static_cast<uint16_t>((((Form->border + Form->weightContent + 1) - (Form->weightContent - Summ)) -
				(Form->minLenColumnSection[iter] >> 1)) - ((wcslen(*(Form->nameSection + iter)) + 2) >> 1)), (Form->headerHeight + 3));
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG | FB | FR | BG);
			std::wcout << Form->nameSection[iter];
		}
		else
		{
			SetCurPos(static_cast<uint16_t>((((Form->border + Form->weightContent + 1) - (Form->weightContent - Summ)) -
				(Form->minLenColumnSection[iter] >> 1)) - ((wcslen(*(Form->nameSection + iter)) + 2) >> 1)), (Form->headerHeight + 3));
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG);
			std::wcout << Form->nameSection[iter];
		}
	}
};

void ChoisSortTable(ModelOBJ* Form, List* listEmployee)
{
	int chois(0); bool check(true);
	while (check)
	{
		SelectChoiseColumn(chois, Form);
		while (int key = _getch())
		{
			if (key > 99) continue;

			if (GetAsyncKeyState(VK_LEFT) != 0)
			{
				--chois; if (chois < 0) chois = Form->countColumnTitle - 1;
				SelectChoiseColumn(chois, Form);

				break;
			}
			else if (GetAsyncKeyState(VK_RIGHT) != 0)
			{
				++chois; if (chois == Form->countColumnTitle) chois = 0;
				SelectChoiseColumn(chois, Form);
				break;
			}
			else if (GetAsyncKeyState(VK_DOWN) != 0)
			{

				if (choisListContent(Form, listEmployee))
					break;
			}
			else if (GetAsyncKeyState(VK_TAB) != 0)
			{
				chois = -1; SelectChoiseColumn(chois, Form);
				check = false;
				break;
			}

			else if (GetAsyncKeyState(VK_RETURN) != 0)
			{
				if (chois < Form->countColumnTitle && chois >= 0)
				{
					SortParamList(listEmployee, chois, Form->countColumnTitle);
					UpdateBoxContent(listEmployee->begin, Form, chois, listEmployee);
					break;
				}
			}
		}
	}
	SetCurPos(Form->border, (Form->headerHeight - 2) + Form->border);

};

void CaseMenu(ModelOBJ* Form, List*& listEmployee, int& chois, char*& keyData)
{
	while ((chois = ChoisMenu(Form, listEmployee)) < (7))
	{
		switch (chois)
		{
		case 0:
		{
			InsertListData(listEmployee, Form);
		} break;
		case 1:
		{
			ShowInfoParamEmployee(listEmployee->begin, Form, false);
		} break;
		case 2:
		{
			ChoisSortTable(Form, listEmployee);
		} break;
		case 3:
		{
			SearchEmployee(listEmployee->begin, Form, listEmployee);
			UpdateBoxContent(listEmployee->begin, Form, chois, listEmployee);

		} break;
		case 4:
		{
			SaveDataListLocalDB(listEmployee, keyData);

		} break;
		case 5:
		{
			DeleteEmployee(listEmployee, chois);
			UpdateBoxContent(listEmployee->begin, Form, chois, listEmployee);
			ShowInfoParamEmployee(listEmployee->begin, Form);
		} break;
		case 6:
		{
			PrintToTXT(listEmployee, Form);
		} break;
		case 7:
		{
			if (listEmployee)
			{
				SaveDataListLocalDB(listEmployee, keyData);
				DeleteEmployee(listEmployee, chois);
				delete listEmployee;
			}
		} break;
		}
	}
};

void ShowInfoFooter(const ModelOBJ* form, const wchar_t* info, bool value)
{
	SetCurPos(form->border, form->coordXY.Y - (form->border >> 1)); std::cout << std::string(form->weightContent, ' ');
	SetCurPos((form->border + (form->weightContent >> 1)) - static_cast<uint16_t>((wcslen(info) >> 1)), static_cast<uint16_t>(form->coordXY.Y - (form->border >> 1)));

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), form->consoleATR); std::wcout << info;
	if (value)
	{
		Sleep(3500); SetCurPos(form->border, form->coordXY.Y - (form->border >> 1)); std::cout << std::string(form->weightContent, ' ');
	}

};

void ShowResult(const uint16_t* Arr, const ModelOBJ* form, bool value)
{
	using namespace std;

	const wchar_t Ainfo[6][11] = { L"|ДО 6", L"|6 - 11", L"|11 - 16", L"|16 - 21", L"|21 - 25", L"|СВЫШЕ 25" };
	if (value)
	{
		uint16_t count(0), iterar(0), iterDelim(2), Xstep(0);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		SetCurPos(form->coordXY.X - (form->border + form->MenuWeight), form->headerHeight + 2);
		for (size_t i = 0; i < form->MenuWeight; i++) wcout << '-';
		wcout << endl;
		SetCurPos(form->coordXY.X - (form->border + form->MenuWeight), form->headerHeight + 3);
		wcout << setw(9) << left << L"|СТАЖ/ЛЕТ" << setw(12) << left << L"|РАЗРЯД" << setw(form->MenuWeight - 22) << left << L"|ОБЩЕЕ" << "|";
		SetCurPos((form->coordXY.X - ((form->MenuWeight)) + 4), form->headerHeight + 4);
		wcout << "|";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BBLACK | BG | BB | BR);
		wcout << setw(3) << left << L" 1 " << setw(3) << left << L"| 2 " << "|" << setw(3) << left << L" 3";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		wcout << "|";
		SetCurPos(form->coordXY.X - (form->border + form->MenuWeight), form->headerHeight + 5);
		for (size_t i = 0; i < form->MenuWeight; i++) wcout << '-';

		for (iterar; iterar < 6; ++iterar, ++count, ++Xstep)
		{
			SetCurPos(form->coordXY.X - (form->border + form->MenuWeight), form->headerHeight + 6 + Xstep);
			wcout << setw(9) << Ainfo[iterar];
			wcout << "|" << setw(3) << Arr[count] << "|" << setw(3) << Arr[count + 1] << "|" << setw(3) << Arr[count + 2] << "|";

			wcout << setw(form->MenuWeight - 23) << Arr[count] + Arr[count + 1] + Arr[count + 2] << "|";
			count += 2;
		}
		SetCurPos(form->coordXY.X - (form->border + form->MenuWeight), form->headerHeight + 12);
		for (size_t i = 0; i < form->MenuWeight; i++) wcout << '-';
	}
	else
	{
		const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
		std::wofstream fileData("REPORTCOUNT.txt");
		fileData.imbue(utf8_locale);
		if (fileData.is_open())
		{
			for (size_t i = 0; i < form->MenuWeight; i++) fileData << '-'; fileData << "\n"
				<< setw(10) << left << L"|СТАЖ/ЛЕТ" << setw(12) << left << L"|РАЗРЯД" << "|" << left << L"ОБЩЕЕ" << "|\n"
				<< setw(3) << left << L"          | 1 " << setw(3) << left << L"| 2 " << "|" << setw(3) << left << L" 3" << "|" << setw(5) << left << L"ВСЕГО" << "|\n";
			for (size_t i = 0; i < form->MenuWeight; i++) fileData << '-';
			fileData << "\n"; uint16_t count(0);
			for (uint16_t iter(0); iter < 6; ++iter, ++count)
			{
				fileData << setw(10) << Ainfo[iter]
					<< "|" << setw(3) << Arr[count] << "|" << setw(3) << Arr[count + 1] << "|" << setw(3) << Arr[count + 2] << "|"
					<< setw(5) << Arr[count] + Arr[count + 1] + Arr[count + 2] << "|\n";
				count += 2;
			}
			fileData.close();
			ShowInfoFooter(form, form->infoAddDelete[5]);
		}
	}
};

void ShowInfoParamEmployee(ListItem* begEmployee, const ModelOBJ* form, bool value)
{
	uint16_t Arr[18] = { 0 };
	if (begEmployee)
	{
		ListItem* tmpEmployee = begEmployee;

		while (tmpEmployee)
		{
			while (true)
			{
				if (tmpEmployee->EmployeeInfo.infoWork.expervalue.experYear < 6)
				{

					if (tmpEmployee->EmployeeInfo.infoWork.category == 1)
						++Arr[0];
					if (tmpEmployee->EmployeeInfo.infoWork.category == 2)
						++Arr[1];
					if (tmpEmployee->EmployeeInfo.infoWork.category == 3)
						++Arr[2];
					break;
				}
				if (tmpEmployee->EmployeeInfo.infoWork.expervalue.experYear >= 6 &&
					tmpEmployee->EmployeeInfo.infoWork.expervalue.experYear < 11)
				{

					if (tmpEmployee->EmployeeInfo.infoWork.category == 1)
						++Arr[3];
					if (tmpEmployee->EmployeeInfo.infoWork.category == 2)
						++Arr[4];
					if (tmpEmployee->EmployeeInfo.infoWork.category == 3)
						++Arr[5];
					break;
				}
				if (tmpEmployee->EmployeeInfo.infoWork.expervalue.experYear >= 11 &&
					tmpEmployee->EmployeeInfo.infoWork.expervalue.experYear < 16)
				{
					if (tmpEmployee->EmployeeInfo.infoWork.category == 1)
						++Arr[6];
					if (tmpEmployee->EmployeeInfo.infoWork.category == 2)
						++Arr[7];
					if (tmpEmployee->EmployeeInfo.infoWork.category == 3)
						++Arr[8];
					break;
				}
				if (tmpEmployee->EmployeeInfo.infoWork.expervalue.experYear >= 16 &&
					tmpEmployee->EmployeeInfo.infoWork.expervalue.experYear < 21)
				{
					if (tmpEmployee->EmployeeInfo.infoWork.category == 1)
						++Arr[9];
					if (tmpEmployee->EmployeeInfo.infoWork.category == 2)
						++Arr[10];
					if (tmpEmployee->EmployeeInfo.infoWork.category == 3)
						++Arr[11];
					break;
				}
				if (tmpEmployee->EmployeeInfo.infoWork.expervalue.experYear >= 21 &&
					tmpEmployee->EmployeeInfo.infoWork.expervalue.experYear < 25)
				{
					if (tmpEmployee->EmployeeInfo.infoWork.category == 1)
						++Arr[12];
					if (tmpEmployee->EmployeeInfo.infoWork.category == 2)
						++Arr[13];
					if (tmpEmployee->EmployeeInfo.infoWork.category == 3)
						++Arr[14];
					break;
				}
				if (tmpEmployee->EmployeeInfo.infoWork.expervalue.experYear > 25)
				{

					if (tmpEmployee->EmployeeInfo.infoWork.category == 1)
						++Arr[15];
					if (tmpEmployee->EmployeeInfo.infoWork.category == 2)
						++Arr[16];
					if (tmpEmployee->EmployeeInfo.infoWork.category == 3)
						++Arr[17];

					break;
				}

			}
			tmpEmployee = tmpEmployee->next;
		}

	}
	ShowResult(Arr, form, value);
};

void DeleteEmploye(ListItem*& employee, List* list, const ModelOBJ* form, bool& flag)
{

	if (employee)
	{
		const wchar_t* info = L"БУДЕТ ПРОИЗВЕДЕНО УДАЛЕНИЕ ВЫБРАННОГО СОТРУДНИКА! ВЫ УВЕРЕНЫ? "; const uint16_t size(2);
		bool result(true); uint16_t x(5), y(form->coordXY.Y - 2); int chois(0); char choisV[size][11] = { " УВЕРЕН! ", " ОТМЕНА " };
		while (result)
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); x = 5;
			chois = 100;
			DrawButtonEmployeeChoise(chois, x, y, choisV, size); SetCurPos(x, y);
			std::wcout << info;  x += static_cast<uint16_t>(wcslen(info));
			DrawButtonEmployeeChoise(chois, x, y, choisV, size);

			while (int key = _getch())
			{
				if (key > 99) continue;

				if (GetAsyncKeyState(VK_LEFT) != 0)
				{
					--chois; if (chois < 0) chois = 1;
					DrawButtonEmployeeChoise(chois, x, y, choisV, size);

				}
				else if (GetAsyncKeyState(VK_RIGHT) != 0)
				{
					++chois; if (chois == 2) chois = 0;
					DrawButtonEmployeeChoise(chois, x, y, choisV, size);

				}
				else if (GetAsyncKeyState(VK_RETURN) != 0)
				{

					if (chois == 0)
					{
						ListItem* tmp = employee;
						if (tmp->prev)
						{
							if (tmp->next)
							{
								tmp->prev->next = tmp->next;
								tmp->next->prev = tmp->prev;
								employee = tmp->next;
							}
							else
							{
								tmp->prev->next = nullptr;
								list->end = tmp->prev;
								employee = tmp->prev;
								flag = 1;
							}
							delete tmp;
						}

						else if (tmp->next)
						{
							list->begin = employee->next;
							employee = employee->next;
							employee->prev = nullptr;
							delete tmp;
						}
						x = 5; chois = 100;
						DrawButtonEmployeeChoise(chois, x, y, choisV, size);
						result = false; --list->countItemList;
						break;
					}
					else if (chois == 1)
					{
						x = 5; chois = 100;
						DrawButtonEmployeeChoise(chois, x, y, choisV, size);
						result = false;
						break;
					}
				}
			}
		}
	}

};

void EditEmploye(ListItem*& employee, const ModelOBJ* form)
{

	AddInfoProfile(employee, form);
	std::cin.ignore();
};

void Reverse(List* list)
{

	if (list)
	{
		ListItem* newHead = list->end, * t;
		for (ListItem* item = list->begin; item; item = item->prev) {
			t = item->prev;
			item->prev = item->next;
			item->next = t;
		}
		list->end = list->begin;
		list->begin = newHead;

	}

};


ListItem* SearchEmployee(ListItem* list, const ModelOBJ* form, List* tmplist)
{
	if (list)
	{
		SetConsoleCP(1251); SetConsoleOutputCP(1251); bool flag(0);
		uint16_t iter(0); ListItem* tempEmployee = list; wchar_t tmpLine[21]{ 0 };
		ShowInfoFooter(form, form->infoAddDelete[2], 0); int chois(0);
		std::wcin.getline(tmpLine, 20); uint16_t find_(0); ListItem* tempEmployee1(nullptr);
		if (regex_match(tmpLine, std::basic_regex<wchar_t>{ L"^[0-9]{1,5}$" }))
		{
			size_t number(_wtoi(tmpLine));
			while (tempEmployee)
			{
				if (number > tmplist->end->EmployeeInfo.idPerson) break; ++find_;
				if (tempEmployee->EmployeeInfo.idPerson == number)
				{
					if (find_ > form->heightContent)
					{
						uint16_t fixpoz = (find_ / form->heightContent);
						chois = find_; ListItem* tempEmployee2(nullptr);
						tempEmployee2 = tempEmployee;
						for (uint16_t i = 0; i < (find_ - (form->heightContent * fixpoz)); ++i)
						{
							tempEmployee1 = tempEmployee2;
							tempEmployee2 = tempEmployee2->prev;
						}
						UpdateBoxContent(tempEmployee1, form, chois, tmplist);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG | FB | FR | BG);
						SetCurPos(form->border + 1, (form->coordXY.Y - (form->heightContent + form->border)) + ((find_ - (form->heightContent * fixpoz)) - 1));
						CoutList(tempEmployee, form);
					}
					else
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG | FB | FR | BG);
						SetCurPos(form->border + 1, ((form->coordXY.Y - (form->heightContent + form->border)) + find_) - 1);
						CoutList(tempEmployee, form);

					}
					ChoisEmployee(tempEmployee, form, tmplist, flag);
					tempEmployee = list;
					chois = -1;
					return tempEmployee;
				}
				tempEmployee = tempEmployee->next;
			}
			ShowInfoFooter(form, form->infoAddDelete[1], true);
			return list;
		}
		else if ((regex_match(tmpLine, std::basic_regex<wchar_t>{ L"([А-Я]){1}[а-я]{1,19}$" })))
		{
			uint16_t number(0), number2(0); List* tmpBgin(nullptr);
			uint16_t count, counttmp = static_cast<uint16_t>(wcslen(tmpLine)); count = counttmp;
			while (tempEmployee)
			{
				++find_;
				count = static_cast<uint16_t>(wcslen(tmpLine));
				while (tmpLine[iter] != 0 && tempEmployee->EmployeeInfo.SNM[iter] != ' ' && count)
				{
					if ((tmpLine[iter] - 0) == (tempEmployee->EmployeeInfo.SNM[iter] - 0))
						++iter;
					--count;
				}

				if (iter == counttmp)
				{

					if (find_ > form->heightContent)
					{
						uint16_t fixpoz = (find_ / form->heightContent);
						chois = find_; ListItem* tempEmployee2(nullptr);
						tempEmployee2 = tempEmployee;
						for (uint16_t i = 0; i < (find_ - (form->heightContent * fixpoz)); ++i)
						{
							tempEmployee1 = tempEmployee2;
							tempEmployee2 = tempEmployee2->prev;
						}
						UpdateBoxContent(tempEmployee1, form, chois, tmplist);
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG | FB | FR | BG);
						SetCurPos(form->border + 1, (form->coordXY.Y - (form->heightContent + form->border)) + ((find_ - (form->heightContent * fixpoz)) - 1));
						CoutList(tempEmployee, form);
					}
					else
					{
						SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FG | FB | FR | BG);
						SetCurPos(form->border + 1, ((form->coordXY.Y - (form->heightContent + form->border)) + find_) - 1);
						CoutList(tempEmployee, form);

					}
					ChoisEmployee(tempEmployee, form, tmplist, flag);
					tempEmployee = list;
					chois = -1;
					return tempEmployee;
				}
				tempEmployee = tempEmployee->next;

			}
			ShowInfoFooter(form, form->infoAddDelete[1]);
			return list;
		}


		else
		{
			ShowInfoFooter(form, form->infoAddDelete[3]);
			std::wcin.clear();

		}
	}
};

void DeleteEmployee(List*& listEmployee, int& choisT)
{
	if (listEmployee->begin)
	{
		const wchar_t* info = L"ВНИМАНИЕ!!! УДАЛЕНИЕ ВСЕХ ДАННЫХ! ВЫ УВЕРЕНЫ? "; const uint16_t size(2);
		bool result(true); uint16_t x(5), y(37); int chois(0); char choisV[size][11] = { " УВЕРЕН! ", " ОТМЕНА " };
		while (result)
		{
			if (choisT != 7)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15); x = 5;
				chois = 100;
				DrawButtonEmployeeChoise(chois, x, y, choisV, size); SetCurPos(x, y);
				std::wcout << info;  x += static_cast<uint16_t>(wcslen(info));
				DrawButtonEmployeeChoise(chois, x, y, choisV, size);



				while (int key = _getch())
				{
					if (key > 99) continue;

					if (GetAsyncKeyState(VK_LEFT) != 0)
					{
						--chois; if (chois < 0) chois = 1;
						DrawButtonEmployeeChoise(chois, x, y, choisV, size);

					}
					else if (GetAsyncKeyState(VK_RIGHT) != 0)
					{
						++chois; if (chois == 2) chois = 0;
						DrawButtonEmployeeChoise(chois, x, y, choisV, size);

					}
					else if (GetAsyncKeyState(VK_RETURN) != 0)
					{

						if (chois == 0)
						{
							ListItem* temp = listEmployee->begin;
							while (temp)
							{
								listEmployee->begin = listEmployee->begin->next;
								delete temp;
								temp = listEmployee->begin;
							}
							listEmployee->begin = nullptr;
							listEmployee->end = nullptr;
							remove("localDB.dat");
							x = 5; chois = 100;
							DrawButtonEmployeeChoise(chois, x, y, choisV, size);
							result = false;
							break;
						}
						else if (chois == 1)
						{
							x = 5; chois = 100;
							DrawButtonEmployeeChoise(chois, x, y, choisV, size);
							result = false;
							break;
						}
					}
				}
			}
			else {
				ListItem* temp = listEmployee->begin;
				while (temp)
				{
					listEmployee->begin = listEmployee->begin->next;
					delete temp;
					temp = listEmployee->begin;
				}
				listEmployee->begin = nullptr;
				listEmployee->end = nullptr;
				break;
			}
		}
	}

};

void PrintToTXT(List* listEmployee, const ModelOBJ* form)
{
	if (listEmployee->begin)
	{

		const std::locale utf8_locale = std::locale(std::locale(), new std::codecvt_utf8<wchar_t>());
		std::wofstream fileData("REPORT.csv");
		fileData.imbue(utf8_locale);
		if (fileData.is_open())
		{
			ListItem* tmp = listEmployee->begin;
			fileData << L"Табельный номер,Инициалы,Специальность,Дата рождения,Пол,Стаж,Розряд,Цех,Участок,Зарплата\n";
			while (tmp)
			{
				fileData << tmp->EmployeeInfo.idPerson << "," << tmp->EmployeeInfo.SNM << ","
					<< tmp->EmployeeInfo.specialty << "," << tmp->EmployeeInfo.DOB;
				if (tmp->EmployeeInfo.gender) fileData << "," << L"Женский";
				else fileData << "," << L"Мужской";
				fileData << "," << tmp->EmployeeInfo.infoWork.expervalue.experYear << ","
					<< tmp->EmployeeInfo.infoWork.category << "," << tmp->EmployeeInfo.infoWork.idWorkshop << ","
					<< tmp->EmployeeInfo.infoWork.idDepartment << "," << tmp->EmployeeInfo.salary << std::endl;

				tmp = tmp->next;
			}
			ShowInfoFooter(form, form->infoAddDelete[4]);
			fileData.close();
		}

	}
}