#include "Character.h"

void Character::ShowChar()
{
	if (condition[0][0] == 0)
	{
		std::cout << "�̸�: " << name << std::endl;
	}
	else if (condition[0][0] & SLEEP)
	{
		std::cout << "�̸�: " << name << "   (�����̻�: ���)" << std::endl;

	}
	std::cout << "Ư��: " << characteristic << std::endl;
	std::cout << "���� ������: " << haveItem << std::endl;
	std::cout << "ü��: " << hp << "    ";
	std::cout << "���ݷ�: " << atk << "    ";
	std::cout << "����: " << def << "    ";
	std::cout << "���ǵ�: " << spd << std::endl;
	std::cout << "�Ӽ�: " << propertyString << std::endl;

}

void Character::ShowCharFight()
{
	if (condition[0][0] == 0)
	{
		std::cout << "�̸�: " << name << std::endl;
	}
	else if (condition[0][0] & SLEEP)
	{
		std::cout << "�̸�: " << name << "   (�����̻�: ���)" << std::endl;
	}
	if (haveItem != "����")
	{
		std::cout << "���� ������: ����" << std::endl;

	}
	else
	{
		std::cout << "���� ������: ����" << std::endl;

	}
	if (hp <= 0)
	{
		std::cout << "ü��: 0 / " << maxHp << std::endl;

	}
	else
	{
		std::cout << "ü��: " << hp << " / " << maxHp << std::endl;

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


