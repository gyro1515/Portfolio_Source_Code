#pragma once
#include "Character.h"

class CharacterA : public Character
{
	// �Ḹ��
	// �� ĳ���� Ư�� �߰��ϱ�
private:


protected:


public:
	CharacterA()
	{
		name = "�Ḹ��";
		hp = 800;
		maxHp = 800;
		atk = 110;
		def = 110;
		spd = 30;
		property |= NORMAL;
		propertyString = "���";
		characteristic = "�β��� ����";
		condition[0][0] = 0;
		condition[1][0] = 0;
		haveItem = "�Դٳ�������";// �� �� ���� ü�� ȸ��

		SetSkill();
	}

	void SetSkill();
	

	int Attack(int _num);
	

	void ShowAttack(int _num);

	int Defense(int _damage, Character* atacker);
	
	void ShowDefense(int _damage);

	void jamItem();

	
	
};

