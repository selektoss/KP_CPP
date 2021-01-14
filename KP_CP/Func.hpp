#pragma once
#include "__CurPosition__.hpp"
#include <iostream>
#include <iomanip>
#include "color.hpp"
#include "__AddEmployee__.hpp"
#include "UpdateContentBox.hpp"

void ShowInfoParamEmployee(ListItem*, const ModelOBJ*, bool value = true);

//Edit Employe list item.
void EditEmploye(ListItem*&, const ModelOBJ*);

//Removing an item from the list.
void DeleteEmploye(ListItem*&, List* list, const ModelOBJ* form, bool& flag);

//Flip list items.
void Reverse(List*);


ListItem* SearchEmployee(ListItem*, const ModelOBJ*, List*);
void DeleteEmployee(List*&, int&);
void PrintToTXT(List*, const ModelOBJ*);
void ShowResult(const uint16_t*, const ModelOBJ*, bool value = true);
void ShowInfoFooter(const ModelOBJ*, const wchar_t*, bool value = true);
void CaseMenu(ModelOBJ*, List*&, int&, char*&);
//void SortParamList(List*, int&);
//void ExchangeList(ListItem*, ListItem*, List*)