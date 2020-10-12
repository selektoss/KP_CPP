#pragma once
#include "MenuTitle.hpp"
#include "PersonData.hpp"

ModelOBJ*& LoadObjectForm(char*&);
void UpdateMenu(const ModelOBJ*, const int&);
int ChoisMenu(ModelOBJ*&, List*);