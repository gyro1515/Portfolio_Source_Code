#include "Control.h"

int Control::GetKey()
{
	input = _getch();
	return input;
}
