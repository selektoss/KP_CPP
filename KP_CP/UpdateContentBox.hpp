#pragma once
#include "PersonData.hpp"
#include "MenuTitle.hpp"

void UpdateBoxContent(ListItem*, const ModelOBJ*, int&, bool value = false);
bool choisListContent(const ModelOBJ*, List*);
void CoutList(const ListItem*, const ModelOBJ*);
bool ChoisEmployee(ListItem*&, const ModelOBJ*, List*);
void DrawButtonEmployeeChoise(int& , uint16_t&, uint16_t&, const char(*a)[11], const uint16_t&);