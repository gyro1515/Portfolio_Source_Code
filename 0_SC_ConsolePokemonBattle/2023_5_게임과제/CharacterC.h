#pragma once
#include "Character.h"

class CharacterC : public Character
{

	//한카리아스
private:



protected:


public:
	CharacterC()
	{
		name = "한카리아스";
		hp = 540;
		maxHp = 540;
		atk = 130;
		def = 95;
		spd = 102;
		property |= DRAGON;
		property |= GROUND;
		propertyString = "드래곤/땅";
		characteristic = "까칠한피부";//맞으먄 상대한테 상대 최대체력비례 댐지
		condition[0][0] = 0;
		condition[1][0] = 0;
		haveItem = "기합의띠"; // 맞고 피 1이하로 갔을때 한 번 버텨줌

		SetSkill();
	}

	void SetSkill();
	
	int Attack(int _num);
	

	void ShowAttack(int _num);
	

	int Defense(int _damage, Character* attacker);
	
	void ShowDefense(int _damage);

	void Reflex(Character* attacker);
	
};

