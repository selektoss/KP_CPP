#pragma once
#include "PersonData.hpp"
#include "MenuTitle.hpp"

void AddInfoProfile(ListItem*&, const ModelOBJ*, List* tmpb = nullptr);
void InsertListData(List*&, const ModelOBJ*);
void fixErrorDrawing(const uint16_t&, const uint16_t&, const uint16_t&);
void jumpPosCurInfoAdd(const uint16_t&, const uint16_t&, const uint16_t&);
bool RegxCheck(wchar_t* line, const wchar_t* regular, const uint16_t& tmpX, uint16_t& tmpY, const uint16_t& weightContent);