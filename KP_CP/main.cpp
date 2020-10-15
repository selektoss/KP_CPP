#include "__LoadObjectForm__.hpp"
#include "__SaveReadLocalFileData__.hpp"
#include "UpdateContentBox.hpp"
#include "Func.hpp"

int main(void)
{	
	int chois(0); char* keyData(nullptr); ModelOBJ* objForm(LoadObjectForm(keyData)); List* lisT(new List);

	LocalDataRead_AllocationMemoryList(lisT, keyData);
	UpdateBoxContent(lisT->begin, objForm, chois);
	ShowInfoParamEmployee(lisT->begin, objForm);
	CaseMenu(objForm, lisT, chois, keyData);

	return 0;
};