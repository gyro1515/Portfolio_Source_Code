#pragma once
#include "Status.h"


class Skill
{
private:
	

protected:


public:
	vector<int>* skillHp;
	vector<int>* skillAtk;
	vector<int>* skillDef;
	vector<int>* skillSpd;
	vector<string>* skillName;
	vector<int>* skillProperty;
	vector<int>* hitRate;
	

	Skill() : skillHp(new vector<int>(4)), skillAtk(new vector<int>(4)), skillDef(new vector<int>(4)), skillSpd(new vector<int>(4)), skillName(new vector<string>(4)), skillProperty(new vector<int>(4)), hitRate(new vector<int>(4))
	{
	}

	int HitRate(int _hitRate);




	
};

