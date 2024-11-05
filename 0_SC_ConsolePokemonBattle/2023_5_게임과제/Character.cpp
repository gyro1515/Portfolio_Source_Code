#include "Character.h"

void Character::ShowChar()
{
	if (condition[0][0] == 0)
	{
		std::cout << "이름: " << name << std::endl;
	}
	else if (condition[0][0] & SLEEP)
	{
		std::cout << "이름: " << name << "   (상태이상: 잠듦)" << std::endl;

	}
	std::cout << "특성: " << characteristic << std::endl;
	std::cout << "보유 아이템: " << haveItem << std::endl;
	std::cout << "체력: " << hp << "    ";
	std::cout << "공격력: " << atk << "    ";
	std::cout << "방어력: " << def << "    ";
	std::cout << "스피드: " << spd << std::endl;
	std::cout << "속성: " << propertyString << std::endl;

}

void Character::ShowCharFight()
{
	if (condition[0][0] == 0)
	{
		std::cout << "이름: " << name << std::endl;
	}
	else if (condition[0][0] & SLEEP)
	{
		std::cout << "이름: " << name << "   (상태이상: 잠듦)" << std::endl;
	}
	if (haveItem != "없음")
	{
		std::cout << "보유 아이템: 있음" << std::endl;

	}
	else
	{
		std::cout << "보유 아이템: 없음" << std::endl;

	}
	if (hp <= 0)
	{
		std::cout << "체력: 0 / " << maxHp << std::endl;

	}
	else
	{
		std::cout << "체력: " << hp << " / " << maxHp << std::endl;

	}

}

void Character::ShowSkill()
{
	for (int i = 0; i < 2; i++)
	{
		std::cout << "* " << (*skill->skillName)[i] << "   ";

	}
	std::cout << std::endl;
	for (int i = 2; i < 4; i++)
	{
		std::cout << "* " << (*skill->skillName)[i] << "   ";

	}
	std::cout << std::endl;

}

float Character::FindProperty(int attker, int target)
{
	float result = 1.0f;

	if (attker & NORMAL)
	{
		if (target & ROCK)
		{
			result -= 0.2f;
		}
		if (target & STEEL)
		{
			result -= 0.2f;
		}
		if (target & GHOST)
		{
			result *= 0;
		}
	}
	else if (attker & FIRE)
	{
		if (target & FIRE)
		{
			result -= 0.2f;
		}
		if (target & WATER)
		{
			result -= 0.2f;
		}

		if (target & ROCK)
		{
			result -= 0.2f;
		}
		if (target & DRAGON)
		{
			result -= 0.2f;
		}
		if (target & GRASS)
		{
			result += 0.2f;
		}
		if (target & ICE)
		{
			result += 0.2f;
		}
		if (target & BUG)
		{
			result += 0.2f;
		}
		if (target & STEEL)
		{
			result += 0.2f;
		}

	}
	else if (attker & WATER)
	{
		if (target & WATER)
		{
			result -= 0.2f;
		}
		if (target & GRASS)
		{
			result -= 0.2f;
		}
		if (target & DRAGON)
		{
			result -= 0.2f;
		}
		if (target & FIRE)
		{
			result += 0.2f;
		}
		if (target & GROUND)
		{
			result += 0.2f;
		}
		if (target & ROCK)
		{
			result += 0.2f;
		}
	}
	else if (attker & ELECTIRC)
	{
		if (target & ELECTIRC)
		{
			result -= 0.2f;
		}
		if (target & GRASS)
		{
			result -= 0.2f;
		}if (target & DRAGON)
		{
			result -= 0.2f;
		}
		if (target & WATER)
		{
			result += 0.2f;
		}
		if (target & FLYING)
		{
			result += 0.2f;
		}
		if (target & GROUND)
		{
			result *= 0.0f;
		}

	}
	else if (attker & GRASS)
	{
		if (target & FIRE)
		{
			result -= 0.2f;
		}
		if (target & GRASS)
		{
			result -= 0.2f;
		}if (target & POISON)
		{
			result -= 0.2f;
		}
		if (target & FLYING)
		{
			result -= 0.2f;
		}
		if (target & BUG)
		{
			result -= 0.2f;
		}
		if (target & DRAGON)
		{
			result -= 0.2f;
		}
		if (target & STEEL)
		{
			result -= 0.2f;
		}
		if (target & WATER)
		{
			result += 0.2f;
		}
		if (target & GROUND)
		{
			result += 0.2f;
		}
		if (target & ROCK)
		{
			result += 0.2f;
		}

	}
	else if (attker & ICE)
	{
		if (target & FIRE)
		{
			result -= 0.2f;
		}
		if (target & WATER)
		{
			result -= 0.2f;
		}
		if (target & ICE)
		{
			result -= 0.2f;
		}
		if (target & STEEL)
		{
			result -= 0.2f;
		}
		//
		if (target & GRASS)
		{
			result += 0.2f;
		}
		if (target & GROUND)
		{
			result += 0.2f;
		}
		if (target & FLYING)
		{
			result += 0.2f;
		}
		if (target & DRAGON)
		{
			result += 0.2f;
		}

	}
	else if (attker & FIGHTING)
	{
		if (target & POISON)
		{
			result -= 0.2f;
		}
		if (target & FLYING)
		{
			result -= 0.2f;
		}

		if (target & PSYCHIC)
		{
			result -= 0.2f;
		}
		if (target & BUG)
		{
			result -= 0.2f;
		}//
		if (target & NORMAL)
		{
			result += 0.2f;
		}
		if (target & ICE)
		{
			result += 0.2f;
		}
		if (target & ROCK)
		{
			result += 0.2f;
		}
		if (target & DARK)
		{
			result += 0.2f;
		}
		if (target & STEEL)
		{
			result += 0.2f;
		}
	}
	else if (attker & POISON)
	{
		if (target & POISON)
		{
			result -= 0.2f;
		}
		if (target & GROUND)
		{
			result -= 0.2f;
		}if (target & ROCK)
		{
			result -= 0.2f;
		}if (target & GHOST)
		{
			result -= 0.2f;
		}
		//
		if (target & GRASS)
		{
			result += 0.2f;
		}
		if (target & GHOST)
		{
			result *= 0.0f;
		}

	}
	else if (attker & GROUND)
	{
		if (target & GRASS)
		{
			result -= 0.2f;
		}
		if (target & BUG)
		{
			result -= 0.2f;
		}//
		if (target & FIRE)
		{
			result += 0.2f;
		}
		if (target & ELECTIRC)
		{
			result += 0.2f;
		}
		if (target & POISON)
		{
			result += 0.2f;
		}
		if (target & ROCK)
		{
			result += 0.2f;
		}
		if (target & STEEL)
		{
			result += 0.2f;
		}
		if (target & FLYING)
		{
			result *= 0.0f;
		}

	}
	else if (attker & FLYING)
	{
		if (target & ELECTIRC)
		{
			result -= 0.2f;
		}
		if (target & ROCK)
		{
			result -= 0.2f;
		}if (target & STEEL)
		{
			result -= 0.2f;
		}
		if (target & GRASS)
		{
			result += 0.2f;
		}
		if (target & FIGHTING)
		{
			result += 0.2f;
		}
		if (target & BUG)
		{
			result += 0.2f;
		}

	}
	else if (attker & PSYCHIC)
	{
		if (target & PSYCHIC)
		{
			result -= 0.2f;
		}
		if (target & STEEL)
		{
			result -= 0.2f;
		}//
		if (target & FIGHTING)
		{
			result += 0.2f;
		}
		if (target & POISON)
		{
			result += 0.2f;
		}
		if (target & DARK)
		{
			result *= 0.0f;
		}

	}
	else if (attker & BUG)
	{
		if (target & FIRE)
		{
			result -= 0.2f;
		}
		if (target & FIGHTING)
		{
			result -= 0.2f;
		}if (target & POISON)
		{
			result -= 0.2f;
		}
		if (target & FLYING)
		{
			result -= 0.2f;
		}
		if (target & GHOST)
		{
			result -= 0.2f;
		}
		if (target & STEEL)
		{
			result -= 0.2f;
		}//
		if (target & GRASS)
		{
			result += 0.2f;
		}
		if (target & PSYCHIC)
		{
			result += 0.2f;
		}
		if (target & DARK)
		{
			result += 0.2f;
		}

	}
	else if (attker & ROCK)
	{
		if (target & FIGHTING)
		{
			result -= 0.2f;
		}
		if (target & GROUND)
		{
			result -= 0.2f;
		}if (target & STEEL)
		{
			result -= 0.2f;
		}//
		if (target & FIRE)
		{
			result += 0.2f;
		}
		if (target & ICE)
		{
			result += 0.2f;
		}
		if (target & FLYING)
		{
			result += 0.2f;
		}
		if (target & BUG)
		{
			result += 0.2f;
		}

	}
	else if (attker & GHOST)
	{
		if (target & DARK)
		{
			result -= 0.2f;
		}
		if (target & STEEL)
		{
			result -= 0.2f;
		}//
		if (target & PSYCHIC)
		{
			result += 0.2f;
		}
		if (target & GHOST)
		{
			result += 0.2f;
		}
		if (target & NORMAL)
		{
			result *= 0.0f;
		}

	}
	else if (attker & DRAGON)
	{
		if (target & STEEL)
		{
			result -= 0.2f;
		}
		if (target & DRAGON)
		{
			result += 0.2f;
		}

	}
	else if (attker & DARK)
	{
		if (target & FIGHTING)
		{
			result -= 0.2f;
		}
		if (target & DARK)
		{
			result -= 0.2f;
		}if (target & STEEL)
		{
			result -= 0.2f;
		}//
		if (target & PSYCHIC)
		{
			result += 0.2f;
		}
		if (target & GHOST)
		{
			result += 0.2f;
		}


	}
	else if (attker & STEEL)
	{
		if (target & FIRE)
		{
			result -= 0.2f;
		}
		if (target & WATER)
		{
			result -= 0.2f;
		}if (target & ELECTIRC)
		{
			result -= 0.2f;
		}if (target & STEEL)
		{
			result -= 0.2f;
		}//
		if (target & ICE)
		{
			result += 0.2f;
		}
		if (target & ROCK)
		{
			result += 0.2f;
		}

	}

	return result;
}

void Character::SetRankAtk(int* _rankCount)
{
	if (*_rankCount >= 0)
	{
		rankAtk = *_rankCount * 0.5f + 1;
	}
	else
	{
		*_rankCount *= -1;
		rankAtk = (float)1 / (*_rankCount * 0.5f + 1);
	}
}
void Character::SetRankDef(int* _rankCount)
{
	if (*_rankCount >= 0)
	{
		rankDef = *_rankCount * 0.5f + 1;
	}
	else
	{
		*_rankCount *= -1;
		rankDef = (float)1 / (*_rankCount * 0.5f + 1);
	}
}
void Character::SetRankSpd(int* _rankCount)
{
	if (*_rankCount >= 0)
	{
		rankSpd = *_rankCount * 0.5f + 1;
	}
	else
	{
		*_rankCount *= -1;
		rankSpd = (float)1 / (*_rankCount * 0.5f + 1);
	}
}


