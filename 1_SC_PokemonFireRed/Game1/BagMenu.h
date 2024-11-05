#pragma once
enum class BagMenuState
{
	SEL,
	MENU,
	BATTEL_SEL,
	BATTEL_MENU
};
class BagMenu
{
public:
	ObImage* bagImg;
	ObImage* bagSelImg;
	ObImage* bagMenuImg;
	ObImage* bagMenuSelImg;
	ObImage* closeImg;

	BagMenuState state;

	Player* bagPlayer;
	Item* itemList[2];

	wstring usedItemName;

	int sel;
	int menuSel;

	//키 중첩 안되게 유예 시간 추가
	bool keyOn;
	float keyOnTime;

	//이미지 테스트
	int imgX;
	int imgY;

public:
	BagMenu();
	~BagMenu();
	void Update();
	void LateUpdate();
	void Render();
	void Sel();
	void Menu();
	void Battle_Sel();
	void Battle_Menu();
	void ContrlBagMenu();
	wstring UsedItemName() { return usedItemName; };



};

