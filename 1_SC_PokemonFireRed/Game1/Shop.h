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

	//�޴�
	ObImage* mapMenu;
	ObImage* mapMenuSel;
	int menuSel;
	//�޴� ���ϸ�
	PokeMenu* pokeMenu;
	//�޴� ����
	BagMenu* bag;

	Player* player;
	//�̵���ų ��ġ
	Vector2 plDest;
	Vector2 plSour;
	//����
	float   g;
	Vector2 lastPos;
	//�� ĭ�� �̵�
	bool playerGo;
	bool playerTurn;
	bool goWall;
	//�����
	float wallTime;
	//������
	Item* setItem[2];
	ObImage* closeImg;

	//���� �޼���
	wstring shopMes;
	int mesNum;
	int mesIndex;
	float mesTime;
	//����ȯ
	bool goTown;
	//����
	float lightCol;
	bool fadeIn;
	bool fadeOut;

public:
	// Scene��(��) ���� ��ӵ�
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

