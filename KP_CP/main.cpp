#include "__LoadObjectForm__.hpp"
#include "__SaveReadLocalFileData__.hpp"
#include "UpdateContentBox.hpp"
#include "Func.hpp"

int main(void)
{	
	int chois(0); char* keyData(nullptr); ModelOBJ* objForm(LoadObjectForm(keyData)); List* listEmployee(new List);

	LocalDataRead_AllocationMemoryList(listEmployee, keyData);
	UpdateBoxContent(listEmployee->begin, objForm, chois);
	ShowInfoParamEmployee(listEmployee->begin, objForm);
	CaseMenu(objForm, listEmployee, chois, keyData);

	return 0;
};