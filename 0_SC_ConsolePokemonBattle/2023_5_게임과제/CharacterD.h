#pragma once
#include "Character.h"

class CharacterD : public Character
{

	//������
private:


protected:


public:
	CharacterD()
	{
		name = "������";
		hp = 455;
		maxHp = 455;
		atk = 134;
		def = 100;
		spd = 80;
		property |= DRAGON;
		property |= FLYING;
		propertyString = "�巡��/����";
		characteristic = "��Ƽ������";
		condition[0][0] = 0;
		condition[1][0] = 0;
		haveItem = "�巡���־�"; //�巡�� Ÿ�� ��� ���� * 1.5, 1ȸ��

		SetSkill();
	}

	void SetSkill();
	

	int Attack(int _num);

	void ShowAttack(int _num);

	int Defense(int _damage, Character* attacker);

	void ShowDefense(int _damage);
};

