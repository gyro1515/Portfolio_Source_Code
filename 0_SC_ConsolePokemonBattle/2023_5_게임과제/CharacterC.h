#pragma once
#include "Character.h"

class CharacterC : public Character
{

	//��ī���ƽ�
private:



protected:


public:
	CharacterC()
	{
		name = "��ī���ƽ�";
		hp = 540;
		maxHp = 540;
		atk = 130;
		def = 95;
		spd = 102;
		property |= DRAGON;
		property |= GROUND;
		propertyString = "�巡��/��";
		characteristic = "��ĥ���Ǻ�";//������ ������� ��� �ִ�ü�º�� ����
		condition[0][0] = 0;
		condition[1][0] = 0;
		haveItem = "�����Ƕ�"; // �°� �� 1���Ϸ� ������ �� �� ������

		SetSkill();
	}

	void SetSkill();
	
	int Attack(int _num);
	

	void ShowAttack(int _num);
	

	int Defense(int _damage, Character* attacker);
	
	void ShowDefense(int _damage);

	void Reflex(Character* attacker);
	
};

