#include "__SaveReadLocalFileData__.hpp"
#include <fstream>

ListItem* CheckLocalDataRead(ListItem* pointList)
{
	using namespace std;
	ifstream localData("localDB.dat", ios_base::in | ios_base::ate | ios_base::binary);
	ListItem* takeData = nullptr;
	uint64_t sizeStepFileData = localData.tellg();
	if (localData.is_open() && localData.tellg())
	{
			localData.seekg(sizeStepFileData -= sizeof(Employee));
			takeData = new ListItem;

			while (localData.read((char*)&(*takeData), sizeof(Employee)))
			{
				takeData->next = pointList;
				pointList = &*takeData;
				if (!sizeStepFileData)
					break;
				else takeData = new ListItem;
				localData.seekg(sizeStepFileData -= sizeof(Employee));
			}
		localData.close(); return pointList;
	}else
	return nullptr;
};

void SaveDataListLocalDB(ListItem* pointStart)
{
	using namespace std;
	if (pointStart)
	{
		ofstream fileData("localDB.dat", ios_base::out | ios_base::binary);
		if (fileData.is_open())
		{
			while (pointStart) {
				fileData.write((char*)&*pointStart, sizeof(Employee));
				pointStart = pointStart->next;
			}
			fileData.close();
		}
	}
	else remove("localDB.dat");
};