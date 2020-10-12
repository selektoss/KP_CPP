#include "__AddEmployee__.hpp"
#include "__CurPosition__.hpp"
#include "try_error_cin.hpp" 
#include "color.hpp"
#include <regex>
#include "UpdateContentBox.hpp"
#include "Func.hpp"

bool RegxCheck(wchar_t* line, const wchar_t* regular, const uint16_t& tmpX, uint16_t& tmpY, const uint16_t& weightContent)
{
	bool check(0); using namespace std;
	check = regex_match(line, basic_regex<wchar_t>{ regular });

	if (check)
	{
		std::wcout << line;
		while (int key1 = _getch())
		{
			if (key1 > 90) continue;
			if ((GetAsyncKeyState(VK_BACK)) != 0)
			{
				jumpPosCurInfoAdd(tmpX, tmpY, weightContent);
				wcin.getline(line, 31); if (wcin.tellg() < 0) return 0;
				return  regex_match(line, basic_regex<wchar_t>{ regular });
			}
			else return 1;
		}
	}
	else
	{
		wcin.getline(line, 31); 
		if (wcin.tellg() < 0) return 0;
		return  regex_match(line, basic_regex<wchar_t>{ regular });
	}
};

void fixErrorDrawing(const uint16_t& weightContent, const uint16_t& x, const uint16_t& y)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FR | BG | BB | BR);
	SetCurPos(x, y); std::cout << std::string((weightContent + 5) - (x), ' ');
	SetCurPos(x, y); std::wcout << L"*Œÿ»¡ ¿ ‘Œ–Ã¿“¿ ¬¬Œƒ¿ ƒ¿ÕÕ€’"; Sleep(2500);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BBLACK | BG | BB | BR);
	SetCurPos(x, y); std::cout << std::string((weightContent + 5) - (x), ' ');
	SetCurPos(x, y);
};

void jumpPosCurInfoAdd(const uint16_t& x, const uint16_t& y, const uint16_t& weightContent)
{
	
	fixErrorDrawing(weightContent, x, y);
	if (std::wcin.tellg() < 0)
	{
		std::wcin.clear();
		std::wcin.ignore(INT_MAX, '\n');
	}
	
};

bool CheckCinEmployee(wchar_t* line, const uint16_t& key, uint16_t tmpX, uint16_t tmpY, const uint16_t& weightContent)
{
	int key1(0); bool check(0);
	ShowCursor(true); SetConsoleCP(1251); SetConsoleOutputCP(1251);
	using namespace std;
	if (!key)
	{
		const wchar_t* regularSNM = L"([¿-ﬂ]){1}[‡-ˇ]+\\s([¿-ﬂ]){1}[‡-ˇ]+\\s([¿-ﬂ]){1}[‡-ˇ]+";
		return RegxCheck(line, regularSNM, tmpX, tmpY, weightContent);
		
	}
	else if(key < 2)
	{
		const wchar_t* regularSpecial = L"([¿-ﬂ]){1}[‡-ˇ]+";
		return RegxCheck(line, regularSpecial, tmpX, tmpY, weightContent);
		
	}
	else 
	{
		const wchar_t* regularDOB = L"^((3[01]|2\\d|1\\d|0[1-9])[.](1[012]|0[1-9])[.](19|20)[1-9][0-9])$";
		return RegxCheck(line, regularDOB, tmpX, tmpY, weightContent);
	}
};

bool CheckCinEmployee(int& gender, const uint16_t& x, const uint16_t& y, const uint16_t& weightContent)
{
	if (gender >= 0)
	{
		gender == 1 ? std::wcout << L"∆ÂÌÒÍËÈ" : std::wcout << L"ÃÛÊÒÍÓÈ";
		while (int key1 = _getch())
		{
			if (key1 > 99) continue;
			if ((GetAsyncKeyState(VK_BACK)) != 0)
			{
				fixErrorDrawing(weightContent, x, y);
				while (!(std::cin >> gender) && (gender > 1 || gender < 0))
				{
					fixErrorDrawing(weightContent, x, y);
					std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				}
			}
			return true;
		}
	}
	else
	{
		while (!(std::cin >> gender) && (gender > 1 || gender < 0))
		{
			fixErrorDrawing(weightContent, x, y);
			std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
		}
		return true;
	}	
	
};

bool CheckCinEmployee(Employee::WorkPlaceData::exper& exper, const uint16_t& weightContent, const uint16_t& x, const uint16_t& y)
{
	using namespace std;
	if (exper.experYear > 0)
	{
		std::cout << exper.experYear;
		while (int key1 = _getch())
		{
			if (key1 > 99) continue;
			if ((GetAsyncKeyState(VK_BACK)) != 0)
			{
				fixErrorDrawing(weightContent, x, y);
				
				
				while (!(std::cin >> exper.experYear) || exper.experYear > 60)
				{
					fixErrorDrawing(weightContent, x, y);
					std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
				}
			}
			return true;
		}
	}
	else
	{
		
		while (!(std::cin >> exper.experYear) || exper.experYear > 60)
		{
				fixErrorDrawing(weightContent, x, y);
				std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
		}
		return true;
	}
};


bool CheckCinEmployee(uint16_t& infoWork, const uint16_t& weightContent, const uint16_t& x, const uint16_t& y, const uint16_t& iter)
{
	if (iter == 5)
	{
		if (infoWork > 0)
		{
			std::cout << infoWork;
			while (int key1 = _getch())
			{
				if (key1 > 99) continue;
				if ((GetAsyncKeyState(VK_BACK)) != 0)
				{
					fixErrorDrawing(weightContent, x, y);
					while (!(std::cin >> infoWork) || infoWork > 3)
					{
						fixErrorDrawing(weightContent, x, y);
						std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
					}
				}
				return true;
			}
			
		}
		else
		{
			while (!(std::cin >> infoWork) || infoWork > 3)
			{
				fixErrorDrawing(weightContent, x, y);
				std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			}
			return true;
		}
	}

	else
	{
		if (infoWork > 0)
		{
			std::cout << infoWork;
			while (int key1 = _getch())
			{
				if (key1 > 99) continue;
				if ((GetAsyncKeyState(VK_BACK)) != 0)
				{
					fixErrorDrawing(weightContent, x, y);
					while (!(std::cin >> infoWork) || infoWork > 1000)
					{
						fixErrorDrawing(weightContent, x, y);
						std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
					}
				}
				return true;
			}
		}

		else
		{
			while (!(std::cin >> infoWork) || infoWork > 1000)
			{
				fixErrorDrawing(weightContent, x, y);
				std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			}
			return true;
		}
	}
};

void AddInfoProfile(ListItem*& pointTemp, const ModelOBJ* form, List* tmpb)
{
	
	ReClearScreenContentBoxDraw(form);
	const uint16_t lentitleArr(9), columntitleArr(39);
	
	
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), BBLACK | BG | BB | BR); 
	uint16_t iter(0), Yposition(0); static uint16_t idemployee(0);
	if (pointTemp->prev && tmpb)
	{
		ListItem* tmp = tmpb->begin;
		while (tmp)
		{
			if (idemployee < tmp->EmployeeInfo.idPerson)
				idemployee = tmp->EmployeeInfo.idPerson;
			tmp = tmp->next;
		}
		++idemployee;
	}
	uint16_t tmpX(form->border + ((form->weightContent >> 1) - ((columntitleArr + *(form->minLenColumnSection + 1)) >> 1)));
	uint16_t tmpY((((form->border << 1) + (form->heightContent >> 1)) - lentitleArr) + Yposition);
	while (iter < lentitleArr)
	{
		SetCurPos(tmpX, (tmpY + Yposition)); Yposition += 2;
		std::wcout << *((form->infoAddDelete + 6) + (iter++)) << std::endl;
	}
	iter = 0; Yposition = 0;
	if(pointTemp->EmployeeInfo.idPerson == 0)
		pointTemp->EmployeeInfo.idPerson = idemployee++;
	while (iter < lentitleArr)
	{
		uint16_t tmpLen(static_cast<uint16_t>(wcslen(*((form->infoAddDelete + 6) + iter)))); SetCurPos(tmpX + tmpLen, (tmpY + Yposition));
		switch (iter)
		{
		case 0: 
			
			if (CheckCinEmployee(pointTemp->EmployeeInfo.SNM, iter, tmpX + tmpLen, tmpY + Yposition, form->weightContent))
			{
				++iter; Yposition += 2; break;
			}
			else 
				jumpPosCurInfoAdd(tmpX + tmpLen, tmpY + Yposition, form->weightContent); break;

		case 1:

			if (CheckCinEmployee(pointTemp->EmployeeInfo.specialty, iter, tmpX + tmpLen, tmpY + Yposition, form->weightContent))
			{
				++iter; Yposition += 2; break;
			}
			else
				jumpPosCurInfoAdd(tmpX + tmpLen, tmpY + Yposition, form->weightContent); break;

		case 2:

			if (CheckCinEmployee(pointTemp->EmployeeInfo.DOB, iter, tmpX + tmpLen, tmpY + Yposition, form->weightContent))
			{
				++iter; Yposition += 2; break;
			}
			else
				jumpPosCurInfoAdd(tmpX + tmpLen, tmpY + Yposition, form->weightContent); break;

		case 3:

			if (CheckCinEmployee(pointTemp->EmployeeInfo.gender, tmpX + tmpLen, tmpY + Yposition, form->weightContent))
			{
				++iter; Yposition += 2; break;
			}
			break;

		case 4:

			if (CheckCinEmployee(pointTemp->EmployeeInfo.infoWork.expervalue, form->weightContent, tmpX + tmpLen, tmpY + Yposition))
			{
				++iter; Yposition += 2; break;
			}
			break;

		case 5:

			if (CheckCinEmployee(pointTemp->EmployeeInfo.infoWork.category, form->weightContent, tmpX + tmpLen, tmpY + Yposition, iter))
			{
				++iter; Yposition += 2; break;
			}
			break;

		case 6:

			if (CheckCinEmployee(pointTemp->EmployeeInfo.infoWork.idWorkshop, form->weightContent, tmpX + tmpLen, tmpY + Yposition, iter))
			{
				++iter; Yposition += 2; break;
			}
			break;

		case 7:

			if (CheckCinEmployee(pointTemp->EmployeeInfo.infoWork.idDepartment, form->weightContent, tmpX + tmpLen, tmpY + Yposition, iter))
			{
				++iter; Yposition += 2; break;
			}
			break;

		case 8:

			while (!(std::cin >> pointTemp->EmployeeInfo.salary) || pointTemp->EmployeeInfo.salary > 900000)
			{
				fixErrorDrawing(form->weightContent, tmpX + tmpLen, tmpY + Yposition);
				std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
			}
			++iter; Yposition += 2; break;
		}
	}
};

void InsertListData(List*& listEmployee, const ModelOBJ* form)
{
	ListItem* pointTemp(nullptr); int ChoiceYesOrNo(NULL); const uint16_t size(2);
	uint16_t x = form->border; uint16_t y = (form->coordXY.Y - (form->border >> 1));
	const char choisV[size][11] = { " ƒŒ¡¿¬»“‹ ", " Œ“Ã≈Õ¿ " };
	int chois(0); bool result(true);
	uint16_t tmp = static_cast<uint16_t>((wcslen(form->infoAddDelete[0]))) + form->border;
		while (result)
		{
			pointTemp = new ListItem;

			if (!listEmployee->begin)
			{
				listEmployee->begin = pointTemp;
				listEmployee->end = pointTemp;
			}
			else
			{
				listEmployee->end->next = pointTemp;
				pointTemp->prev = listEmployee->end;
				listEmployee->end = pointTemp;
			}
			AddInfoProfile(*&pointTemp, form, listEmployee);
			
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
			x = form->border;
			SetCurPos(x, y);
			std::wcout << form->infoAddDelete[0];  x += tmp;
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
						std::cin.clear(); std::cin.ignore(INT_MAX, '\n');
						break; 
					}
					else if (chois == 1)
					{
						chois = form->coordXY.X; x = form->border;
						DrawButtonEmployeeChoise(chois, x, y, choisV, size);
						result = false;
						break;
					}
				}
			}
		}
	int t = 0; ShowCursor(false);
	ShowInfoParamEmployee(listEmployee->begin, form);
	UpdateBoxContent(listEmployee->begin, form, t, 0);
};