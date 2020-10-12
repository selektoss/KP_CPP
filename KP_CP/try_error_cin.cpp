#include "try_error_cin.hpp"
#include <conio.h>

bool Try_Error_Cin(int& ChoiceYesOrNo)
{
	while (ChoiceYesOrNo = _getch())
	{
		if (ChoiceYesOrNo == 'y' || ChoiceYesOrNo == 'n')
		{
			return (ChoiceYesOrNo == 'y');
		}
	}
};