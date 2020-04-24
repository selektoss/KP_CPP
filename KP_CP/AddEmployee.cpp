#include "__AddEmployee__.hpp"

void AddInfoProfile(ListPerson*& pointTemp)
{

};

void InsertListData(ListPerson*& pointBeginList)
{

	ListPerson* pointTemp(nullptr);

	char ChoiceYesOrNo = NULL;
	//do {
		pointTemp = new ListPerson;
		AddInfoProfile(*&pointTemp);
		pointTemp->next = pointBeginList;
		pointBeginList = pointTemp;

		//std::cout << "\nProfile successfully added! ";
		//std::cout << "Continue adding? (y/n): ";
	//} while (Try_Error_Cin(ChoiceYesOrNo));
};