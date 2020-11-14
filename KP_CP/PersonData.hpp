#pragma once
#include <cstdint>

typedef struct PersonData
{
	uint16_t idPerson;
	wchar_t SNM[31], specialty[11], DOB[11];
	int gender; uint32_t salary;

	struct WorkPlaceData
	{
		struct exper
		{
			uint16_t experYear, experMonth;
		};

		uint16_t idWorkshop, idDepartment, category;
		exper expervalue;
	};

	WorkPlaceData infoWork;
	

}Employee;

typedef struct ListPerson
{
	Employee EmployeeInfo;
	ListPerson* next;
	ListPerson* prev;

	ListPerson(): next(nullptr), prev(nullptr)
	{
		
		EmployeeInfo.gender = -1; EmployeeInfo.idPerson = 0; 
		EmployeeInfo.infoWork = { 0,0,0,0,0};
	}
}ListItem;

struct List
{
	ListItem* begin; ListItem* end; uint16_t countItemList; bool flag;
	List() : begin(nullptr), end(nullptr), countItemList(0), flag(0){}
};
