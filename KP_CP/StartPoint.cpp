#include "__LoadObjectForm__.hpp"
#include "__SaveReadLocalFileData__.hpp"

int main(void)
{	
	ModelOBJ* objForm(LoadObjectForm());
	ListPerson* beginList(nullptr); beginList = CheckLocalDataRead(beginList);
	

	

	
	int chois(0);
	while ((chois = ChoisMenu(objForm)) < objForm->sizeMenu - 1)
	{
		switch (chois)
		{
		case 0:
		{
			

		} break;
		case 1:
		{
			

		} break;
		case 2:
		{
			
		} break;
		case 3:
		{
			
		} break;
		case 4:
		{
			
		} break;
		case 5:
		{
			
		} break;
		case 6:
		{
			
		} break;
		}
	}
	return 0;
};