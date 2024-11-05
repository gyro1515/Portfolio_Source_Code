#include "CharacterB.h"

void CharacterB::SetSkill()
{
	(*skill->skillName)[0] = "칼춤";
	(*skill->skillName)[1] = "불릿펀치"; //선공기
	(*skill->skillProperty)[1] |= STEEL;
	(*skill->skillProperty)[1] |= SPEED;
	(*skill->skillAtk)[1] = 60;
	(*skill->skillName)[2] = "애크러뱃";
	(*skill->skillAtk)[2] = 55;
	(*skill->skillProperty)[2] |= FLYING;
	(*skill->skillName)[3] = "유턴";
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
		if (CharacterB::haveItem == "비행주얼")
		{
			result = (*skill->skillAtk)[2] * 3 * atk;

			CharacterB::haveItem = "없음";
		}
		else if (CharacterB::haveItem == "없음")
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
		std::cout << name << "가 " << (*skill->skillName)[0] << "을 사용합니다." << std::endl;
		if (CharacterB::rankAtkCount >= 8)
		{
			std::cout << name << "의 공격력 랭크가 크게 상승합니다." << std::endl;
			std::cout << "더이상 공격력 랭크가 오르지 않습니다." << std::endl;

		}
		else
		{
			std::cout << name << "의 공격력 랭크가 크게 상승합니다." << std::endl;

		}


		break;
	case 1:
		std::cout << name << "가 " << (*skill->skillName)[1] << "를 사용합니다." << std::endl;

		break;
	case 2:
		std::cout << name << "가 " << (*skill->skillName)[2] << "을 사용합니다." << std::endl;

		break;
	case 3:
		std::cout << name << "가 " << (*skill->skillName)[3] << "을 사용합니다." << std::endl;

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