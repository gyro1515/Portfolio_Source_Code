#pragma once
#include "Character.h"

class CharacterA : public Character
{
	// 잠만보
	// 각 캐릭터 특성 추가하기
private:


protected:


public:
	CharacterA()
	{
		name = "잠만보";
		hp = 800;
		maxHp = 800;
		atk = 110;
		def = 110;
		spd = 30;
		property |= NORMAL;
		propertyString = "노멀";
		characteristic = "두꺼운 지방";
		condition[0][0] = 0;
		condition[1][0] = 0;
		haveItem = "먹다남은음식";// 매 턴 일정 체력 회복

		SetSkill();
	}

	void SetSkill();
	

	int Attack(int _num);
	

	void ShowAttack(int _num);

	int Defense(int _damage, Character* atacker);
	
	void ShowDefense(int _damage);

	void jamItem();

	
	
};

