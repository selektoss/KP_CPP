#include <regex>
#include <fstream>
#include <sstream>
#include <iostream>
#include "resource.h"
#include "__MainForm__.hpp"
#include "__CurPosition__.hpp"
#include <stdio.h>
#define F ios_base

char*& GetDataResourceMenu(ModelOBJ*& form, wchar_t*& title_contetnt, wchar_t**& nameSection)
{
	using namespace std;
	const wchar_t* regular[] = { L"#HEADER",L"^(#\\END_HEADER)", L"#MENU", L"^(#\\END_MENU)",
		L"#HELP", L"^(#\\END_HELP)", L"#TITLE", L"^(#\\END_TITLE)",
		L"#CONTENT", L"^(#\\END_CONTENT)", L"#INFO_ADD", L"^(#\\END_INFO)", L"#KEY_DATA",L"^(#\\END_KEY)", L"^(#\\END_CONF)"
	};
	wstring lineTemp; wstringstream lineBuffM(F::app | F::ate | F::in | F::out); std::wstringstream lineBuff;
	uint16_t check(NULL); uint16_t count(NULL); wcmatch res; form->Menu = nullptr; char* KeyData(nullptr);

	if (HRSRC FileResource = FindResource(GetModuleHandle(NULL), MAKEINTRESOURCE(INITXTFILE), L"ini"))
	{
		if (HGLOBAL ResourceMem = LoadResource(GetModuleHandle(NULL), FileResource))
			lineBuff << (wchar_t*)LockResource(ResourceMem);
		if (lineBuff.good())
			while (getline(lineBuff, lineTemp) && !(regex_match(lineTemp.c_str(), std::basic_regex<wchar_t>{ *(regular + 14) })))
			{
				if (regex_match(lineTemp.c_str(), res, 
					std::basic_regex<wchar_t>{ L"^(#\\HEADER|#\\MENU|#\\HELP|#\\TITLE|#\\CONTENT|#\\INFO_ADD|#\\KEY_DATA*)" },
					std::regex_constants::match_not_eol))
				{
					res[0] == regular[0] ? check = 1 : res[0] == regular[2] ? check = 3 : 
						res[0] == regular[4] ? check = 5 : res[0] == regular[8] ? check = 9 : res[0] == regular[10] ? check = 11 : 
						res[0] == regular[12] ? check = 13 : check = 7;
					while (getline(lineBuff, lineTemp) && !(regex_match(lineTemp.c_str(), 
						std::basic_regex<wchar_t>{ *(regular + check) })))
					{
						if (lineTemp == L"\r" || lineTemp == L"") continue;
						if (check == 1)
						{
							DrawBoxFormHeader(form->coordXY, lineTemp, form->border); break;
						}
						else if (check == 3 || check == 5 || check == 9 || check == 11)
						{
							lineBuffM << lineTemp + L'\n'; ++count;
						}
						else if (!title_contetnt && check == 7)
						{
							title_contetnt = new wchar_t[lineTemp.length() + 1];
							wcscpy(title_contetnt, lineTemp.c_str());
						}
						else if (check == 13)
						{
							size_t tmpLenghtKey(lineTemp.length()); KeyData = new char[tmpLenghtKey + 1];
							
							for (uint16_t i(0); i < tmpLenghtKey; ++i) *(KeyData + i) = lineTemp[i];
							*(KeyData + tmpLenghtKey) = '\0';
							
						}
					}
					(!(form->Menu) && count) ? form->Menu = new LoBject::button[count] : NULL;
					if (count && (check != 9 && check != 11))
					{
						form->sizeMenu = count;
						for (uint16_t iter(0); iter < count; ++iter)
							check == 3 ? getline(lineBuffM, ((form->Menu) + iter)->nameButton) : 
							getline(lineBuffM, ((form->Menu) + iter)->txtHelp);
						lineBuffM.str(std::wstring()); lineBuffM.clear();
					}
					
					else if (check == 9 || check == 11)
					{
						wchar_t** temp = new wchar_t* [count];
						check == 9 ? nameSection = temp  : form->infoAddDelete = temp;
						
						(*temp) = new wchar_t[lineBuffM.str().length() + 1];
						wcscpy((*temp), lineBuffM.str().c_str());

						size_t positionL(lineBuffM.str().find(L"\n")); uint16_t iterF(1);
						while (positionL != std::wstring::npos && iterF < count)
						{
							*((*temp) + positionL) = L'\0';
							*(temp + iterF) = (*temp) + (positionL + 1); ++iterF;
							positionL = lineBuffM.str().find(L"\n", positionL + 1);
						}
						lineBuffM.str(std::wstring()); lineBuffM.clear();
						check == 9 ? form->countColumnTitle = count : NULL;
						
					}
					count = 0;
				}
			}
	}
	else
	{
		const char* info_error = "Error load resource! Check resource ID. Exit programm";
		SetCurPos(static_cast<uint16_t>((form->coordXY.X >> 1) - ((strlen(info_error)) >> 1)),
			static_cast<uint16_t>(form->coordXY.Y >> 1));
		std::cout << info_error;
		Sleep(2000); exit(-2);
	}

	if (!title_contetnt)
	{
		title_contetnt = new wchar_t[wcslen(L"NONE TITLE CONTENT") + 1]; wcscpy(title_contetnt, L"NONE TITLE CONTENT");
	}
	
	lineBuff.str(std::wstring()); lineBuff.clear();
	return KeyData;
};