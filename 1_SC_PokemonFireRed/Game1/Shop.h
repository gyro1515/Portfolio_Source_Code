#pragma once
enum class ShopState
{
	SHOP,
	MENU,
	BUY,
	SEL,
	POKEMENU,
	POKEMON,
	BAG
};
class Shop : public Scene
{
public:
	ShopState state;
	ObTileMap* shop;
	ObImage* shopBack;
	ObImage* shopFront;
	ObImage* shopSel1;
	ObImage* shopSel2;
	ObImage* shopSel3;
	ObImage* shopSel4;
	ObImage* shopSel5;
	ObImage* shopMenu;
	int shopMenuSel;
	int buyNum;
	int selNum;
	int totalNum;
	float keyDownTime;
	wstring sel_0;
	bool isErase;

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
	bool goWall;
	//사운드용
	float wallTime;
	//아이템
	Item* setItem[2];
	ObImage* closeImg;

	//상점 메세지
	wstring shopMes;
	int mesNum;
	int mesIndex;
	float mesTime;
	//씬전환
	bool goTown;
	//조명
	float lightCol;
	bool fadeIn;
	bool fadeOut;

public:
	// Scene을(를) 통해 상속됨
	virtual void Init() override;
	virtual void Release() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void Render() override;
	virtual void ResizeScreen() override;

	void SHOP();
	void MENU();
	void BUY();
	void SEL();
	void POKEMENU();
	void POKEMON();
	void BAG();
};

