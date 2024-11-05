#include "CharacterD.h"

void CharacterD::SetSkill()
{
	(*skill->skillName)[0] = "역린";
	(*skill->skillAtk)[0] = 120;
	(*skill->skillProperty)[0] |= DRAGON;

	(*skill->skillName)[1] = "지진";
	(*skill->skillAtk)[1] = 100;
	(*skill->skillProperty)[1] |= GROUND;

	(*skill->skillName)[2] = "신속";
	(*skill->skillAtk)[2] = 80;
	(*skill->skillProperty)[2] |= NORMAL;
	(*skill->skillProperty)[2] |= SPEED;

	(*skill->skillName)[3] = "불꽃펀치";
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
			if (CharacterD::haveItem == "드래곤주얼")
			{
				CharacterD::haveItem = "없음";
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
		std::cout << name << "가 " << (*skill->skillName)[0] << "을 사용합니다." << std::endl;

		break;
	case 1:
		std::cout << name << "가 " << (*skill->skillName)[1] << "을 사용합니다." << std::endl;

		break;
	case 2:
		std::cout << name << "가 " << (*skill->skillName)[2] << "을 사용합니다." << std::endl;

		break;
	case 3:
		std::cout << name << "가 " << (*skill->skillName)[3] << "를 사용합니다." << std::endl;

		break;

	}
}

int CharacterD::Defense(int _damage, Character* attacker)
{
	int result = 0;
	
	if (hp == maxHp)// 특성: 풀피일때 받는 데미지 절반
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