#include "__SaveReadLocalFileData__.hpp"
#include <fstream>
#include "UpdateContentBox.hpp"
#include <iostream>



void LocalDataRead_AllocationMemoryList(List*& listEmployee, char*& key)
{
	std::ifstream localData("localDB.dat", std::ios_base::in | std::ios_base::ate | std::ios_base::binary);
	ListItem* takeData = nullptr; std::streampos fileSize(localData.tellg()); 
	
	size_t sizeFile(localData.tellg()), lenKey(strlen(key));
	if ((fileSize > sizeof(Employee)) && (((sizeFile - lenKey) % sizeof(Employee)) == 0))
	{
		uint16_t check = static_cast<uint16_t>(localData.tellg() / sizeof(Employee));
		if (localData.is_open())
		{
			char* keyequal(new char[lenKey + 1]);
			localData.seekg(0); 
			localData.read(keyequal, lenKey); *(keyequal + lenKey) = '\0';

			if (!strncmp(keyequal, key, (lenKey)))
			{
				takeData = new ListItem;
				while (localData.read((char*)&(takeData->EmployeeInfo), sizeof(Employee)))
				{
					if (!listEmployee->begin)
					{
						listEmployee->begin = takeData;
						listEmployee->end = takeData;
					}
					else
					{
						listEmployee->end->next = takeData;
						takeData->prev = listEmployee->end;
						listEmployee->end = takeData;
					}
					if (--check)
						takeData = new ListItem;
				}
			}
			localData.close(); delete[] keyequal;
		}
	}
 };

void SaveDataListLocalDB(List* listEmployee, char*& keyData)
{
	using namespace std;
	if (listEmployee->begin)
	{
		ListItem* tmpBegin = listEmployee->begin;
		ofstream fileData("localDB.dat", ios_base::out | ios_base::binary);
		if (fileData.is_open())
		{
			fileData.seekp(0); fileData.write(keyData, strlen(keyData));
			while (tmpBegin) {
				fileData.write((char*)&tmpBegin->EmployeeInfo, sizeof(Employee));
				tmpBegin = tmpBegin->next;
			}
			fileData.close();
		}
	}

};