#pragma once
#include "__CurPosition__.hpp"
#include <iostream>
#include <iomanip>
#include "color.hpp"
#include "__AddEmployee__.hpp"
#include "UpdateContentBox.hpp"

void ShowInfoParamEmployee(ListItem*, const ModelOBJ*, bool value = true);
void EditEmploye(ListItem*&, const ModelOBJ*);
void DeleteEmploye(ListItem*&, List* list);
void Reverse(List*);
ListItem* SearchEmployee(ListItem*, const ModelOBJ*, List*);
void DeleteEmployee(List*&, int&);
void PrintToTXT(List*, const ModelOBJ*);
void ShowResult(const uint16_t*, const ModelOBJ*, bool value = true);
void ShowInfoFooter(const ModelOBJ*, const wchar_t*, bool value = true);
void CaseMenu(ModelOBJ*, List*&, int&, char*&);