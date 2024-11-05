#pragma once
#include "Status.h"
#include "Skill.h"

//상태이상
#define SLEEP 1

class Character : public Status
{
private:



protected:


public:
	unsigned int property;
	unsigned int condition[2][1]; // [0][0]: 상태이상 확인, [1][0]: 남은 상태이상 턴수
	string haveItem;
	Skill* skill;
	string propertyString;
	int propertyArr[17];
	string characteristic;
	int maxHp;
	int damage;
	int jamtmp;

	float findProperty;
	int mySkillNum;


	int rankAtkCount;
	float rankAtk;
	int rankDefCount;
	float rankDef;
	int rankSpdCount;
	float rankSpd;

	Character() : damage(0), skill(new Skill()), findProperty(0), mySkillNum(0), jamtmp(0)
	{
		property = 0;
		haveItem = "";
		condition[0][0] = 0;
		condition[1][0] = 0;
		characteristic = "";
		maxHp = 0;

		rankAtkCount = 0;
		rankAtk = 0;
		rankDefCount = 0;
		rankDef = 0;
		rankSpdCount = 0;
		rankSpd = 0;
	}

	virtual int Attack(int _num) = 0;
	virtual void ShowAttack(int _num) = 0;
	virtual int Defense(int _damage, Character* atacker) = 0;
	virtual void ShowDefense(int _damage) = 0;



	void ShowChar();

	void ShowCharFight();


	void ShowSkill();

	float FindProperty(int attker, int target); //속성타입 상성 계산

	void SetRankAtk(int* _rankCount);
	void SetRankDef(int* _rankCount);
	void SetRankSpd(int* _rankCount);


};

