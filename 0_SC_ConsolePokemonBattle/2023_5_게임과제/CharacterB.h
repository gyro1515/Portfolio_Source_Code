#pragma once
#include "Character.h"

class CharacterB : public Character
{
	//ÇÖ»ï
private:


protected:


public:
	CharacterB()
	{
		name = "ÇÖ»ï";
		hp = 650;
		maxHp = 650;
		atk = 130;
		def = 100;
		spd = 65;
		property |= STEEL;
		property |= BUG;
		propertyString = "°­Ã¶/¹ú·¹";
		characteristic = "Å×Å©´Ï¼Ç";// À§·Â 40 ÀÌÇÏ ½ºÅ³ °ø°Ý * 1.5
		condition[0][0] = 0;
		condition[1][0] = 0;
		haveItem = "ºñÇàÁÖ¾ó";

		SetSkill();
	}

	void SetSkill();

	int Attack(int _num);

	void ShowAttack(int _num);

	int Defense(int _damage, Character* attacker);
	
	void ShowDefense(int _damage);
	
};

