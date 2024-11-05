#include "CharacterC.h"

void CharacterC::SetSkill()
{
	(*skill->skillName)[0] = "����";
	(*skill->skillAtk)[0] = 100;
	(*skill->skillProperty)[0] |= GROUND;

	(*skill->skillName)[1] = "����";
	(*skill->skillAtk)[1] = 120;
	(*skill->skillProperty)[1] |= DRAGON;

	(*skill->skillName)[2] = "���濡��";
	(*skill->skillAtk)[2] = 100;
	(*skill->skillProperty)[2] |= ROCK;
	(*skill->hitRate)[2] = 80;

	(*skill->skillName)[3] = "�Ҵ빮��";
	(*skill->skillAtk)[3] = 120;
	(*skill->skillProperty)[3] |= FIRE;
	(*skill->hitRate)[3] = 85;
}

int CharacterC::Attack(int _num)
{
	int result = 0;
	switch (_num)
	{
	case 0:
		if ((*skill->skillProperty)[0] & CharacterC::property)
		{
			result = (*skill->skillAtk)[0] / 2 * 3 * atk;
		}
		else
		{
			result = (*skill->skillAtk)[0] * atk;

		}
		break;
	case 1:
		if ((*skill->skillProperty)[1] & CharacterC::property)
		{
			result = (*skill->skillAtk)[1] / 2 * 3 * atk;
		}
		else
		{
			result = (*skill->skillAtk)[1] * atk;

		}
		break;
	case 2:
		if (skill->HitRate((*skill->hitRate)[2]) == 0)
		{
			result = (*skill->skillAtk)[2] * atk;

		}
		else
		{
			result = -1;//������
		}
		break;
	case 3:
		if (skill->HitRate((*skill->hitRate)[3]) == 0)
		{
			result = (*skill->skillAtk)[3] * atk;

		}
		else
		{
			result = -1;//������
		}

		break;

	}
	return result;
}

void CharacterC::ShowAttack(int _num)
{
	switch (_num)
	{
	case 0:
		std::cout << name << "�� " << (*skill->skillName)[0] << "�� ����մϴ�." << std::endl;

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

int CharacterC::Defense(int _damage, Character* attacker) //��ī���ƽ� Ư��: ������ ���� ü�º�� ������ ��
{
	int result = 0;


	_damage = (int)(_damage * attacker->findProperty * attacker->rankAtk);

	CharacterC::hp -= (int)(_damage / CharacterC::def * CharacterC::rankDef);

	if (CharacterC::haveItem == "�����Ƕ�" && CharacterC::hp < 1)
	{
		CharacterC::haveItem = "����";

		CharacterC::hp = 1;
	}
	return result;
}
void CharacterC::ShowDefense(int _damage)
{

}
void CharacterC::Reflex(Character* attacker)
{
	std::cout << "��ī���ƽ� Ư�� ��ĥ���Ǻ� ����" << std::endl;
	attacker->hp -= (attacker->maxHp / 8);
}

