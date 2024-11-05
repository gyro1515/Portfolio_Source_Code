#include "CharacterD.h"

void CharacterD::SetSkill()
{
	(*skill->skillName)[0] = "����";
	(*skill->skillAtk)[0] = 120;
	(*skill->skillProperty)[0] |= DRAGON;

	(*skill->skillName)[1] = "����";
	(*skill->skillAtk)[1] = 100;
	(*skill->skillProperty)[1] |= GROUND;

	(*skill->skillName)[2] = "�ż�";
	(*skill->skillAtk)[2] = 80;
	(*skill->skillProperty)[2] |= NORMAL;
	(*skill->skillProperty)[2] |= SPEED;

	(*skill->skillName)[3] = "�Ҳ���ġ";
	(*skill->skillAtk)[3] = 75;
	(*skill->skillProperty)[3] |= FIRE;



}

int CharacterD::Attack(int _num)
{
	int result = 0;
	switch (_num)
	{
	case 0:
		if ((*skill->skillProperty)[0] & CharacterD::property)
		{
			if (CharacterD::haveItem == "�巡���־�")
			{
				CharacterD::haveItem = "����";
				result = (*skill->skillAtk)[0] / 4 * 9 * atk;

			}
			else
			{
				result = (*skill->skillAtk)[0] / 2 * 3 * atk;

			}
		}
		else
		{
			result = (*skill->skillAtk)[1] * atk;

		}
		break;
	case 1:
		if ((*skill->skillProperty)[1] & CharacterD::property)
		{
			result = (*skill->skillAtk)[1] / 2 * 3 * atk;
		}
		else
		{
			result = (*skill->skillAtk)[1] * atk;

		}
		break;
	case 2:
		result = (*skill->skillAtk)[2] * atk;

		break;
	case 3:
		result = (*skill->skillAtk)[3] * atk;

		break;

	}
	return result;
}

void CharacterD::ShowAttack(int _num)
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

int CharacterD::Defense(int _damage, Character* attacker)
{
	int result = 0;
	
	if (hp == maxHp)// Ư��: Ǯ���϶� �޴� ������ ����
	{
		_damage = (int)(_damage * attacker->findProperty * attacker->rankAtk / 2);

	}
	else
	{
		_damage = (int)(_damage * attacker->findProperty * attacker->rankAtk);

	}

	CharacterD::hp -= (int)(_damage / CharacterD::def * CharacterD::rankDef);

	return result;
}
void CharacterD::ShowDefense(int _damage) {

}