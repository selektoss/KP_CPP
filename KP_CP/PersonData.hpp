#pragma once
#include <cstdint>
typedef struct PersonData
{
	uint16_t idPerson;
	char SNM[31], specialty[11], DOB[10];
	bool gender; float salary;

	struct WorkPlaceData
	{
		uint16_t idWorkshop, idDepartment, category;
		uint16_t experYear, experMonth;
	};
	WorkPlaceData infoWork;
}Employee;

typedef struct ListPerson
{
	Employee EmployeeInfo;
	ListPerson* next;
}ListItem;