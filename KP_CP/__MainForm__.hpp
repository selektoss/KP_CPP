#pragma once

//#!!!
#pragma warning (disable:4996)
//#!!!

#include <Windows.h>
#include "MenuTitle.hpp"


void DrawBoxFormHeader(const COORD&, const std::wstring&, const uint16_t&);

void DrawMenuBox(const COORD&, const uint16_t&, const uint16_t&, uint16_t*&, uint16_t&, const LoBject::button*);

void DrawHelpTextBox(const ModelOBJ*);

void DrawContentDataBox(const ModelOBJ*, wchar_t*&, wchar_t**&);

void InitWeightColumnSectionContentBox(wchar_t**&, const uint16_t&, uint16_t&, uint16_t*&, const uint16_t&);

void DeleteObjModel(ModelOBJ*&);

void GenerateHashKey(char*&, uint16_t&);