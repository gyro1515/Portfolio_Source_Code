#pragma once
#include "Character.h"

class CharacterB : public Character
{
	//�ֻ�
private:


protected:


public:
	CharacterB()
	{
		name = "�ֻ�";
		hp = 650;
		maxHp = 650;
		atk = 130;
		def = 100;
		spd = 65;
		property |= STEEL;
		property |= BUG;
		propertyString = "��ö/����";
		characteristic = "��ũ�ϼ�";// ���� 40 ���� ��ų ���� * 1.5
		condition[0][0] = 0;
		condition[1][0] = 0;
		haveItem = "�����־�";

		SetSkill();
	}

	void SetSkill();

	int Attack(int _num);

	void ShowAttack(int _num);

	int Defense(int _damage, Character* attacker);
	
	void ShowDefense(int _damage);
	
};

