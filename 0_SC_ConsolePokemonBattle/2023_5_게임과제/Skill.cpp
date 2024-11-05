#include "Skill.h"


int Skill::HitRate(int _hitRate)
{
	int result = 0;
	int percentage = rand() % 100 + 1;
	if (percentage <= _hitRate)
	{
		result = 0;
	}
	else
	{
		result = -1;
	}
	return result;
}
