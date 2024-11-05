#pragma once
enum class CaveState
{
	CAVE,
	POKEMENU,
	POKEMON,
	BAG
};
class Cave : public Scene
{
public:
	CaveState state;
	ObTileMap* cave;
	ObImage* jam;
	Int2 ranJam[9];
	int tempRan;
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
	//길찾기용 변수
	vector<Tile*> PlWay;
	//길찾기 색 변경용 변수;
	vector<Tile*> TmpPlWay;

	bool playAni;
	//비율
	float   g;
	Vector2 lastPos;
	//한 칸씩 이동
	bool playerGo;
	bool playerTurn;
	ObImage* onGrassImg;
	bool goWall;
	bool goShop;

	//포켓몬
	Pokemon* fieldPoke;
	
	//사운드용
	float wallTime;

	//전투시작
	bool battleStart;

	//씬전환
	bool goTown;
	float sceneTime;
	//조명
	float lightCol;
	float lightTime;
	bool fadeIn;
	bool fadeOut;
	int battleLightCount;
	bool battleLightOn;

public:
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;
	void CAVE();
	void POKEMENU();
	void POKEMON();
	void BAG();
};

