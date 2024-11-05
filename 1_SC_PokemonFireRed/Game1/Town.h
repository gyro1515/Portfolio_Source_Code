#pragma once
enum class TownState
{
	TOWN,
	POKEMENU,
	POKEMON,
	BAG
};
class Town : public Scene
{
public:
	TownState state;
	ObTileMap* town;
	ObImage* townBack;
	ObImage* building1;
	ObImage* pokeCenter;
	ObImage* shop;
	ObImage* building1Roof;
	ObImage* pokeCenterRoof;
	ObImage* shopRoof;
	ObImage* door[3];
	//메뉴
	ObImage* mapMenu;
	ObImage* mapMenuSel;
	int menuSel;
	//메뉴 포켓몬
	PokeMenu* pokeMenu;
	//메뉴 가방
	BagMenu* bag;


	Player* player;
	//이동시킬 위치
	Vector2 plDest;
	Vector2 plSour;
	//비율
	float   g;
	Vector2 lastPos;
	//한 칸씩 이동
	bool playerGo;
	bool playerTurn;
	ObImage* onGrassImg;
	bool goWall;
	bool goShop;
	bool goCave;

	//포켓몬
	Pokemon* fieldPoke[10];
	Poke3* testPoke;
	//아이템
	Item* setItem[2];

	//사운드용
	float wallTime;

	//전투시작
	bool battleStart;

	//씬체인지용 타임
	float sceneTime;
	//조명
	float lightCol;
	int battleLightCount;
	bool battleLightOn;
	float lightTime;
	bool fadeIn;
	bool fadeOut;

	//테스트
	int imgX;
	int imgY;

public:
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void FAIDEIN();
	void SCENE_TO_TOWN();
	void TOWN();
	void POKEMENU();
	void POKEMON();
	void BAG();
	void SetSound();


};

