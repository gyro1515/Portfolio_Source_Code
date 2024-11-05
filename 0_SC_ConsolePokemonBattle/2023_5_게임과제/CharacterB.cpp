#include "CharacterB.h"

void CharacterB::SetSkill()
{
	(*skill->skillName)[0] = "Į��";
	(*skill->skillName)[1] = "�Ҹ���ġ"; //������
	(*skill->skillProperty)[1] |= STEEL;
	(*skill->skillProperty)[1] |= SPEED;
	(*skill->skillAtk)[1] = 60;
	(*skill->skillName)[2] = "��ũ����";
	(*skill->skillAtk)[2] = 55;
	(*skill->skillProperty)[2] |= FLYING;
	(*skill->skillName)[3] = "����";
	(*skill->skillAtk)[3] = 70;
	(*skill->skillProperty)[3] |= BUG;



}

int CharacterB::Attack(int _num)
{
	int result = 0;
	switch (_num)
	{
	case 0:
		
		CharacterB::rankAtkCount += 2;
		if (CharacterB::rankAtkCount >= 8)
		{
			CharacterB::rankAtkCount = 8;
		}
		
		break;
	case 1:
		if ((*skill->skillProperty)[1] & CharacterB::property)
		{
			result = (*skill->skillAtk)[1] / 2 * 3 * atk;
		}
		else
		{
			result = (*skill->skillAtk)[1] * atk;

		}
		break;
	case 2:
		if (CharacterB::haveItem == "�����־�")
		{
			result = (*skill->skillAtk)[2] * 3 * atk;

			CharacterB::haveItem = "����";
		}
		else if (CharacterB::haveItem == "����")
		{
			result = (*skill->skillAtk)[2] * 2 * atk;
		}
		else
		{
			result = (*skill->skillAtk)[2] * atk;

		}
		break;
	case 3:
		if ((*skill->skillProperty)[3] & CharacterB::property)
		{
			result = (*skill->skillAtk)[3] / 2 * 3 * atk;
		}
		else
		{
			result = (*skill->skillAtk)[3] * atk;

		}

		break;

	}
	return result;
}

void CharacterB::ShowAttack(int _num)
{
	switch (_num)
	{
	case 0:
		std::cout << name << "�� " << (*skill->skillName)[0] << "�� ����մϴ�." << std::endl;
		if (CharacterB::rankAtkCount >= 8)
		{
			std::cout << name << "�� ���ݷ� ��ũ�� ũ�� ����մϴ�." << std::endl;
			std::cout << "���̻� ���ݷ� ��ũ�� ������ �ʽ��ϴ�." << std::endl;

		}
		else
		{
			std::cout << name << "�� ���ݷ� ��ũ�� ũ�� ����մϴ�." << std::endl;

		}


		break;
	case 1:
		std::cout << name << "�� " << (*skill->skillName)[1] << "�� ����մϴ�." << std::endl;

		break;
	case 2:
		std::cout << name << "�� " << (*skill->skillName)[2] << "�� ����մϴ�." << std::endl;

		break;
	case 3:
		std::cout << name << "�� " << (*skill->skillName)[3] << "�� ����մϴ�." << std::endl;

		break;

	}
}

int CharacterB::Defense(int _damage, Character* attacker)
{
	int result = 0;


	_damage = (int)(_damage * attacker->findProperty * attacker->rankAtk);

	if (_damage > 0)
	{
		CharacterB::hp -= (int)(_damage / CharacterB::def * CharacterB::rankDef);
	}
	return result;

}
void CharacterB::ShowDefense(int _damage)
{

}