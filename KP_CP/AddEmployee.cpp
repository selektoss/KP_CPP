#include "__AddEmployee__.hpp"

void AddInfoProfile(ListItem*& pointTemp)
{

};

void InsertListData(ListItem*& pointBeginList)
{

	ListItem* pointTemp(nullptr);

	char ChoiceYesOrNo = NULL;
	//do {
		pointTemp = new ListItem;
		AddInfoProfile(*&pointTemp);
		pointTemp->next = pointBeginList;
		pointBeginList = pointTemp;

		//std::cout << "\nProfile successfully added! ";
		//std::cout << "Continue adding? (y/n): ";
	//} while (Try_Error_Cin(ChoiceYesOrNo));
};