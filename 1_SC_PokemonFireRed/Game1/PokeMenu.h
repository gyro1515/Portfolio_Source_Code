#pragma once
enum class PokeMenuState
{
	SEL,
	MENU,
	CHANGE_SEL,
	BATTEL_SEL,
	BATTEL_LOSE_SEL,
	BAG_ITEM,
	USE_BAG_ITEM

};
class PokeMenu
{
public:
	ObImage* pokeListBack_Img;
	ObImage* pokeListPick1_Img[3];
	ObImage* pokeListPick2_Img[3];
	ObImage* pokeListPick3_Img[3];
	ObImage* pokeListPick4_Img[3];
	ObImage* pokeListPick5_Img[3];
	ObImage* pokeListPick6_Img[3];
	ObImage* pokeListPickC_Img[2];
	ObImage* pokeListHpG_Img[6];
	ObImage* pokeListHpY_Img[6];
	ObImage* pokeListHpR_Img[6];
	ObImage* pokeListDie[6];

	int pokeListSize;
	int selPokeList;
	int lastSelPokeList;
	int selChangePokeList;

	ObImage* outUseItem;
	float useItemTime;
	bool pokemonToBag;
	int changeHp;
	float changeHpFloat;

	Player* pokeMenuPlayer;
	Pokemon* pokeList[6];
	PokeMenuState state;
	wstring tempW;
	wstring tempW2;

	string tempS;

public:
	PokeMenu();
	~PokeMenu();
	void Update();
	void LateUpdate();
	void Render();

	void SetPokeMenu(Player* _player, int _myPokeSize);
	void ContrlPokeMenu();
	void SetState(PokeMenuState _state);
};

