#pragma once
#include "Character.h"

class CharacterD : public Character
{

	//망나뇽
private:


protected:


public:
	CharacterD()
	{
		name = "망나뇽";
		hp = 455;
		maxHp = 455;
		atk = 134;
		def = 100;
		spd = 80;
		property |= DRAGON;
		property |= FLYING;
		propertyString = "드래곤/비행";
		characteristic = "멀티스케일";
		condition[0][0] = 0;
		condition[1][0] = 0;
		haveItem = "드래곤주얼"; //드래곤 타입 기술 공격 * 1.5, 1회용

		SetSkill();
	}

	void SetSkill();
	

	int Attack(int _num);

	void ShowAttack(int _num);

	int Defense(int _damage, Character* attacker);

	void ShowDefense(int _damage);
};

