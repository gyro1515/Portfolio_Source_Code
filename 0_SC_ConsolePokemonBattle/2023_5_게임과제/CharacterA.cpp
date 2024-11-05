#include "CharacterA.h"

void CharacterA::SetSkill()
{
	(*skill->skillName)[0] = "잠꼬대";
	(*skill->skillName)[1] = "잠자기";
	(*skill->skillName)[2] = "누르기";
	(*skill->skillAtk)[2] = 85;
	(*skill->skillProperty)[2] |= NORMAL;
	(*skill->skillName)[3] = "땅가르기";
	(*skill->skillAtk)[3] = 99999;
	(*skill->skillProperty)[3] |= GROUND;
	(*skill->hitRate)[3] = 30;



}

int CharacterA::Attack(int _num)
{
	int result = 0;
	int tmp = 0;
	switch (_num)
	{
	case 0:
		if (condition[0][0] & SLEEP)
		{
			jamtmp = rand() % 3 + 1;
			if (jamtmp == 2)
			{
				(*skill->skillProperty)[0] |= NORMAL;
			}
			else if (jamtmp == 3)
			{
				(*skill->skillProperty)[0] |= GROUND;
			}
			else
			{
				(*skill->skillProperty)[0] = 0;

			}
			result = CharacterA::Attack(jamtmp);
		}
		else
		{
			result = -2;
		}
		break;
	case 1:
		condition[0][0] = 0;
		hp = maxHp;
		condition[0][0] = SLEEP;
		condition[0][1] = 2;
		break;
	case 2:
		if ((*skill->skillProperty)[2] & CharacterA::property)
		{
			result = (*skill->skillAtk)[2] / 2 * 3 * atk;
		}
		else
		{
			result = (*skill->skillAtk)[2] * atk;

		}
		break;
	case 3:
		if (skill->HitRate((*skill->hitRate)[3]) == 0)
		{
			result = (*skill->skillAtk)[3] * atk;

		}
		else
		{
			result = -1;//빗나감
		}
		break;

	}
	return result;
}

void CharacterA::ShowAttack(int _num)
{
	switch (_num)
	{
	case 0:
		if (condition[0][0] & SLEEP)
		{
			std::cout << name << "가 " << (*skill->skillName)[0] << "를 사용합니다. 무작위로 스킬 사용!" << std::endl;

			CharacterA::ShowAttack(jamtmp);
		}
		else
		{
			std::cout << "잠든 상태에서만 사용할 수 있습니다." << std::endl;
		}
		break;
	case 1:
		std::cout << name << "가 " << (*skill->skillName)[1] << "를 사용합니다." << std::endl;
		std::cout << name << "가 체력을 회복합니다." << std::endl;

		break;
	case 2:
		std::cout << name << "가 " << (*skill->skillName)[2] << "를 사용합니다." << std::endl;
		break;
	case 3:
		std::cout << name << "가 " << (*skill->skillName)[3] << "를 사용합니다." << std::endl;
		break;

	}
}

int CharacterA::Defense(int _damage, Character* attacker) //잠만보 특성: 얼음 불 속성 -0.2f씩
{
	int result = 0;

	if ((*attacker->skill->skillProperty)[attacker->mySkillNum] & FIRE || (*attacker->skill->skillProperty)[attacker->mySkillNum] & ICE)
	{
		attacker->findProperty -= 0.2f;
	}

	_damage = (int)(_damage * attacker->findProperty * attacker->rankAtk);


	if (_damage > 0)
	{
		CharacterA::hp -= (int)(_damage / CharacterA::def * CharacterA::rankDef);
	}

	return result;

}

void CharacterA::ShowDefense(int _damage)
{
	if (_damage > 0)
	{
		std::cout << name;
	}
}

void CharacterA::jamItem()
{
	if (CharacterA::hp < CharacterA::maxHp)
	{
		CharacterA::hp += CharacterA::maxHp / 16;
		if (CharacterA::hp >= CharacterA::maxHp)
		{
			CharacterA::hp = CharacterA::maxHp;
		}
	}
}

