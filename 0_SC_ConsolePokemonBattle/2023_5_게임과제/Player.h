#pragma once
#include "Store.h"
#include "Control.h"
#include "CharacterA.h"
#include "CharacterB.h"
#include "CharacterC.h"
#include "CharacterD.h"

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77



class Player
{
private:
	int myMoney;
	int selSkill;
	int selChar;
	int selCom;
	int turn; // 공격턴
	int progress; // 순서
	int playerSpd;
	int comSpd;
	int comtmp;
	int skillTmp;

	Control* ctrl;

	CharacterA* jam;
	CharacterB* hots;
	CharacterC* han;
	CharacterD* mang;



protected:


public:
	int x; //선택 좌표
	int y;
	Player() : myMoney(10000), selSkill(0), selChar(4), selCom(-1), turn(0), progress(0), x(0), y(0), playerSpd(0), comSpd(0), comtmp(0), skillTmp(0)
	{
		ctrl = new Control();

		jam = new CharacterA();
		hots = new CharacterB();
		han = new CharacterC();
		mang = new CharacterD();

	}

	void Move(int _move, int _xSize, int _ySize);

	void ShowSkillFight(Character* _char);

	void ShowYesNo();

	void ShowFightOrBag();

	void SelCom();

	void SkillEffect(float _findProperty);

	void Fight4(Character* player, Character* com);
	void Fight6(Character* player, Character* com);
	void Fight7(Character* player, Character* com);
	void Fight8(Character* player, Character* com);
	void Fight9(Character* player, Character* com);


	void Die(Character* player, Character* com);


	void Start();



};

